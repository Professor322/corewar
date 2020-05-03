//
// Created by Cricun on 11.12.2019.
//

#include "corewar.h"

void	 move_car(t_car *car, t_arg *args)
{
	int i;

	i = 0;
	car->pos += OP_BYTE_OFFSET;
//    ft_printf("moving offset byte 1\n");
	car->pos += car->oper.has_type_byte;
//    ft_printf("moving type byte %d\n", car->oper.has_type_byte);
	while (i < CW_MAX_ARGS)
	{
		if (args[i].type)
			car->pos += args[i].size;
//		ft_printf("moving bytes %d\n", args[i].size);
		i++;
	}
	car->pos = POS(car->pos);
}

int		get_default_arg_size(t_arg_type type)
{
	if (type == NONE)
		return 0;
	else if (type == REG)
		return T_REG_BYTE_SIZE;
	else if (type == DIR)
		return T_DIR_BYTE_SIZE;
	else if (type == IND)
		return T_IND_BYTE_SIZE;
	else
		ft_printf("WRONG ARGUMENT TYPE\n");
	return 0;
}

int		prepare_arguments(t_carbox *carbox,
		t_arg args[CW_MAX_ARGS],
		int (*validate_permitted_types)(t_arg*))
{
	if (carbox->car->oper.has_type_byte)
	{
		cw_get_arg_types(carbox->car, carbox->cbox, args);
		if (!validate_permitted_types(args))
			return 0;
	}
	else
	{
		validate_permitted_types(args); // set default types
	}
	if (!get_arg_values(carbox->car, carbox->cbox, args))
		return 0;
	return 1;
}

int		get_arg_size(t_car *car, t_arg_type type)
{
	if (type == DIR)
		return car->oper.t_dir_size;
	else
		return get_default_arg_size(type);
}

void	cw_get_arg_types(t_car *car, t_cbox *cbox, t_arg *args)
{
	unsigned int i;
	unsigned char byte;

//	ft_printf("started getting arg types");
	byte = cbox->arena.arena[POS(car->pos + OP_BYTE_OFFSET)];
	i = 0;
	while (i < CW_MAX_ARGS) {
	    if (i < car->oper.args_amount)
        {
            args[i].type = byte >> ((CW_MAX_ARGS - i - 1) * 2) & 0b11;
            args[i].size = get_arg_size(car, args[i].type);
        }
	    else
        {
            args[i].type = 0;
            args[i].size = 0;
        }
//		ft_printf("arg type: %d, arg size: %d\n", args[i].type, args[i].size);
//      ft_printf("%d %d\n",car->oper.args_amount, CW_MAX_ARGS);
        i++;
	}
}

int     get_fd_debug(void)
{
    static int fdd;

    if (fdd == 0) {
        fdd = open("debug.txt", O_WRONLY | O_CREAT, 0644);
        if (fdd == -1) {
            ft_printf("get_fd_debug - FAILED\n");
            exit(1);
        }
    }
    return fdd;
}

int		get_int_from_bytes(unsigned char *arr, unsigned int pos, int size)
{
	char 	c;
	short	s;
	int		i;
    //dprintf(get_fd_debug(), "pos =%u\tsize=%d\n", pos, size);
	if (size == 1)
	{
		c = arr[POS(pos)];
		return c;
	}
	if (size == 2)
	{
		s = ((short)arr[POS(pos)]) << 8 | ((short)arr[POS(pos + 1)]);
		return s;
	}
	if (size == 4)
	{
		i = ((int)arr[POS(pos)]) << 24
			| ((int)arr[POS(pos + 1)]) << 16
			| ((int)arr[POS(pos + 2)]) << 8
			| ((int)arr[POS(pos + 3)]);
		return i;
	}
    dprintf(get_fd_debug(), "Failed");
	ft_printf("INT TO BYTES CONVERSTION FAILED\n");
    //ft_printf("arr =%s\n");
    //ft_printf("pos =%u\nsize=%d\n");
	exit(-42);
}

int 	get_int_from_arg(t_car *car, t_cbox *cbox, t_arg arg)
{
	if (arg.type == IND)
		return get_int_from_bytes(cbox->arena.arena, car->pos + IND_OFFSET(arg.value), REG_SIZE);
	else if (arg.type == DIR )
		return arg.value;
	else if (arg.type == REG)
		return car->regs[REG(arg.value)];
	else
		return 0;
}

int		get_arg_values(t_car *car, t_cbox *cbox, t_arg *args)
{
	unsigned char	*arr;
	unsigned int	arg_i;
	unsigned int 	arr_i;

	arg_i = 0;
	arr_i = car->oper.has_type_byte + OP_BYTE_OFFSET;
	arr = cbox->arena.arena;

	while (arg_i < CW_MAX_ARGS && args[arg_i].type != NONE)
	{
		args[arg_i].value = get_int_from_bytes(arr, car->pos + arr_i, args[arg_i].size);
		arr_i += args[arg_i].size;
		if (args[arg_i].type == REG && !valid_reg_number(args[arg_i].value))
		{
			//todo remove printf before release
			//ft_printf("BAD REG NUMBER\n");
			return 0;
		}
		arg_i++;
	}
	return 1;
}

