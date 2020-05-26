/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:39:01 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/17 18:34:08 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** need to clean: heaps in eventloop, dead cars, rip, every car, cars
*/

int		clean_all(t_cbox *cbox, char code_exit)
{
	int	cars_count;
	int	i;

	i = -1;
	while (++i < SIZE_OF_EVENTLOOP)
		if (cbox->eventloop[i])
			ft_vdel(&cbox->eventloop[i]);
	if (cbox->dead_cars)
		ft_vdel(&cbox->dead_cars);
	if (cbox->rip)
		ft_vdel(&cbox->rip);
	if (cbox->cars)
	{
		i = -1;
		cars_count = cars_len(cbox->cars);
		while (++i < cars_count)
			if (((t_car **)cbox->cars->cont)[i])
			{
				free(((t_car **)cbox->cars->cont)[i]);
				((t_car **)cbox->cars->cont)[i] = NULL;
			}
		ft_vdel(&cbox->cars);
	}
	finish_interface(cbox);
	return (code_exit);
}
