//
// Created by Миняйлов Дмитрий Владимирович on 21.01.2020.
//

#include "corewar.h"

static int validate_permitted_types(t_arg *args)
{
    if ((args[0].type == REG || args[0].type == DIR || args[0].type == IND)
        &&
        (args[1].type == REG || args[1].type == DIR)
        &&
        args[2].type == REG
        &&
        args[3].type == NONE)
        return 1;
    return 0;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
    int		reg;
    int		val1;
    int		val2;

    val1 = get_int_from_arg(car, cbox, args[0]);
    val2 = get_int_from_arg(car, cbox, args[1]);
    reg = args[2].value;
    car->regs[REG(reg)] = get_int_from_bytes(cbox->arena.arena, car->pos + IND_OFFSET(val1 + val2), REG_SIZE);
    if (car->regs[REG(reg)] == 0)
        car->carry = 1;
    else
        car->carry = 0;
}

void ft_ldi(t_car *car, t_cbox *cbox)
{
    t_carbox carbox;

    carbox.cbox = cbox;
    carbox.car = car;
    carbox.op_command_code = LDI_COMMAND_CODE;
    exec_command(&carbox, op_unique_commands, validate_permitted_types);
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