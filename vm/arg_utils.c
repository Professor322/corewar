//
// Created by Cricun on 11.12.2019.
//

#include "corewar.h"

void	 move_car(t_car *car, t_arg *args)
{
	int i;

	i = 0;
	car->pos += OP_BYTE_OFFSET;
	car->pos += car->oper.has_type_byte;
	while (i < CW_MAX_ARGS)
	{
		if (args[i].type)
			car->pos += args[i].size;
		i++;
	}
	car->pos = POS(car->pos);
}

int		get_default_arg_size(t_arg_type type)
{
	if (type == NONE)
		return 0;
	else if (type == REG)
		return T_REG_BYTE_SIZE;
	else if (type == DIR)
		return T_DIR_BYTE_SIZE;
	else if (type == IND)
		return T_IND_BYTE_SIZE;
	else
		ft_printf("WRONG ARGUMENT TYPE\n");
	return 0;
}

int		prepare_arguments(t_carbox carbox, t_arg args[CW_MAX_ARGS], int (*get_arg_size)(t_arg_type), int (*validate_permitted_types)(t_arg*))
{
	cw_get_arg_types(carbox.car, carbox.cbox, args, get_arg_size);
	if (!validate_permitted_types(args))
		return 0;
	if (!get_arg_values(carbox.car, carbox.cbox, args))
		return 0;
	return 1;
}

void	cw_get_arg_types(t_car *car, t_cbox *cbox, t_arg *args, int (*get_arg_size)(t_arg_type))
{
	unsigned int i;
	unsigned char byte;

	byte = cbox->arena.arena[POS(car->pos + OP_BYTE_OFFSET)];
	i = 0;
	while (i < CW_MAX_ARGS) {
		args[i].type = byte >> ((CW_MAX_ARGS - i - 1) * 2) & 0b11;
		args[i].size = get_arg_size(args[i].type);
		i++;
	}
}

int		get_int_from_bytes(unsigned char *arr, unsigned int pos, int size)
{
	char 	c;
	short	s;
	int		i;
	ft_printf("\n%b\n", arr);
	if (size == 1)
	{
		c = arr[POS(pos)];
		return c;
	}
	if (size == 2)
	{
		s = ((short)arr[POS(pos)]) << 8 | ((short)arr[POS(pos + 1)]);
		return s;
	}
	if (size == 4)
	{
		i = ((int)arr[POS(pos)]) << 24
			| ((int)arr[POS(pos + 1)]) << 16
			| ((int)arr[POS(pos + 2)]) << 8
			| ((int)arr[POS(pos + 3)]);
		return i;
	}
	ft_printf("INT TO BYTES CONVERSTION FAILED\n");
	exit(-42);
}

int		get_arg_values(t_car *car, t_cbox *cbox, t_arg *args)
{
	unsigned char	*arr;
	int				arg_i;
	int 			arr_i;

	arg_i = 0;
	arr_i = car->oper.has_type_byte + OP_BYTE_OFFSET;
	arr = cbox->arena.arena;

	while (arg_i < CW_MAX_ARGS && args[arg_i].type != NONE)
	{
		args[arg_i].value = get_int_from_bytes(arr, car->pos + arr_i, args[arg_i].size);
		arr_i += args[arg_i].size;
		if (args[arg_i].type == REG && !valid_reg_number(args[arg_i].value))
		{
			ft_printf("BAD REG NUMBER\n");
			return 0;
		}
		arg_i++;
	}
	return 1;
}

int validate_command_byte(t_car *car, t_cbox *cbox, int command_byte)
{
	unsigned char c;

	c = cbox->arena.arena[car->pos];
	return c == command_byte;
}