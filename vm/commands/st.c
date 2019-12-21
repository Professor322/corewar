//
// Created by Cricun on 18.12.2019.
//

#include "corewar.h"

static int validate_permitted_types(t_arg *args)
{
	if (args[0].type == REG
		&&
		(args[1].type == REG || args[1].type == IND)
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

static		void write_value(unsigned char *arr, unsigned int pos, unsigned int val)
{
	arr[pos++] = val >> 24;
	arr[pos++] = val >> 16;
	arr[pos++] = val >> 8;
	arr[pos] = val;
}

void 		st(t_car *car, t_cbox *cbox)
{
	t_arg	args[CW_MAX_ARGS];
	t_arg	param;
	int		val;
	t_carbox	carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	if (!validate_command_byte(car, cbox, ST_COMMAND_CODE))
	{
		car->pos = POS(car->pos + 1);
		return ;
	}
	if (prepare_arguments(carbox, args, get_arg_size, validate_permitted_types))
	{
		param = args[1];
		val = car->regs[REG(args[0].value)];
		if (param.type == REG)
			car->regs[REG(param.value)] = val;
		else // IND
			write_value(cbox->arena.arena, car->pos + IND_OFFSET(param.value), val);
	}
	move_car(car, args);
}


////// TESTS
///*
// * TEST MAIN
// */
//

static void st_init_reg(t_cbox *cbox)
{
	char *arr = cbox->arena.arena;
	int i = 0;

	//command_code
	arr[i++] = 3;

	//arg_types
	arr[i++] = 0b01010000; //t-dir + t-reg

	//t_reg
	arr[i++] = 8;
//	arr[i++] = 517;

	//t_reg
	arr[i] = 4;

	arr[20] = 88;
}

static void st_init_ind(t_cbox *cbox)
{
	char *arr = cbox->arena.arena;
	int i = 0;

	//command_code
	arr[i++] = 3;

	//arg_types
	arr[i++] = 0b01110000; //t-dir + t-reg

	//t_reg
	arr[i++] = 8;

	//t_ind
	arr[i++] = 2410 >> 8;
	arr[i] = 2410;

}

int		main(int argc, char **argv)
{
	size_t 		i;
	int 		n;  // number of players
	t_cbox		cbox;  // corewar-box: champions, arena, timeline

	ft_printf("\n{RED}LD TEST\n\n");

	ft_bzero(&cbox, sizeof(t_cbox));
	i = 0;
	n = 0;
	while (++i < argc)
		if (argv[i][0] != '-' && ++n)
			get_champion(argv[i], &cbox.champs[i - 1], i, &cbox);

	greet_champions(cbox.champs, MAX_PLAYERS);

	init_timeline(&cbox);

	init_arena(n, &cbox);
//	dump_arena(cbox.arena.arena);

	st_init_ind(&cbox);
	dump_arena(cbox.arena.arena);

	t_car testcar;

	testcar.pos = 0;
	testcar.carry = 0;
	for (int j = 0; j < REG_NUMBER; ++j)
		testcar.regs[j] = 0;
	testcar.id = 0;
	testcar.oper = get_operation(3);

	testcar.oper.f(&testcar, &cbox);
	dump_arena(cbox.arena.arena);
	return (clean_all(&cbox, SUCCESS));
}