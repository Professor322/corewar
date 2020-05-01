/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:17:03 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 21:50:44 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	kill_cars(t_cbox *cbox)
{
	size_t i;
    size_t cars_vec;
	t_car	**cars;
	t_arena	ar;
	unsigned char somebody_alive;

	somebody_alive = 0;
	cars = (t_car **)(cbox->cars->cont);
	ar = cbox->arena;
	i = cars_len(cbox->cars);
	while (--i != -1) // max value of size_t
	{
		if (!cars[i]) {
            continue;
		}
		if (cars[i]->last_live <= cbox->cycle_counter + 1 - ar.cycles_to_die)
		{
			// kill it: clean space of car and put it's pointer to cemetery
			if (cbox->flags & V_FLAG_DEATHS) {
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", cars[i]->id + 1,  cbox->cycle_counter - cars[i]->last_live, ar.cycles_to_die);
			}
			//ft_printf("%d kill= %d\n", cbox->cycle_counter, cars[i]->id + 1);
			ft_bzero(cars[i], sizeof(t_car));
			if (!(ft_vadd(cbox->dead_cars, &cars[i], sizeof(t_car *))))
				exit(clean_all(cbox, MALLOC_ERROR));
		}
		else
            somebody_alive = 1;
	}
	return somebody_alive;
}

unsigned char check(t_cbox *cbox, t_arena *arena)
{
	unsigned char	out;
    if (arena->cycles_to_die <= 0)
		// end of game
		return 0;
	if (((cbox->cycle_counter + 1) - arena->last_check) != arena->cycles_to_die)
		// not need to check
		return 1;
	// do check:
	dprintf(get_fd_debug(), "\t >>> Its check time");
	out = kill_cars(cbox);
	arena->last_check = cbox->cycle_counter + 1;
	if (arena->live_count >= NBR_LIVE || arena->checks_count == MAX_CHECKS - 1)
	{
		arena->cycles_to_die -= CYCLE_DELTA;
		arena->checks_count = 0;
    if (cbox->flags & V_FLAG_CHECK)
		  ft_printf("Cycle to die is now %d\n", arena->cycles_to_die);
	}
	else
		arena->checks_count += 1;
	arena->live_count = 0;
	return out;
}


/*
** For each carry in the unit at timeline do one of two options:
** - try to set operation if there is no one in the carry;
** - execute operation
*/

unsigned char	do_the_fight(t_cbox *cbox)
{
	t_car	*car;
	int 	cycle;

	if (cbox->flags & V_FLAG_CYCLES) {
		ft_printf("It is now cycle %d\n", cbox->cycle_counter + 1);
	}
	cycle = cbox->cycle_counter % SIZE_OF_TIMELINE;
	while (cbox->timeline[cycle]->len)
	{
		car = (t_car *) pop_que(cbox->timeline[cycle]).data;
		if (car == NULL)  // todo: kill car
			continue;
//		print_bytes(cbox, car, 4);
//		print_car(car);  // todo DEBUG
		if (car->oper.f == NULL)
		{
			// set new operation
			car->oper = get_operation(cbox->arena.arena[POS(car->pos)]);
			reschedule_car(cbox, car, car->oper.delay - 1);
		}
		else
		{
//		    print_bytes(cbox, car, 30);
			// do operation
			if (ft_strcmp(car->oper.name, "ld"))
			    dprintf(get_fd_debug(), "oper_to_do=\t\t\t%s\n", car->oper.name);
			car->oper.f(car, cbox);
//            if (car->regs[11] == 190057729) ft_printf("\033[0;91m");
//            ft_printf("r12 value %d\n\033[0;10m", car->regs[11]);
			ft_bzero(&car->oper, sizeof(t_oper)); // ??
			// set new operation will be in next turn
			reschedule_car(cbox, car, 1);
		}
	}
	return (check(cbox, &cbox->arena));
}