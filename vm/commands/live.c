//
// Created by Cricun on 18.12.2019.
//

#include "corewar.h"
//TODO доделать
static int	validate_permitted_types(t_arg *args)
{
    args[0].type = DIR;
    args[0].size = 4;
    args[1].type = NONE;
    args[1].size = 0;
    args[2].type = NONE;
    args[2].size = 0;
    args[3].type = NONE;
    args[3].size = 0;
    return 1;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS]) {
    int val;

    val = args[0].value;
    //val = get_int_from_arg(car, cbox, args[0]);
    car->last_live = cbox->cycle_counter; //todo cycle_counter?
    cbox->arena.live_count++;
    if (validate_user(cbox, -val)) {
        cbox->arena.last_alive = val;
    }
    if (cbox->flags & V_FLAG_CHECK) {
        ft_printf("P % 4lu | live %d\n", car->id + 1, val);
    }
    //if (countdown(1))
    //   print_cars(cbox);//print_timeline(cbox);
}

void		ft_live(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LIVE_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}