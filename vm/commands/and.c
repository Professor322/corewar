//
// Created by Dacey mormont Jon connington on 21/12/2019.
//

#include "corewar.h"

static int	validate_permitted_types(t_arg *args)
{
	if ((args[0].type == REG || args[0].type == DIR || args[0].type == IND)
		&&
		(args[1].type == REG || args[1].type == DIR || args[1].type == IND)
		&&
		args[2].type == REG
		&&
		args[3].type == NONE)
		return 1;
	return 0;
	//todo return and-or-xor validation function
}

static int	get_arg_size(t_arg_type type)
{
	return get_default_arg_size(type);
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
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
}

void		ft_and(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = AND_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, get_arg_size,
				 validate_permitted_types);
}