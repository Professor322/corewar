//
// Created by Dacey mormont Jon connington on 16/11/2019.
//

#include "../assembler.h"

t_foo		*live(t_command command)
{
	t_foo *foo;

	t_arg arg1 = get_arg(command.arg1, command.position, LIVE_T_DIR_SIZE);
	command.position += arg1.size;
	t_arg arg2 = get_arg(command.arg2, command.position, LIVE_T_DIR_SIZE);
	command.position += arg2.size;
	t_arg arg3 = get_arg(command.arg3, command.position, LIVE_T_DIR_SIZE);
	command.position += arg3.size;

	arg_to_bin(bin, arg1);
	bin += arg1.size;
	arg_to_bin(bin, arg2);
	bin += arg2.size;
	arg_to_bin(bin, arg3);
	bin += arg3.size;
	// собрать массив из меток
	return foo;
}