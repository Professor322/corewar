/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djon-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:06 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/09 14:44:06 by djon-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	set_types(t_arg *args)
{
	args[0].type = DIR;
	args[0].size = get_operation(FORK_COMMAND_CODE).t_dir_size;
	args[1].type = NONE;
	args[1].size = 0;
	args[2].type = NONE;
	args[2].size = 0;
	args[3].type = NONE;
	args[3].size = 0;
	return (1);
}

static void	op_unique_commands(t_car *old_car,
								t_cbox *cbox,
								t_arg args[CW_MAX_ARGS])
{
	t_car	*new_car;
	int		value;

	new_car = fetch_free_car(cbox);
	clone_car(old_car, new_car);
	new_car->id = cbox->car_counter;
	cbox->car_counter += 1;
	value = get_int_from_arg(old_car, cbox, args[0]);
	new_car->pos = new_car->pos + IND_OFFSET(value);
	ft_bzero(&new_car->oper, sizeof(t_oper));
	reschedule_car(cbox, new_car, 1);
	if (cbox->flags & V_FLAG_OPER)
	{
		ft_printf("P % 4lu | fork %d (%d)\n",
					old_car->id + 1, value, new_car->pos);
	}
}

void		ft_fork(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = FORK_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, set_types);
}
