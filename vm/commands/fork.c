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

    //print_cars(cbox); print_eventloop(cbox);

    new_car = fetch_free_car(cbox);
    clone_car(old_car, new_car);
    new_car->id = cbox->car_counter;
    cbox->car_counter += 1;

    value = get_int_from_arg(old_car, cbox, args[0]);
    new_car->pos = new_car->pos + IND_OFFSET(value);

//    new_car->oper = get_operation(cbox->arena.arena[POS(new_car->pos)]);
    //old_car->oper = get_operation(cbox->arena.arena[new_car->pos]);
    //reschedule_car(cbox, new_car, get_operation(FORK_COMMAND_CODE).delay);
//    reschedule_car(cbox, new_car, new_car->oper.delay);

    ft_bzero(&new_car->oper, sizeof(t_oper)); // ??
    // set new operation will be in next turn
    reschedule_car(cbox, new_car, 1);

    if (cbox->flags & V_FLAG_OPER) {
        ft_printf("P % 4lu | fork %d (%d)\n", old_car->id + 1, value, new_car->pos);
    }
    //ft_printf("\t\tfork: car=%d -> new=%d\n", old_car->id, new_car->id);
    //print_cars(cbox); print_eventloop(cbox);
    //print_eventloop(cbox);
}

void		ft_fork(t_car *car, t_cbox *cbox)
{
    t_carbox carbox;

    carbox.cbox = cbox;
    carbox.car = car;
    carbox.op_command_code = FORK_COMMAND_CODE;
    exec_command(&carbox, op_unique_commands, set_types);
}