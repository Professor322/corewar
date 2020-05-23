/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:02 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/10 18:07:17 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm-proj/includes/corewar.h"

static int	validate_permitted_types(t_arg *args)
{
	if (args[0].type == REG
		&&
		args[1].type == NONE
		&&
		args[2].type == NONE
		&&
		args[3].type == NONE)
		return (1);
	return (0);
}

static void	op_unique_commands(t_car *car,
		t_cbox *cbox,
		t_arg args[CW_MAX_ARGS])
{
	int val1;

	val1 = get_int_from_arg(car, cbox, args[0]);
	if (cbox->flags & A_FLAG_EXIST)
		ft_printf("Aff: %c\n", val1);
}

void		ft_aff(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = AFF_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}
