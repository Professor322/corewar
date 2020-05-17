/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:17:03 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/17 20:02:46 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void				refresh_heap(t_cbox *cbox, int index)
{
	t_vector	*tmp;
	t_car		*car;

	while (cbox->eventloop[index]->len)
	{
		car = (t_car *)pop_que(cbox->eventloop[index]).data;
		if (car->in_event_loop == 0)
			continue;
		car_to_heap(car, cbox->rip, cbox);
	}
	tmp = cbox->eventloop[index];
	cbox->eventloop[index] = cbox->rip;
	cbox->rip = tmp;
}

/*
** kill cars in rip:
** - clean space of car, put it pointer to dead_car cemetery
** - refresh heap in eventloop
*/

static void				kill_cars(t_cbox *cbox)
{
	t_car			*car;
	int				i;
	unsigned char	to_refresh[SIZE_OF_EVENTLOOP];

	ft_bzero(to_refresh, SIZE_OF_EVENTLOOP * sizeof(unsigned char));
	while (cbox->rip->len)
	{
		car = (t_car *)pop_que(cbox->rip).data;
		if (cbox->flags & V_FLAG_DEATHS)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					car->id + 1, cbox->cycle_counter - car->last_live,
					cbox->arena.cycles_to_die);
		to_refresh[car->in_event_loop - 1] = 1;
		place_car(car->pos, -car->regs[0], cbox, "pop");
		change_car_count(-car->regs[0], cbox, -1);
		ft_bzero(car, sizeof(t_car));
		car_to_vec(car, cbox->dead_cars, cbox);
	}
	i = -1;
	while (++i < SIZE_OF_EVENTLOOP)
		if (to_refresh[i])
			refresh_heap(cbox, i);
	show_deaths(cbox);
}

/*
** check cars and remember (to rip) the ones to kill
** return 1 if somebody alive, otherwise 0
*/

static unsigned char	check_cars(t_cbox *cbox)
{
	ssize_t			i;
	t_car			**cars;
	unsigned char	somebody_alive;

	somebody_alive = 0;
	cars = (t_car **)(cbox->cars->cont);
	i = -1;
	while ((size_t)++i < cars_len(cbox->cars))
	{
		if (cars[i]->in_event_loop == 0)
			continue;
		if ((int)(cbox->cycle_counter - cars[i]->last_live) >=
		cbox->arena.cycles_to_die)
		{
			car_to_heap(cars[i], cbox->rip, cbox);
		}
		else
			somebody_alive = 1;
	}
	show_deaths(cbox);
	kill_cars(cbox);
	return (somebody_alive);
}

/*
** if necessary check all cars and reset constants
*/

static unsigned char	check(t_cbox *cbox, t_arena *arena)
{
	unsigned char	out;

	if (((int)((cbox->cycle_counter + 1) - arena->last_check) !=
	arena->cycles_to_die) && arena->cycles_to_die > 0)
		return (1);
	out = check_cars(cbox);
	arena->last_check = cbox->cycle_counter + 1;
	if (arena->live_count >= NBR_LIVE || arena->checks_count == MAX_CHECKS - 1)
	{
		arena->cycles_to_die -= CYCLE_DELTA;
		show_cycles_to_die(cbox);
		arena->checks_count = 0;
		if (cbox->flags & V_FLAG_CYCLES)
			ft_printf("Cycle to die is now %d\n", arena->cycles_to_die);
	}
	else
		arena->checks_count += 1;
	show_nbr_checks(cbox);
	arena->live_count = 0;
	show_nbr_lives(cbox);
	return (out);
}

/*
** For each carry in the unit of eventloop do one of two options:
** - try to set operation if there is no one (NULL) in the carry;
** - execute operation
*/

unsigned char			do_the_fight(t_cbox *cbox)
{
	t_car	*car;
	int		cycle;

	if (cbox->flags & V_FLAG_CYCLES)
		ft_printf("It is now cycle %d\n", cbox->cycle_counter + 1);
	show_cycle(cbox);
	cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
	while (cbox->eventloop[cycle]->len)
	{
		car = (t_car *)pop_que(cbox->eventloop[cycle]).data;
		if (car->oper.f == NULL)
		{
			car->oper = get_operation(cbox->arena.arena[POS(car->pos)]);
			reschedule_car(cbox, car, car->oper.delay - 1);
		}
		else
		{
			car->pos = POS(car->pos);
			car->oper.f(car, cbox);
			ft_bzero(&car->oper, sizeof(t_oper));
			reschedule_car(cbox, car, 1);
		}
	}
	return (check(cbox, &cbox->arena));
}
