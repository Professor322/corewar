//
// Created by Cricun on 21.01.2020.
//

#include "corewar.h"

static int set_types(t_arg *args)
{
    args[0].type = REG;
    args[0].size = get_default_arg_size(REG);
    args[1].type = NONE;
    args[2].type = NONE;
    args[3].type = NONE;
    return 1;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
    int val1;

    val1 = get_int_from_arg(car, cbox, args[0]);
    // no ft_printf ?
}

void		ft_aff(t_car *car, t_cbox *cbox)
{
    t_carbox carbox;

    carbox.cbox = cbox;
    carbox.car = car;
    carbox.op_command_code = AFF_COMMAND_CODE;
    exec_command(&carbox, op_unique_commands, set_types);
}



////// TESTS
///*
// * TEST MAIN
// */

//static void test_init(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	//offset
//	i = 15;
//
//	//command_code
//	arr[i++] = AFF_COMMAND_CODE;
//
//	//arg_types
//	arr[i++] = 0b01000000;
//
//	//t_reg
//	arr[i++] = 5;
//
//	//t_reg
////	arr[i++] = 4;
//
//	//t_reg
////	arr[i++] = 5;
//
//}
//
//int		main(int argc, char **argv)
//{
//	size_t 		i;
//	int 		n;  // number of players
//	t_cbox		cbox;  // corewar-box: champions, arena, timeline
//
//	ft_printf("\n{RED}AFF TEST\n\n");
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
//    test_init(&cbox);
//	dump_arena(cbox.arena.arena);
//	ft_printf("\n\n\n\n\n");
//	t_car testcar;
//
//	testcar.pos = 15;
//	testcar.carry = 0;
//	for (int j = 0; j < REG_NUMBER; ++j)
//		testcar.regs[j] = 0;
//	testcar.id = 0;
//	testcar.regs[4] = 'k';
//    ft_printf("\n\n\n\n\n");
//    ft_printf("\n\n\n\n\n");
//    ft_printf("\n\n\n\n\n");
//
//    testcar.oper = get_operation(AFF_COMMAND_CODE);
//
//	testcar.oper.f(&testcar, &cbox);
//
//	return (clean_all(&cbox, SUCCESS));
//}