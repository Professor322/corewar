//
// Created by Cricun on 18.12.2019.
//

#include "corewar.h"
//TODO доделать
static int	validate_permitted_types(t_arg *args)
{
	if (args[0].type == DIR
		&&
		args[1].type == NONE
		&&
		args[2].type == NONE
		&&
		args[3].type == NONE)
		return 1;
	return 0;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int			val;

	val = args[0].value;
	if (validate_user(cbox, val))
		car->is_alive = TRUE;
}

void		ft_live(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LIVE_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, get_default_arg_size,
				 validate_permitted_types);
}