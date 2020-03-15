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

int		prepare_arguments(t_carbox *carbox,
		t_arg args[CW_MAX_ARGS],
		int (*validate_permitted_types)(t_arg*))
{
	if (carbox->car->oper.has_type_byte)
	{
		cw_get_arg_types(carbox->car, carbox->cbox, args);
		if (!validate_permitted_types(args))
			return 0;
	}
	else
	{
		validate_permitted_types(args); // set default types
	}
	if (!get_arg_values(carbox->car, carbox->cbox, args))
		return 0;
	return 1;
}

int		get_arg_size(t_car *car, t_arg_type type)
{
	if (type == DIR)
		return car->oper.t_dir_size;
	else
		return get_default_arg_size(type);
}

void	cw_get_arg_types(t_car *car, t_cbox *cbox, t_arg *args)
{
	unsigned int i;
	unsigned char byte;

	byte = cbox->arena.arena[POS(car->pos + OP_BYTE_OFFSET)];
	i = 0;
	while (i < CW_MAX_ARGS) {
		args[i].type = byte >> ((CW_MAX_ARGS - i - 1) * 2) & 0b11;
		args[i].size = get_arg_size(car, args[i].type);
		i++;
	}
}

int		get_int_from_bytes(unsigned char *arr, unsigned int pos, int size)
{
	char 	c;
	short	s;
	int		i;
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

int 	get_int_from_arg(t_car *car, t_cbox *cbox, t_arg arg)
{
	if (arg.type == IND)
		return get_int_from_bytes(cbox->arena.arena, car->pos + IND_OFFSET(arg.value), REG_SIZE);
	else if (arg.type == DIR )
		return arg.value;
	else if (arg.type == REG)
		return car->regs[REG(arg.value)];
	else
		return 0;
}

int		get_arg_values(t_car *car, t_cbox *cbox, t_arg *args)
{
	unsigned char	*arr;
	unsigned int	arg_i;
	unsigned int 	arr_i;

	arg_i = 0;
	arr_i = car->oper.has_type_byte + OP_BYTE_OFFSET;
	arr = cbox->arena.arena;

	while (arg_i < CW_MAX_ARGS && args[arg_i].type != NONE)
	{
		args[arg_i].value = get_int_from_bytes(arr, car->pos + arr_i, args[arg_i].size);
		arr_i += args[arg_i].size;
		if (args[arg_i].type == REG && !valid_reg_number(args[arg_i].value))
		{
			//todo remove printf before release
			ft_printf("BAD REG NUMBER\n");
			return 0;
		}
		arg_i++;
	}
	return 1;
}

int		validate_command_byte(t_carbox *carbox)
{
	unsigned char c;

	c = carbox->cbox->arena.arena[carbox->car->pos];
	return c == carbox->op_command_code;
}

int		validate_user(t_cbox *cbox, int value) // todo: ????
{
	if (value < 0 || value > cbox->champs_amount)
		return 0;
	return 1;
}

void	exec_command(t_carbox *carbox,
		void (*op_unique_commands)(t_car*, t_cbox*, t_arg[CW_MAX_ARGS]),
		int (*validate_permitted_types)(t_arg*))
{
	t_arg		args[CW_MAX_ARGS];

	if (!validate_command_byte(carbox))
	{
		carbox->car->pos = POS(carbox->car->pos + 1);
		return ;
	}
	if (prepare_arguments(carbox, args, validate_permitted_types))
		op_unique_commands(carbox->car, carbox->cbox, args);
	move_car(carbox->car, args);
}


void	write_int_to_bytes(unsigned char *arr, unsigned int pos, unsigned int val)
{
	arr[POS(pos++)] = val >> 24;
	arr[POS(pos++)] = val >> 16;
	arr[POS(pos++)] = val >> 8;
	arr[POS(pos)] = val;
}