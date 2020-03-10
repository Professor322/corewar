/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:47:18 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/25 14:41:45 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car	*make_car(t_cbox *cbox, char player, unsigned int pos, int next_time)
{
	t_car	*new;

	if (!(new = ft_memalloc(sizeof(t_car))))
		exit(clean_all(cbox, MALLOC_ERROR));
	cbox->carry_counter += 1;
	new->id = cbox->carry_counter;
	new->regs[0] = player;
	new->pos = pos;
	new->next_time = next_time;
	return new;
}

void	print_car(t_car *car)
{
	ft_printf("\nP\t%d | %s | pos=%-4d, carry=%d",
			car->id,
			car->oper.f != NULL ? car->oper.name : "NULL",
			car->pos,
			car->carry);
	ft_printf(" regs=[");
	int i = -1;
	while (++i < REG_NUMBER)
		ft_printf("r%d %-2d, ", i+1, car->regs[i]);
	ft_printf("]");
}
