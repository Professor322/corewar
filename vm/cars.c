/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:47:18 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/23 20:48:06 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car	*make_car(t_cbox *cbox, char player, unsigned int pos)
{
	t_car	*new;

	if (!(new = ft_memalloc(sizeof(t_car))))
		exit(clean_all(cbox, MALLOC_ERROR));
	cbox->carry_counter += 1;
	new->id = cbox->carry_counter;
	new->regs[0] = player;
	new->pos = pos;
	// TODO init new car
	return new;
}

void	print_car(t_car *car)
{
	ft_printf(
			"\nid=%d carry=%b pos=%d\n",
			car->id,
			car->carry,
			car->pos
			);
}
