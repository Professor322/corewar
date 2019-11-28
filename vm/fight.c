/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:17:03 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/25 15:34:30 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int check(cycle)
{
	// TODO check end of the game
	return (cycle > 20 ? 0 : 1);
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
}

/*
** For each carry in the unit at timeline do one of two options:
** - try to set operation if there is no one in the carry;
*/

int	do_the_fight(t_cbox *cbox)
{
	t_car	*car;
	int 	cycle;

	ft_printf("\nIt is now cycle %d", cbox->cycle_counter + 1);
	cycle = cbox->cycle_counter % SIZE_OF_TIMELINE;
	while (cbox->timeline[cycle]->len)
	{
		car = (t_car *) pop_que(cbox->timeline[cycle]).data;
		print_car(car);
		if (car->oper.f == NULL)
			set_operation(car, cbox);
		else
		{
			car->oper.f(car);
			ft_bzero(&car->oper, sizeof(t_oper));
			push_que(cbox->timeline[(cbox->cycle_counter + 1) % SIZE_OF_TIMELINE], car, -car->id);
		}
	}
	return (check(cbox->cycle_counter));
}
