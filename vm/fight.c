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

unsigned char check(t_cbox *cbox)
{
	unsigned char do_check;

	dont_check = cbox->arena.cycles_to_die && cbox->cycle_counter % cbox->arena.cycles_to_die;
	if (dont_check)
		return 1;
	// TODO death of cars
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
		print_car(car);
		if (car->oper.f == NULL)
			set_operation(car, cbox);
		else
		{
			car->oper.f(car, cbox);
			ft_bzero(&car->oper, sizeof(t_oper));
			next_time = (cbox->cycle_counter + 1) % CYCLE_OF_TIMELINE;
			push_que(cbox->timeline[next_time], car, -car->id);
			car->next_time = next_time;
		}
	}
	return (check(cbox));
}
