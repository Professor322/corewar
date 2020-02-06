//
// Created by Dacey mormont Jon connington on 18/01/2020.
//

#include "corewar.h"

int	sub_add_validate_permitted_types(t_arg *args)
{
	if (args[0].type == REG
		&&
		args[1].type == REG
		&&
		args[2].type == REG
		&&
		args[3].type == NONE)
		return 1;
	return 0;
}