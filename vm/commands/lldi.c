/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:10 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/16 22:03:39 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	validate_permitted_types(t_arg *args)
{
	if ((args[0].type == REG || args[0].type == DIR || args[0].type == IND)
		&&
		(args[1].type == REG || args[1].type == DIR)
		&&
		args[2].type == REG
		&&
		args[3].type == NONE)
		return (1);
	return (0);
}

static void	op_unique_commands(t_car *car,
								t_cbox *cbox,
								t_arg args[CW_MAX_ARGS])
{
	int		reg;
	int		val1;
	int		val2;
	int		value;

	val1 = get_int_from_arg(car, cbox, args[0]);
	val2 = get_int_from_arg(car, cbox, args[1]);
	reg = args[2].value;
	value = get_int_from_bytes(cbox->arena.arena, car->pos + val1 + val2,
			REG_SIZE);
	car_change_player(reg, -car->regs[0], -value, cbox);
	car->regs[REG(reg)] = value;
	if (car->regs[REG(reg)] == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if (cbox->flags & V_FLAG_OPER)
	{
		ft_printf("P % 4lu | lldi %d %d r%d\n",
				car->id + 1, val1, val2, reg);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n"
				, val1, val2, val1 + val2, car->pos + val1 + val2);
	}
}

void		ft_lldi(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LLDI_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}
