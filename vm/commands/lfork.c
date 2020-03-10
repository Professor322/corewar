//
// Created by Миняйлов Дмитрий Владимирович on 24.01.2020.
//

#include "corewar.h"
//TODO TO BE DONE
static int set_types(t_arg *args)
{
    return 1;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
}

void		ft_lfork(t_car *car, t_cbox *cbox)
{
    t_carbox carbox;

    carbox.cbox = cbox;
    carbox.car = car;
    carbox.op_command_code = LFORK_COMMAND_CODE;
    exec_command(&carbox, op_unique_commands, set_types);
}