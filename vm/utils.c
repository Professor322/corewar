/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:39:01 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/09 22:23:30 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** need to clean: heps in eventloop, dead cars, rip, every car, cars
*/

int		clean_all(t_cbox *cbox, char code_exit)
{
	int	cars_count;
	int	i;

	finish_interface(cbox);
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
	return (code_exit);
}

void	dump_arena(unsigned char *arena)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!i)
			ft_printf("0x%#.4x : ", i);
		else if (!(i % 64))
			ft_printf("\n%#.4x : ", i);
		ft_printf("%c%c ", HEX[arena[i] / 16], HEX[arena[i] % 16]);
	}
	ft_printf("\n");
}

void	car_to_vec(t_car *car, t_vector *vec, t_cbox *cbox)
{
	if (!(ft_vadd(vec, &car, sizeof(t_car *))))
		exit(clean_all(cbox, MALLOC_ERROR));
}

void	car_to_heap(t_car *car, t_vector *heap, t_cbox *cbox)
{
	if (!(push_que(heap, car, -car->id)))
		exit(clean_all(cbox, MALLOC_ERROR));
}

void	cw_exit(t_cbox *cbox, char *msg, char *filename)
{
	ft_putstr_fd("Error with champion ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(clean_all(cbox, INPUT_ERROR));
}
