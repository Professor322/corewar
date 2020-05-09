/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djon-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:05 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/09 14:44:05 by djon-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	op_unique_commands(t_car *car,
		t_cbox *cbox,
		t_arg args[CW_MAX_ARGS])
{
	int val1;
	int val2;
	int value;
	int reg;

	val1 = get_int_from_arg(car, cbox, args[0]);
	val2 = get_int_from_arg(car, cbox, args[1]);
	value = val1 & val2;
	reg = args[2].value;
	car->regs[REG(reg)] = value;
	if (value == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if (cbox->flags & V_FLAG_OPER)
	{
		ft_printf("P % 4lu | and %d %d r%d\n",
					car->id + 1, val1, val2, reg);
	}
}

void		ft_and(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = AND_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, logical_validate_permitted_types);
}
