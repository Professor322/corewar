/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:28:46 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 20:31:28 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** If operation is invalid, move carry to the next byte
** and put it to the next unit at timeline
*/
void	invalid_operation(t_car *car, t_cbox *cbox)
{
	car->pos = (car->pos + 1) % MEM_SIZE;
//	ft_printf(" ---%s--- ", car->oper.name);
}

/*
** Try to set operation if there is no one in the carry.
** If operation is valid, move carry to N-1 units by timeline,
** otherwise move it just to the next unit
*/
t_oper	get_operation(char code)
{
	static t_oper	operations[] = {
			{"live", ft_live, 10, FALSE, 4, 1},
			{"ld", ft_ld, 5, TRUE, 4, 2},
			{"st", ft_st, 5, TRUE, 4, 2},
			{"add", ft_add, 10, TRUE, 4, 3},
			{"sub", ft_sub, 10, TRUE, 4, 3},
			{"and", ft_and, 6, TRUE, 4, 3},
			{"or", ft_or, 6, TRUE, 4, 3},
			{"xor", ft_xor, 6, TRUE, 4, 3},
			{"zjmp", ft_zjmp, 20, FALSE, 2, 1},
			{"ldi", ft_ldi, 25, TRUE, 2, 3},
			{"sti", ft_sti, 25, TRUE, 2, 3},
			{"fork", ft_fork, 800, FALSE, 2, 1},
			{"lld", ft_lld, 10, TRUE, 4, 2},
			{"lldi", ft_lldi, 50, TRUE, 2, 3},
			{"lfork", ft_lfork, 1000, FALSE, 2, 2},
			{"aff", ft_aff, 2, TRUE, 4, 2},
			{"inval", invalid_operation, 1, FALSE, 4, 0}
	};
//	ft_printf(" ---set operation--- ");
	return (code > 0 && code <= NUMBER_OF_OPERATIONS ?
	operations[code - 1] : operations[NUMBER_OF_OPERATIONS]);
}