int		validate_command_byte(t_carbox *carbox)
{
	unsigned char c;

	c = carbox->cbox->arena.arena[POS(carbox->car->pos)];
	return c == carbox->op_command_code;
}

// value is real number of champion (1, 2, .. )
int		validate_user(t_cbox *cbox, int value)
{
	if (value <= 0 || value > MAX_PLAYERS)
		return 0;
	if (cbox->champs[value - 1].code_size)
	    return 1;
	return 0;
}

void	exec_command(t_carbox *carbox,
		void (*op_unique_commands)(t_car*, t_cbox*, t_arg[CW_MAX_ARGS]),
		int (*validate_permitted_types)(t_arg*))
{
	t_arg		args[CW_MAX_ARGS];

//	ft_printf("command %d\n", carbox->op_command_code);

//	if (!validate_command_byte(carbox))
//	{
//		carbox->car->pos = POS(carbox->car->pos + 1);
//		return ;
//	}
	if (prepare_arguments(carbox, args, validate_permitted_types))
		op_unique_commands(carbox->car, carbox->cbox, args);
	if (carbox->car->oper.f != ft_zjmp || carbox->car->carry != 1)
	    move_car(carbox->car, args);
}


void	write_int_to_bytes(unsigned char *arr, unsigned int pos, unsigned int val)
{
	arr[POS(pos++)] = val >> 24;
	arr[POS(pos++)] = val >> 16;
	arr[POS(pos++)] = val >> 8;
	arr[POS(pos)] = val;
}

void    print_cars(t_cbox *cbox) {
    int idx;

    ft_printf("🏎️  🏎  ️🏎️\n");
    idx = -1;
    while (++idx < cbox->car_counter) {
        print_car(((t_car **) cbox->cars->cont)[idx]);
    }
}

void    print_eventloop(t_cbox *cbox) {
    int idx;
    int cycle;
    int delta;

    cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
    ft_printf("⏱️  = %d\n", cycle);
    idx = -1;
    while (++idx < SIZE_OF_EVENTLOOP) {
        if (cbox->eventloop[idx]->len) {
            if (idx < cycle)
                delta = SIZE_OF_EVENTLOOP - cycle + idx;
            else
                delta = idx - cycle;
            ft_printf("idx = %3d [%3d]\tcont= %d --- ", delta, idx, cbox->eventloop[idx]->len/sizeof(t_pque));
            print_car_without_reg(((t_car **) cbox->eventloop[idx]->cont)[0]);
            ft_printf("\n");
        }
    }
}

void    print_cur_eventloop(t_cbox *cbox) {
    int idx;
    int cycle;
    int car;
    int delta;

    cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
    ft_printf("⏳  = %d\n", cycle);
    idx = -1;
    while (++idx < SIZE_OF_EVENTLOOP) {
        if (cbox->eventloop[idx]->len) {
            if (idx < cycle)
                delta = SIZE_OF_EVENTLOOP - cycle + idx;
            else
                delta = idx - cycle;
            car = -1;
            while (++car < cbox->eventloop[idx]->len/sizeof(t_pque)) {
                if (((t_car *) (((t_pque *) cbox->eventloop[idx]->cont)[car].data))->id == 546) {
                    ft_printf("idx = %3d [%3d]\tcont= %d --- ", delta, idx, cbox->eventloop[idx]->len/sizeof(t_pque));
                    print_car_without_reg(((t_pque *) cbox->eventloop[idx]->cont)[car].data);
                    ft_printf("\n");
                }
            }
        }
    }
}

void    print_full_eventloop(t_cbox *cbox) {
	int idx;
	int cycle;
	int delta;
	int car;

	cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
	ft_printf("⏱️  = %d\n", cycle);
	idx = -1;
	while (++idx < SIZE_OF_EVENTLOOP) {
		if (cbox->eventloop[idx]->len) {
			if (idx < cycle)
				delta = SIZE_OF_EVENTLOOP - cycle + idx;
			else
				delta = idx - cycle;
			car = -1;
			while (++car < cbox->eventloop[idx]->len/sizeof(t_pque)) {
				ft_printf("idx = %3d [%3d]\tcont= %d --- ", delta, idx, cbox->eventloop[idx]->len/sizeof(t_pque));
				print_car_without_reg(((t_pque *) cbox->eventloop[idx]->cont)[car].data);
				ft_printf("\n");
			}
			ft_printf("\n");
		}
	}
}

int     countdown(int setup) {
    static int count;
    static int unset;
    if (unset == 0) {
        unset = 1;
        count = setup;
    }
    if (count > 0) {
        count--;
        return 0;
    }
    return 1;

}

void print_bytes(t_cbox *cbox, t_car *car, int bytes_amount)
{
	unsigned char *arena = cbox->arena.arena;
	int pos = car->pos;
	ft_printf("car pos %d\n", pos);
	for (int j = 0; j < bytes_amount; j++)
	{
		ft_printf("%.2x ", arena[pos +  j]);
	}
	ft_printf("\n");
}
