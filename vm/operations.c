/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:28:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/28 19:11:34 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	decorator(t_car *car)
{
	ft_printf(" ---%s--- ", car->oper.name);
	car->oper = (t_oper){"", NULL, 0};
}

void	moke_up_function(t_car *car)
{
	decorator(car);
}

/*
** If operation is invalid, move carry to the next byte
** and put it to the next unit at timeline
*/

void	invalid_operation(t_car *car)
{
	car->pos = (car->pos + 1) % MEM_SIZE;
	decorator(car);
}

t_oper	get_operation(char code)
{

	static t_oper	operations[] = {
			{"ft_live", ft_live, 10, FALSE},
			{"ft_ld", ft_ld, 5, TRUE},
			{"ft_st", ft_st, 5, TRUE},
			{"ft_add", ft_add, 10, TRUE},
			{"sub", ft_sub, 10, TRUE},
			{"and", ft_and, 6, TRUE},
			{"or", &moke_up_function, 6, TRUE},
			{"xor", &moke_up_function, 6, TRUE},
			{"zjmp", &moke_up_function, 20, FALSE},
			{"ldi", &moke_up_function, 25, TRUE},
			{"sti", &moke_up_function, 25, TRUE},
			{"fork", &moke_up_function, 800, FALSE},
			{"lld", &moke_up_function, 10, TRUE},
			{"lldi", &moke_up_function, 50, TRUE},
			{"lfork", &moke_up_function, 1000, FALSE},
			{"aff", &moke_up_function, 2, TRUE},
			{"inval", &invalid_operation, 1, FALSE}
	};
	ft_printf(" ---set operation--- ");
	return (code > 0 && code <= NUMBER_OF_OPERATIONS ?
	operations[code - 1] : operations[NUMBER_OF_OPERATIONS]);
}

