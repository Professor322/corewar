//
// Created by Dacey mormont Jon connington on 21/12/2019.
//

#include "corewar.h"

static int set_types(t_arg *args)
{
	args[0].type = DIR;
	args[0].size = get_operation(ZJMP_COMMAND_CODE).t_dir_size;
	args[1].type = NONE;
	args[2].type = NONE;
	args[3].type = NONE;
	return 1;
}

static void	op_unique_commands(t_car *car, t_cbox *cbox, t_arg args[CW_MAX_ARGS])
{
	int val1;

	val1 = get_int_from_arg(car, cbox, args[0]);
	if (car->carry == 1)
		car->pos = car->pos + IND_OFFSET(val1);
    if (cbox->flags & V_FLAG_CHECK) {
        if (car->carry == 1)
            ft_printf("P% 5lu | zjmp %d OK\n", car->id + 1, val1);
        else
            ft_printf("P% 5lu | zjmp %d FAILED\n", car->id + 1, val1);
    }
    //if (countdown(1))
      //  print_cars(cbox);//print_timeline(cbox);
}

void		ft_zjmp(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = ZJMP_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, set_types);
}

/// TESTS

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
//	arr[i++] = ZJMP_COMMAND_CODE;
//
//	//arg_types
////	arr[i++] = 0b10100100;
//
//	//t_dir
//	arr[i++] = 0;
//	arr[i++] = 22;
//
//	//t_dir
////	arr[i++] = 0;
////	arr[i++] = 0;
////	arr[i++] = 0;
////	arr[i++] = 15;
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
//	testcar.carry = 1;
//	for (int j = 0; j < REG_NUMBER; ++j)
//		testcar.regs[j] = 0;
//	testcar.regs[3] = 22;
//	testcar.regs[5] = -1;
//	testcar.id = 0;
//	testcar.oper = get_operation(ZJMP_COMMAND_CODE);
//
//	testcar.oper.f(&testcar, &cbox);
//
//	return (clean_all(&cbox, SUCCESS));
//}