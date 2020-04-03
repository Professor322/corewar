//
// Created by Cricun on 18.12.2019.
//

#include "corewar.h"
//TODO доделать
static int	validate_permitted_types(t_arg *args)
{
    args[0].size = 4;
    args[1].type = NONE;
    args[2].type = NONE;
    args[3].type = NONE;
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
        car->last_live = cbox->arena.cycle; // car->last_live = cbox->cycle_counter; //todo cycle_counter?
    if (cbox->flags & V_FLAG_CHECK) {
        ft_printf("P    %lu | live %d\n", car->id + 1, val);
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