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
    //dprintf(get_fd_debug(), "P % 4lu | sti r%d %d %d\n", car->id + 1, 1, val1, val2);
    if (cbox->flags & V_FLAG_OPER) {
        //ft_printf("%d\t", cbox->cycle_counter);
        ft_printf("P % 4lu | sti r%d %d %d\n", car->id + 1, args[0].value, val1, val2);
        ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n"
                , val1, val2, val1 + val2, NOTZERO(car->pos + IND_OFFSET(val1 + val2)));

//        ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n"
//                , val1, val2, IND_OFFSET(val1 + val2) == 1 ? 1025 : IND_OFFSET(val1 + val2), car->pos + IND_OFFSET(val1 + val2));

        // 1025 ? -> ./test.sh -a mandragore -b littlepuppy -f 2624 -t 8 -v
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