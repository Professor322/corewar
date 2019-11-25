/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:28:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/25 14:10:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	moke_up_function()
{
	ft_printf("some function do some operation here\n");
}

t_oper	get_operation(char code)
{
	static t_oper	operations[] = {
			{"live", &moke_up_function},
			{"ld", &moke_up_function},
			{"st", &moke_up_function},
			{"add", &moke_up_function},
			{"sub", &moke_up_function},
			{"and", &moke_up_function},
			{"or", &moke_up_function},
			{"xor", &moke_up_function},
			{"zjmp", &moke_up_function},
			{"ldi", &moke_up_function},
			{"sti", &moke_up_function},
			{"fork", &moke_up_function},
			{"lld", &moke_up_function},
			{"lldi", &moke_up_function},
			{"lfork", &moke_up_function},
			{"aff", &moke_up_function}
	};
	return (operations[code - 1]);
}

