/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:17:03 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/10 23:24:51 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void	check_car(t_car *car, t_arena *arena)
{
	if (car->last_live <= arena->cycle - arena->cycles_to_die)
		ft_bzero(car, sizeof(t_car));
}

unsigned char check(t_cbox *cbox, t_arena *arena)
{
	ssize_t		i;
	t_car		*car;

	if (arena->cycles_to_die <= 0)
		// end of game
		return 0;
	if (cbox->cycle_counter % arena->cycles_to_die)
		// not need to check
		return 1;
	// do check:
	if (arena->live_count >= NBR_LIVE || arena->checks_count == MAX_CHECKS - 1)
	{
		arena->cycles_to_die -= CYCLE_DELTA;
		arena->checks_count = 0;
	}
	else
		arena->checks_count += 1;
	arena->live_count = 0;
	i = -1;
	while (++i < cbox->cars.len)
	{
		car = (t_car *)(cbox->cars.cont);
		if (car)
			check_car(car, &(cbox->arena));
		
	}
	// TODO death of cars
	return 1;
}



/*
** Try to set operation if there is no one in the carry.
** If operation is valid, move carry to N-1 units by timeline,
** otherwise move it just to the next unit
*/

void	set_operation(t_car *car, t_cbox *cbox)
{
	int 	next_time;

	// TODO if operation non-valid, time delay = 1 unit, move carry to the next byte
	car->oper = get_operation(cbox->arena.arena[car->pos]);
	next_time = (cbox->cycle_counter + car->oper.delay - 1) % SIZE_OF_TIMELINE;
	push_que(cbox->timeline[next_time], car, -car->id);
	car->next_time = next_time;
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
	int	next_time;

	ft_printf("\nIt is now cycle %d", cbox->cycle_counter + 1);
	cycle = cbox->cycle_counter % SIZE_OF_TIMELINE;
	while (cbox->timeline[cycle]->len)
	{
		car = (t_car *) pop_que(cbox->timeline[cycle]).data;
		if (!car->id)  // dead car
			continue;
		print_car(car);
		if (car->oper.f == NULL)
			set_operation(car, cbox);
		else
		{
			car->oper.f(car, cbox);
			ft_bzero(&car->oper, sizeof(t_oper));
			next_time = (cbox->cycle_counter + 1) % SIZE_OF_TIMELINE;
			push_que(cbox->timeline[next_time], car, -car->id);
			car->next_time = next_time;
		}
	}
	return (check(cbox, &cbox->arena));
}
