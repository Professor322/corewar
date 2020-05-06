/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:39:01 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 20:32:54 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define HEX "0123456789abcdef"

int 	clean_all(t_cbox *cbox, char code_exit)
{
    int cars_count;
	int 	i;

	// heaps in eventloop
	i = -1;
	while (++i < SIZE_OF_EVENTLOOP)
	    if (cbox->eventloop[i])
		    ft_vdel(&cbox->eventloop[i]);
    // vec for dead cars
    if (cbox->dead_cars)
        ft_vdel(&cbox->dead_cars);
    // vec for rip
    if (cbox->rip)
        ft_vdel(&cbox->rip);
	// cars
	if (cbox->cars)
	{
        i = -1;
        cars_count = cars_len(cbox->cars);
        while (++i < cars_count)
            if (((t_car **) cbox->cars->cont)[i]) {
                free(((t_car **) cbox->cars->cont)[i]);
                ((t_car **) cbox->cars->cont)[i] = NULL;
            }
        // vec for cars
        ft_vdel(&cbox->cars);
    }
	return code_exit;
}

void	dump_arena(unsigned char *arena)
{
	int i;

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

void car_to_vec(t_car *car, t_vector *vec, t_cbox *cbox)
{
	if (!(ft_vadd(vec, &car, sizeof(t_car *))))
	    exit(clean_all(cbox, MALLOC_ERROR));
}

void car_to_heap(t_car *car, t_vector *heap, t_cbox *cbox)
{
    if (!(push_que(heap, car, -car->id)))
        exit(clean_all(cbox, MALLOC_ERROR));
}

void cw_exit(t_cbox *cbox, char *msg, char *filename)
{
    ft_printf(msg, filename);
    ft_printf("\n");
    exit(clean_all(cbox, INPUT_ERROR));
}
