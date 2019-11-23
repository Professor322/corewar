/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:17:03 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/23 20:33:12 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO check end of the game
int check(cycle)
{
	return (cycle > 10 ? 0 : 1);
}

int	do_the_fight(t_cbox *cbox, size_t cycle)
{
	t_car	*car;

	ft_printf("\nIt is now cycle %d", cycle + 1);
	cycle = cycle % SIZE_OF_TIMELINE;
	while (cbox->timeline[cycle]->len)
	{
		car = (t_car *) pop_que(cbox->timeline[cycle]).data;
		print_car(car);
	}
	return (check(cycle));
}