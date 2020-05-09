/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djon-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:00 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/09 14:44:00 by djon-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	clone_regs(const int old[REG_NUMBER], int new[REG_NUMBER])
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		new[i] = old[i];
		i++;
	}
}

void	clone_car(t_car *old, t_car *new)
{
	new->pos = old->pos;
	new->last_live = old->last_live;
	new->carry = old->carry;
	new->id = old->id;
	new->oper = old->oper;
	clone_regs(old->regs, new->regs);
}
