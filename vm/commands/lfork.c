//
// Created by Миняйлов Дмитрий Владимирович on 24.01.2020.
//

#include "corewar.h"
//TODO TO BE TESTED

static int set_types(t_arg *args)
{
    args[0].type = DIR;
    args[0].size = get_operation(FORK_COMMAND_CODE).t_dir_size;
    args[1].type = NONE;
    args[1].size = 0;
    args[2].type = NONE;
    args[2].size = 0;
    args[3].type = NONE;
    args[3].size = 0;
    return 1;
}

static void	op_unique_commands(t_car *old_car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
    t_car *new_car;
    int value;

    value = get_int_from_arg(old_car, cbox, args[0]);
    new_car = fetch_free_car(cbox);
    clone_car(old_car, new_car);
    new_car->id = cbox->car_counter;
    cbox->car_counter += 1;
    new_car->pos = new_car->pos + value;
    new_car->oper = get_operation(cbox->arena.arena[POS(new_car->pos)]);
    reschedule_car(cbox, new_car, new_car->oper.delay);
    if (cbox->flags & V_FLAG_CHECK) {
        ft_printf("P % 4lu | lfork %d (%d)\n", old_car->id + 1, value, new_car->pos);
    }
}

void		ft_lfork(t_car *car, t_cbox *cbox)
{
    t_carbox carbox;

    carbox.cbox = cbox;
    carbox.car = car;
    carbox.op_command_code = LFORK_COMMAND_CODE;
    exec_command(&carbox, op_unique_commands, set_types);
}