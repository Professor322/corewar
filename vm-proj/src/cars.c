/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:47:18 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/17 18:27:07 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm-proj/includes/corewar.h"

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
	ft_bzero(cbox->dead_cars->cont + cbox->dead_cars->len, sizeof(t_car *));
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
