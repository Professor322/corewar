//
// Created by Dacey mormont Jon connington on 21/12/2019.
//

#include "corewar.h"

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int reg1;
	int reg2;
	int reg3;

	reg1 = args[0].value;
	reg2 = args[1].value;
	reg3 = args[2].value;
	car->regs[REG(reg3)] = car->regs[REG(reg1)] + car->regs[REG(reg2)];
	cbox = cbox;
    if (cbox->flags & V_FLAG_CHECK) {
        ft_printf("P% 5lu | add r%d r%d r%d\n", car->id + 1,
                  reg1, reg2, reg3);
    }
}

void		ft_add(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = ADD_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, sub_add_validate_permitted_types);
}