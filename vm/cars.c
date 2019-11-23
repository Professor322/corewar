/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:47:18 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/23 19:06:38 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car	*make_car(t_cbox *cbox, char player)
{
	t_car	*new;

	if (!(new = ft_memalloc(sizeof(t_car))))
		exit(clean_all(cbox, MALLOC_ERROR));
	new->id = cbox->carry_counter;
	cbox->carry_counter += 1;
	new->regs[0] = player;
	// TODO init new car
	return new;
}
