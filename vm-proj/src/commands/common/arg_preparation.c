/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_preparation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djon-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:43:53 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/09 14:43:53 by djon-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm-proj/includes/corewar.h"

/*
** Setting and validating arg types
** or else setting dafaults for function
*/

int		prepare_arguments(t_carbox *carbox,
							t_arg args[CW_MAX_ARGS],
							int (*validate_permitted_types)(t_arg*))
{
	if (carbox->car->oper.has_type_byte)
	{
		cw_get_arg_types(carbox->car, carbox->cbox, args);
		if (!validate_permitted_types(args))
			return (0);
	}
	else
		validate_permitted_types(args);
	if (!get_arg_values(carbox->car, carbox->cbox, args))
		return (0);
	return (1);
}

int		get_arg_size(t_car *car, t_arg_type type)
{
	if (type == DIR)
		return (car->oper.t_dir_size);
	else
		return (get_default_arg_size(type));
}

void	cw_get_arg_types(t_car *car, t_cbox *cbox, t_arg *args)
{
	int				i;
	unsigned char	byte;

	byte = cbox->arena.arena[POS(car->pos + OP_BYTE_OFFSET)];
	i = 0;
	while (i < CW_MAX_ARGS)
	{
		if (i < car->oper.args_amount)
		{
			args[i].type = byte >> ((CW_MAX_ARGS - i - 1) * 2) & 0b11;
			args[i].size = get_arg_size(car, args[i].type);
		}
		else
		{
			args[i].type = 0;
			args[i].size = 0;
		}
		i++;
	}
}

int		get_arg_values(t_car *car, t_cbox *cbox, t_arg *args)
{
	unsigned char	*arr;
	unsigned int	arg_i;
	unsigned int	arr_i;

	arg_i = 0;
	arr_i = car->oper.has_type_byte + OP_BYTE_OFFSET;
	arr = cbox->arena.arena;
	while (arg_i < CW_MAX_ARGS && args[arg_i].type != NONE)
	{
		args[arg_i].value = get_int_from_bytes(arr,
						car->pos + arr_i, args[arg_i].size);
		arr_i += args[arg_i].size;
		if (args[arg_i].type == REG && !valid_reg_number(args[arg_i].value))
			return (0);
		arg_i++;
	}
	return (1);
}
