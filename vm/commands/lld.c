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
	int		val0;

	if (args[0].type == IND)
        val0 = get_int_from_bytes(cbox->arena.arena, car->pos + args[0].value, REG_SIZE);
	else
	    val0 = get_int_from_arg(car, cbox, args[0]);
    reg = args[1].value;
    car->regs[REG(reg)] = val0;
	if (val0 == 0)
		car->carry = 1;
	else
		car->carry = 0;
    if (cbox->flags & V_FLAG_OPER)
        ft_printf("P % 4lu | lld %d r%d\n", car->id + 1, val0, reg);
}

void ft_lld(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LLD_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}