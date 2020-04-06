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
** fetch space for new car
*/
t_car	*fetch_free_car(t_cbox *cbox)
{
	t_car	**cars;
	t_car	*new;

	if (!cbox->dead_cars->len)
	{
		// malloc new car if we dont have dead cars
		if (!(new = ft_memalloc(sizeof(t_car))))
			exit(clean_all(cbox, MALLOC_ERROR));
		// remember it in overall cars array
		if (!(cbox->cars = ft_vadd(cbox->cars, &new, sizeof(t_car*))))
			exit(clean_all(cbox, MALLOC_ERROR));
		return new;
	}
	// get car from cemetery, clean up grave
	cars = (t_car **)(cbox->dead_cars->cont);
	new = cars[cbox->dead_cars->len - 1];
	ft_bzero(cars[cbox->dead_cars->len - 1], sizeof(t_car *));
	cbox->dead_cars->len -= 1;
	return new;
}


/*
** reschedule car in timeline (now + time_delta)
*/
void	reschedule_car(t_cbox *cbox, t_car *car, int time_delta)
{
	int	next_time;

	next_time = (cbox->cycle_counter + time_delta) % SIZE_OF_TIMELINE;
	if (!push_que(cbox->timeline[next_time], car, -car->id))
		exit(clean_all(cbox, MALLOC_ERROR));
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
	// add to timeline
	reschedule_car(cbox, new, 0);
}


void	print_car(t_car *car)
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
}

void	print_car_without_reg(t_car *car)
{
    ft_printf("P\t%d | %4s | pos=%-4d, carry=%d",
              car->id + 1,
              car->oper.f != NULL ? car->oper.name : "NULL",
              car->pos,
              car->carry);
}
