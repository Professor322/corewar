/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:47:18 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/12 22:58:09 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** length of array of pointers to car
*/

size_t	cars_len(t_vector *cars_vec)
{
	return (cars_vec->len / sizeof(t_car *));
}

/*
** fetch pointer to new car with malloced space
** get it from dead cars if can otherwise create new
*/

t_car	*fetch_free_car(t_cbox *cbox)
{
	t_car	**cars;
	t_car	*new;
	size_t	dead_idx;

	if (!cbox->dead_cars->len)
	{
		if (!(new = ft_memalloc(sizeof(t_car))))
			exit(clean_all(cbox, MALLOC_ERROR));
		car_to_vec(new, cbox->cars, cbox);
		return (new);
	}
	cars = (t_car **)(cbox->dead_cars->cont);
	dead_idx = cars_len(cbox->dead_cars);
	new = cars[dead_idx - 1];
	cbox->dead_cars->len -= sizeof(t_car *);
	ft_bzero(cbox->dead_cars->cont + cbox->dead_cars->len - 1,
			sizeof(t_car *));
	return (new);
}

/*
** reschedule car in eventloop (now + time_delta)
*/

void	reschedule_car(t_cbox *cbox, t_car *car, int time_delta)
{
	int	next_time;

	next_time = (cbox->cycle_counter + time_delta) % SIZE_OF_EVENTLOOP;
	car->in_event_loop = next_time + 1;
	car_to_heap(car, cbox->eventloop[next_time], cbox);
}

/*
** make new empty car at the start of the game
*/

void	make_car(t_cbox *cbox, char player, unsigned int pos)
{
	t_car	*new;

	new = fetch_free_car(cbox);
	new->id = cbox->car_counter;
	cbox->car_counter += 1;
	new->regs[0] = player;
	new->pos = pos;
	new->last_live = -1;
	// add to eventloop
	reschedule_car(cbox, new, 0);
}

/*
void	print_car(t_car *car) //
{
	ft_printf("🚗P\t%d | %s | pos=%-4d, carry=%d",
			car->id + 1,
			car->oper.f != NULL ? car->oper.name : "NULL",
			car->pos,
			car->carry);
	ft_printf(" regs=[");
	int i = -1;
	while (++i < REG_NUMBER)
		ft_printf("r%d %-2d, ", i+1, car->regs[i]);
	ft_printf("]\n");
}*/
/*
void	print_car_without_reg(t_car *car) //
{
    ft_printf("P\t%d | %4s | pos=%-4d, carry=%d",
              car->id + 1,
              car->oper.f != NULL ? car->oper.name : "NULL",
              car->pos,
              car->carry);
}
*/
