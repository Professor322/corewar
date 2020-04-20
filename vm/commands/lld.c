//
// Created by Cricun on 11.12.2019.
//

#include "corewar.h"

static int validate_permitted_types(t_arg *args)
{
	if ((args[0].type == DIR || args[0].type == IND)
		&&
		args[1].type == REG
		&&
		args[2].type == NONE
		&&
		args[3].type == NONE)
		return 1;
	return 0;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int		reg;
	int		val0;

	if (args[0].type == IND)
        val0 = get_int_from_bytes(cbox->arena.arena, car->pos + args[0].value, REG_SIZE);
	else
	    val0 = get_int_from_arg(car, cbox, args[0]);
    reg = args[1].value;
    car->regs[REG(reg)] = val0;
	if (val0 == 0)
		car->carry = 1;
	else
		car->carry = 0;
    if (cbox->flags & V_FLAG_OPER)
        ft_printf("P % 4lu | lld %d r%d\n", car->id + 1, val0, reg);
}

void ft_lld(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LLD_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}


////// TESTS
///*
// * TEST MAIN
// */

/// dir test

//static void test_init(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	//command_code
//	arr[i++] = 2;
//
//	//arg_types
//	arr[i++] = 0b10010000; //t-dir + t-reg
//
//	//t_dir
//	arr[i++] = 0;
//	arr[i++] = 0;
//	arr[i++] = 0;
//	arr[i++] = 42;
//
//	arr[43] = 88;
//
//	//t_reg
//	arr[i++] = 4;
//
//}

/// ind test

static void test_init(t_cbox *cbox)
{
	unsigned char *arr = cbox->arena.arena;
	int i = 0;

	i = 15;
	//command_code
	arr[i++] = LLD_COMMAND_CODE;

	//arg_types
	arr[i++] = 0b11010000;

	//t_indir
	arr[i++] = 17 >> 8;
	arr[i++] = 17;

	//t_reg
	arr[i++] = 4;


	i = 15 + 17;
    arr[i++] = 0;
    arr[i++] = 0;
    arr[i++] = 0;
    arr[i++] = 88;
}

//int		main(int argc, char **argv)
//{
//	size_t 		i;
//	int 		n;  // number of players
//	t_cbox		cbox;  // corewar-box: champions, arena, timeline
//
//	ft_printf("\n{RED}LLD TEST\n\n");
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
//	ft_printf("\n\n\n\n\n");
//	t_car testcar;
//
//	testcar.pos = 15;
//	testcar.carry = 0;
//	for (int j = 0; j < REG_NUMBER; ++j)
//		testcar.regs[j] = 0;
//	testcar.id = 0;
//	testcar.oper = get_operation(LLD_COMMAND_CODE);
//
//	testcar.oper.f(&testcar, &cbox);
//
//	return (clean_all(&cbox, SUCCESS));
//}