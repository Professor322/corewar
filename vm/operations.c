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
			{"live", &moke_up_function, 10},
			{"ld", &moke_up_function, 5},
			{"st", &moke_up_function, 5},
			{"add", &moke_up_function, 10},
			{"sub", &moke_up_function, 10},
			{"and", &moke_up_function, 6},
			{"or", &moke_up_function, 6},
			{"xor", &moke_up_function, 6},
			{"zjmp", &moke_up_function, 20},
			{"ldi", &moke_up_function, 25},
			{"sti", &moke_up_function, 25},
			{"fork", &moke_up_function, 800},
			{"lld", &moke_up_function, 10},
			{"lldi", &moke_up_function, 50},
			{"lfork", &moke_up_function, 1000},
			{"aff", &moke_up_function, 2},
			{"inval", &invalid_operation, 1}
	};
	ft_printf(" ---set operation--- ");
	return (code > 0 && code <= NUMBER_OF_OPERATIONS ?
	operations[code - 1] : operations[NUMBER_OF_OPERATIONS]);
}

