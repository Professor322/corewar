//
// Created by Cricun on 18.12.2019.
//

#include "corewar.h"

static int validate_permitted_types(t_arg *args)
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

static int get_arg_size(t_arg_type type)
{
	return get_default_arg_size(type);
}

void live(t_car *car, t_cbox *cbox)
{
	t_arg args[CW_MAX_ARGS];
	t_arg val;
	t_carbox	carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	if (prepare_arguments(carbox, args, get_arg_size, validate_permitted_types))
	{
		val = args[0];
		//todo

	}
	move_car(car, args);
}