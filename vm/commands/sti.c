//
// Created by Миняйлов Дмитрий Владимирович on 21.01.2020.
//

#include "corewar.h"

// TODO to be tested

static int validate_permitted_types(t_arg *args)
{
	if (args[0].type == REG
		&&
		(args[1].type == REG || args[1].type == DIR || args[1].type == IND)
		&&
        (args[2].type == REG || args[2].type == DIR)
        &&
		args[3].type == NONE)
		return 1;
	return 0;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
    int     val0;
    int		val1;
    int		val2;

    val0 = get_int_from_arg(car, cbox, args[0]);
    val1 = get_int_from_arg(car, cbox, args[1]);
    val2 = get_int_from_arg(car, cbox, args[2]);
    write_int_to_bytes(cbox->arena.arena, car->pos + IND_OFFSET(val1 + val2), val0);
    //dprintf(get_fd_debug(), "P% 5lu | sti r%d %d %d\n", car->id + 1, 1, val1, val2);
    if (cbox->flags & V_FLAG_CHECK) {
        ft_printf("P% 5lu | sti r%d %d %d\n", car->id + 1, args[0].value, val1, val2);
        ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n"
                , val1, val2, IND_OFFSET(val1 + val2), car->pos + IND_OFFSET(val1 + val2));
    }
}

void 		ft_sti(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = STI_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}


////// TESTS
///*
// * TEST MAIN
// */
//

///reg test

//static void st_init_reg(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	//command_code
//	arr[i++] = ST_COMMAND_CODE;
//
//	//arg_types
//	arr[i++] = 0b01010000; //t-dir + t-reg
//
//	//t_reg
//	arr[i++] = 8;
////	arr[i++] = 517;
//
//	//t_reg
//	arr[i] = 4;
//
//	arr[20] = 88;
//}

/// ind test

//static void test_init(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	//command_code
//	arr[i++] = ST_COMMAND_CODE;
//
//	//arg_types
//	arr[i++] = 0b01110000; //t-dir + t-reg
//
//	//t_reg
//	arr[i++] = 8;
//
//	//t_ind
//	arr[i++] = 2410 >> 8;
//	arr[i] = (unsigned char)2410;
//
//}

//int		main(int argc, char **argv)
//{
//	size_t 		i;
//	int 		n;  // number of players
//	t_cbox		cbox;  // corewar-box: champions, arena, timeline
//
//	ft_printf("\n{RED}ST TEST\n\n");
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
//	test_init(&cbox);
//	dump_arena(cbox.arena.arena);
//
//	t_car testcar;
//
//	testcar.pos = 0;
//	testcar.carry = 0;
//	for (int j = 0; j < REG_NUMBER; ++j)
//		testcar.regs[j] = 0;
//	testcar.id = 0;
//	testcar.oper = get_operation(ST_COMMAND_CODE);
//
//	testcar.oper.f(&testcar, &cbox);
//	dump_arena(cbox.arena.arena);
//	return (clean_all(&cbox, SUCCESS));
//}