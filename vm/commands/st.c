//
// Created by Cricun on 18.12.2019.
//

#include "corewar.h"

static int validate_permitted_types(t_arg *args)
{
	if (args[0].type == REG
		&&
		(args[1].type == REG || args[1].type == IND)
		&&
		args[2].type == NONE
		&&
		args[3].type == NONE)
		return 1;
	return 0;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	t_arg		param;
	int			val;

	param = args[1];
    val = get_int_from_arg(car, cbox, args[0]);
	if (param.type == REG)
		car->regs[REG(param.value)] = val;
	else // IND
		write_int_to_bytes(cbox->arena.arena, car->pos + IND_OFFSET(param.value), val);
    if (cbox->flags & V_FLAG_CHECK) {
        ft_printf("P % 4lu | st r%d %d\n", car->id + 1, args[0].value, IND_OFFSET(param.value));
    }
}

void 		ft_st(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = ST_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}