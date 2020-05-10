/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:28:46 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 03:21:36 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** If operation is invalid, move carry to the next byte
** and put it to the next unit at eventloop
*/

void	invalid_operation(t_car *car, t_cbox *cbox)
{
	car->pos = POS(car->pos + 1);
	drive_car(car->pos, -(car->pos + 1), car->regs[0], cbox);
}

/*
** Try to set operation if there is no one in the carry.
** If operation is valid, move carry to N-1 units by eventloop,
** otherwise move it just to the next unit
*/

t_oper	get_operation(char code)
{
	static t_oper	operations[] = {
			{ft_live, 10, T_FALSE, 4, 1},
			{ft_ld, 5, T_TRUE, 4, 2},
			{ft_st, 5, T_TRUE, 4, 2},
			{ft_add, 10, T_TRUE, 4, 3},
			{ft_sub, 10, T_TRUE, 4, 3},
			{ft_and, 6, T_TRUE, 4, 3},
			{ft_or, 6, T_TRUE, 4, 3},
			{ft_xor, 6, T_TRUE, 4, 3},
			{ft_zjmp, 20, T_FALSE, 2, 1},
			{ft_ldi, 25, T_TRUE, 2, 3},
			{ft_sti, 25, T_TRUE, 2, 3},
			{ft_fork, 800, T_FALSE, 2, 1},
			{ft_lld, 10, T_TRUE, 4, 2},
			{ft_lldi, 50, T_TRUE, 2, 3},
			{ft_lfork, 1000, T_FALSE, 2, 2},
			{ft_aff, 2, T_TRUE, 4, 1},
			{invalid_operation, 1, T_FALSE, 4, 0}
	};

	return (code > 0 && code <= NUMBER_OF_OPERATIONS ?
	operations[code - 1] : operations[NUMBER_OF_OPERATIONS]);
}
