
#include "corewar.h"

/*
** value is real number of champion (1, 2, .. )
*/

int		validate_user(t_cbox *cbox, int value)
{
	if (value <= 0 || value > MAX_PLAYERS)
		return (0);
	if (cbox->champs[value - 1].code_size)
		return (1);
	return (0);
}

void	exec_command(t_carbox *carbox,
				void (*op_unique_commands)(t_car*, t_cbox*, t_arg[CW_MAX_ARGS]),
				int (*validate_permitted_types)(t_arg*))
{
	t_arg		args[CW_MAX_ARGS];

	if (prepare_arguments(carbox, args, validate_permitted_types))
		op_unique_commands(carbox->car, carbox->cbox, args);
	if (carbox->car->oper.f != ft_zjmp || carbox->car->carry != 1)
		move_car(carbox->car, args);
}

void	write_int_to_bytes(unsigned char *arr,
							unsigned int pos,
							unsigned int val)
{
	arr[POS(pos++)] = val >> 24;
	arr[POS(pos++)] = val >> 16;
	arr[POS(pos++)] = val >> 8;
	arr[POS(pos)] = val;
}

int		valid_reg_number(int value)
{
	if (value < 1 || value > REG_NUMBER)
		return (0);
	return (1);
}
