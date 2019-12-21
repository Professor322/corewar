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

static int	get_arg_size(t_arg_type type)
{
	return get_default_arg_size(type);
}

void ld(t_car *car, t_cbox *cbox)
{
	t_arg	args[CW_MAX_ARGS];
	t_arg	reg;
	int		val;
	t_carbox	carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	if (!validate_command_byte(car, cbox, LD_COMMAND_CODE))
	{
		car->pos = POS(car->pos + 1);
		return ;
	}
	if (prepare_arguments(carbox, args, get_arg_size, validate_permitted_types))
	{
		if (args[0].type == IND)
			val = get_int_from_bytes(cbox->arena.arena, car->pos + IND_OFFSET(args[0].value), REG_SIZE);
		else
			val = args[0].value;
		reg = args[1];
		car->regs[REG(reg.value)] = val;
		if (reg.value == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
	move_car(car, args);
}



////// TESTS
///*
// * TEST MAIN
// */
//
//static void ld_init_dir(t_cbox *cbox)
//{
//	char *arr = cbox->arena.arena;
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
//
//static void ld_init_indir(t_cbox *cbox)
//{
//	char *arr = cbox->arena.arena;
//	int i = 0;
//
//	i = 15;
//	//command_code
//	arr[i++] = 2;
//
//	//arg_types
//	arr[i++] = 0b11010000; //t-dir + t-reg
//
//	//t_indir
//	arr[i++] = 517 >> 8;
//	arr[i++] = 517;
//
//	//t_reg
//	arr[i++] = 4;
//
//	arr[20] = 88;
//}
//
//int		main(int argc, char **argv)
//{
//	size_t 		i;
//	int 		n;  // number of players
//	t_cbox		cbox;  // corewar-box: champions, arena, timeline
//
//	ft_printf("\n{RED}LD TEST\n\n");
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
//	ld_init_indir(&cbox);
//	dump_arena(cbox.arena.arena);
//
//	t_car testcar;
//
//	testcar.pos = 15;
//	testcar.carry = 0;
//	for (int j = 0; j < REG_NUMBER; ++j)
//		testcar.regs[j] = 0;
//	testcar.id = 0;
//	testcar.oper = get_operation(2);
//
//	testcar.oper.f(&testcar, &cbox);
//
//	return (clean_all(&cbox, SUCCESS));
//}