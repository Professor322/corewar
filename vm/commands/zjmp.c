//
// Created by Dacey mormont Jon connington on 21/12/2019.
//

#include "corewar.h"

static int set_types(t_arg *args)
{
	args[0].type = DIR;
	args[0].size = get_operation(ZJMP_COMMAND_CODE).t_dir_size;
    args[1].type = NONE;
    args[1].size = 0;
    args[2].type = NONE;
    args[2].size = 0;
    args[3].type = NONE;
    args[3].size = 0;
	return 1;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int val1;

	val1 = get_int_from_arg(car, cbox, args[0]);
	if (car->carry == 1)
		car->pos = POS(car->pos + IND_OFFSET(val1));
    if (cbox->flags & V_FLAG_CHECK) {
        if (car->carry == 1)
            ft_printf("P % 4lu | zjmp %d OK\n", car->id + 1, val1);
        else
            ft_printf("P % 4lu | zjmp %d FAILED\n", car->id + 1, val1);
    }
    //if (countdown(1))
      //  print_cars(cbox);//print_timeline(cbox);
}

void		ft_zjmp(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = ZJMP_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, set_types);
}