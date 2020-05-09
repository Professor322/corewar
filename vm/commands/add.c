#include "corewar.h"

static void	op_unique_commands(t_car *car,
								t_cbox *cbox,
								t_arg args[CW_MAX_ARGS])
{
	int reg1;
	int reg2;
	int reg3;

	reg1 = args[0].value;
	reg2 = args[1].value;
	reg3 = args[2].value;
	car->regs[REG(reg3)] = car->regs[REG(reg1)] + car->regs[REG(reg2)];
	if (car->regs[REG(reg3)] == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if (cbox->flags & V_FLAG_OPER)
	{
		ft_printf("P % 4lu | add r%d r%d r%d\n", car->id + 1,
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
