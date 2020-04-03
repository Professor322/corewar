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
    args[2].type = NONE;
    args[3].type = NONE;
    return 1;
}

static void	op_unique_commands(t_car *old_car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
    t_car *new_car;
    int value;

    //print_cars(cbox); print_timeline(cbox);

    new_car = fetch_free_car(cbox);
    clone_car(old_car, new_car);
    new_car->id = cbox->car_counter;
    cbox->car_counter += 1;

    value = get_int_from_arg(old_car, cbox, args[0]);
    new_car->pos += IND_OFFSET(value);

    new_car->oper = get_operation(cbox->arena.arena[new_car->pos]);
    //reschedule_car(cbox, new_car, get_operation(FORK_COMMAND_CODE).delay);
    reschedule_car(cbox, new_car, new_car->oper.delay);
    if (cbox->flags & V_FLAG_CHECK) {
        ft_printf("P% 5lu | fork %d (%d)\n", old_car->id + 1, value, new_car->pos);
    }
    //ft_printf("\t\tfork: car=%d -> new=%d\n", old_car->id, new_car->id);
    //print_cars(cbox); print_timeline(cbox);
}

void		ft_fork(t_car *car, t_cbox *cbox)
{
    t_carbox carbox;

    carbox.cbox = cbox;
    carbox.car = car;
    carbox.op_command_code = FORK_COMMAND_CODE;
    exec_command(&carbox, op_unique_commands, set_types);
}

////// TESTS


/// reg test
//
//static void test_init(t_cbox *cbox, t_car * testcar)
//{
//	unsigned char *arr = cbox->arena.arena;
//
//    testcar->pos = 15;
//    int i = testcar->pos;
//    testcar->carry = 0;
//    for (int j = 0; j < REG_NUMBER; ++j)
//        testcar->regs[j] = 0;
//    testcar->id = 0;
//    testcar->oper = get_operation(LDI_COMMAND_CODE);
//
//	//command_code
//	arr[i++] = LDI_COMMAND_CODE;
//
//	//arg_types
//	arr[i++] = 0b01010100; //t-reg + t-reg + t-reg
//
//	//t_reg
//	arr[i++] = 4;
//	testcar->regs[3] = 10;
//
//    //t_reg
//    arr[i++] = 8;
//    testcar->regs[7] = 22;
//
//    //t_reg
//    arr[i++] = 16;
//    testcar->regs[15] = 34;
//
//
//
//    i = testcar->pos + testcar->regs[3] + testcar->regs[7];
//    arr[i++] = 0;
//    arr[i++] = 0;
//    arr[i++] = 0;
//    arr[i++] = 88;
//
//}
//
//
//int		main(int argc, char **argv)
//{
//	size_t 		i;
//	int 		n;  // number of players
//	t_cbox		cbox;  // corewar-box: champions, arena, timeline
//
//	ft_printf("\n{RED}LDI TEST\n\n");
//
//	ft_bzero(&cbox, sizeof(t_cbox));
//	i = 0;
//	n = 0;
//	while (++i < argc)
//		if (argv[i][0] != '-' && ++n)
//			get_champion(argv[i], &cbox.champs[i - 1], i, &cbox);
//
//	greet_champions(cbox.champs, MAX_PLAYERS);
//
//	init_timeline(&cbox);
//
//	init_arena(n, &cbox);
////	dump_arena(cbox.arena.arena);
//
//    t_car testcar;
//    test_init(&cbox, &testcar);
//    dump_arena(cbox.arena.arena);
//    ft_printf("\n\n\n\n\n");
//
//	testcar.oper.f(&testcar, &cbox);
//
//	return (clean_all(&cbox, SUCCESS));
//}