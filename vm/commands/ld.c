//
// Created by Cricun on 11.12.2019.
//

#include "corewar.h"

static int validate_permitted_types(t_arg *args)
{
	if ((args[0].type == DIR || args[0].type == IND)
		&&
		args[1].type == REG
		&&
		args[2].type == NONE
		&&
		args[3].type == NONE)
		return 1;
	return 0;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int		reg;
	int		value;

	value = get_int_from_arg(car, cbox, args[0]);
	reg = args[1].value;
	car->regs[REG(reg)] = value;
	if (value == 0)
		car->carry = 1;
	else
		car->carry = 0;
	//dprintf(get_fd_debug(), "P % 4lu | ld %d r%d\n", car->id + 1, value, reg);
	if (cbox->flags & V_FLAG_CHECK)
        ft_printf("P % 4lu | ld %d r%d\n", car->id + 1, value, reg);
}

void ft_ld(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LD_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}