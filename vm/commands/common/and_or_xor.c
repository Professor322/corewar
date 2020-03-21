//
// Created by Миняйлов Дмитрий Владимирович on 15/01/2020.
//

#include "corewar.h"

int	logical_validate_permitted_types(t_arg *args)
{
    if ((args[0].type == REG || args[0].type == DIR || args[0].type == IND)
        &&
        (args[1].type == REG || args[1].type == DIR || args[1].type == IND)
        &&
        args[2].type == REG
        &&
        args[3].type == NONE)
        return 1;
    return 0;
}