//
// Created by Dacey mormont Jon connington on 21/12/2019.
//

#include "corewar.h"

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int val1;
	int val2;
	int value;
	int reg;

	val1 = get_int_from_arg(car, cbox, args[0]);
	val2 = get_int_from_arg(car, cbox, args[1]);
	value = val1 & val2;
	reg = args[2].value;
	car->regs[REG(reg)] = value;
	if (value == 0)
		car->carry = 1;
	else
		car->carry = 0;
}

void		ft_and(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = AND_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, logical_validate_permitted_types);
}

/// TESTS

/// reg test

//static void test_init(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	//offset
//	i = 15;
//
//	//command_code
//	arr[i++] = AND_COMMAND_CODE;
//
//	//arg_types
//	arr[i++] = 0b01010100;
//
//	//t_reg
//	arr[i++] = 3;
//
//	//t_reg
//	arr[i++] = 4;
//
//	//t_reg
//	arr[i++] = 5;
//
//}

/// dir test

//static void test_init(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	//offset
//	i = 15;
//
//	//command_code
//	arr[i++] = AND_COMMAND_CODE;
//
//	//arg_types
//	arr[i++] = 0b10100100;
//
//	//t_dir
//	arr[i++] = 0;
//	arr[i++] = 0;
//	arr[i++] = 0;
//	arr[i++] = 22;
//
//	//t_dir
//	arr[i++] = 0;
//	arr[i++] = 0;
//	arr[i++] = 0;
//	arr[i++] = 15;
//
//	//t_reg
//	arr[i++] = 5;
//
//}

/// ind test

//static void test_init(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	i = 15;
//	//command_code
//	arr[i++] = AND_COMMAND_CODE;
//
//	//arg_types
//	arr[i++] = 0b11010100; //t-dir + t-reg
//
//	//t_indir
//	arr[i++] = -3 >> 8;
//	arr[i++] = -3;
//
//	//t_reg
//	arr[i++] = 6;
//
//	//t_reg
//	arr[i++] = 4;
//
//	arr[21] = 88;
//}
//
//int		main(int argc, char **argv)
//{
//	size_t 		i;
//	int 		n;  // number of players
//	t_cbox		cbox;  // corewar-box: champions, arena, timeline
//
//	ft_printf("\n{RED}ADD TEST\n\n");
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
//	testcar.regs[3] = 22;
//	testcar.regs[5] = -1;
//	testcar.id = 0;
//	testcar.oper = get_operation(AND_COMMAND_CODE);
//
//	testcar.oper.f(&testcar, &cbox);
//
//	return (clean_all(&cbox, SUCCESS));
//}