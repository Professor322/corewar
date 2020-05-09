/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djon-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:09 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/09 14:44:09 by djon-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	validate_permitted_types(t_arg *args)
{
	args[0].type = DIR;
	args[0].size = 4;
	args[1].type = NONE;
	args[1].size = 0;
	args[2].type = NONE;
	args[2].size = 0;
	args[3].type = NONE;
	args[3].size = 0;
	return (1);
}

static void	op_unique_commands(t_car *car,
			t_cbox *cbox,
			t_arg args[CW_MAX_ARGS])
{
	int val;

	val = args[0].value;
	car->last_live = cbox->cycle_counter;
	cbox->arena.live_count++;
	if (cbox->flags & V_FLAG_OPER)
		ft_printf("P % 4lu | live %d\n", car->id + 1, val);
	if (validate_user(cbox, -val))
	{
		cbox->arena.last_alive = -val;
		if (cbox->flags & V_FLAG_LIVES)
			ft_printf("Player %d (%s) is said to be alive\n", -val,
					cbox->champs[-val - 1].name);
	}
}

void		ft_live(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LIVE_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}
