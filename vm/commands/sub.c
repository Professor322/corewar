//
// Created by Dacey mormont Jon connington on 21/12/2019.
//

#include "corewar.h"

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int reg1;
	int reg2;
	int reg3;

	reg1 = args[0].value;
	reg2 = args[1].value;
	reg3 = args[2].value;
	car->regs[REG(reg3)] = car->regs[REG(reg1)] - car->regs[REG(reg2)];
	cbox = cbox;
}

void		ft_sub(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = SUB_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, sub_add_validate_permitted_types);
}

////// TESTS

///reg test

//static void test_init(t_cbox *cbox)
//{
//	unsigned char *arr = cbox->arena.arena;
//	int i = 0;
//
//	//offset
////	i = 15;
//
//	//command_code
//	arr[i++] = SUB_COMMAND_CODE;
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
//
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
//	testcar.pos = 0;
//	testcar.carry = 0;
//	for (int j = 0; j < REG_NUMBER; ++j)
//		testcar.regs[j] = 0;
//	testcar.regs[2] = 15;
//	testcar.regs[3] = 22;
//	testcar.regs[4] = 100;
//	testcar.id = 0;
//	testcar.oper = get_operation(SUB_COMMAND_CODE);
//
//	testcar.oper.f(&testcar, &cbox);
//
//	return (clean_all(&cbox, SUCCESS));
//}