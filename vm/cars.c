/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:47:18 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 21:27:18 by mbartole         ###   ########.fr       */
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
** length of queue
*/

size_t	queue_len(t_vector *queue_vec)
{
	return (queue_vec->len / sizeof(t_pque));
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
	place_car(pos, -player, cbox);
	change_car_count(-player, cbox, 1);
	call_it_alive(-player, cbox);
	new->last_live = -1;
	reschedule_car(cbox, new, 0);
}
