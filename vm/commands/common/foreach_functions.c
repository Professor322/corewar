//
// Created by Cricun on 12.12.2019.
//

#include "corewar.h"

int		valid_reg_number(int value)
{
	if (value < 1 || value > REG_NUMBER)
		return 0;
	return 1;
}