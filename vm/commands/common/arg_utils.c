#include "corewar.h"

void	move_car(t_car *car, t_arg *args)
{
	int i;

	i = 0;
	car->pos += OP_BYTE_OFFSET;
	car->pos += car->oper.has_type_byte;
	while (i < CW_MAX_ARGS)
	{
		if (args[i].type)
			car->pos += args[i].size;
		i++;
	}
	car->pos = POS(car->pos);
}

int		get_default_arg_size(t_arg_type type)
{
	if (type == NONE)
		return (0);
	else if (type == REG)
		return (T_REG_BYTE_SIZE);
	else if (type == DIR)
		return (T_DIR_BYTE_SIZE);
	else if (type == IND)
		return (T_IND_BYTE_SIZE);
	else
		ft_printf("WRONG ARGUMENT TYPE\n");
	return (0);
}

int		get_int_from_bytes(unsigned char *arr, unsigned int pos, int size)
{
	char	c;
	short	s;
	int		i;

	if (size == 1)
	{
		c = arr[POS(pos)];
		return (c);
	}
	if (size == 2)
	{
		s = ((short)arr[POS(pos)]) << 8 | ((short)arr[POS(pos + 1)]);
		return (s);
	}
	if (size == 4)
	{
		i = ((int)arr[POS(pos)]) << 24
			| ((int)arr[POS(pos + 1)]) << 16
			| ((int)arr[POS(pos + 2)]) << 8
			| ((int)arr[POS(pos + 3)]);
		return (i);
	}
	ft_printf("INT TO BYTES CONVERSTION FAILED\n");
	exit(-42); // todo: unsafe exit
}

int		get_int_from_arg(t_car *car, t_cbox *cbox, t_arg arg)
{
	if (arg.type == IND)
		return (get_int_from_bytes(cbox->arena.arena,
				car->pos + IND_OFFSET(arg.value), REG_SIZE));
	else if (arg.type == DIR)
		return (arg.value);
	else if (arg.type == REG)
		return (car->regs[REG(arg.value)]);
	else
		return (0);
}
