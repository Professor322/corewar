//
// Created by Миняйлов Дмитрий Владимирович on 21.03.2020.
//

#include "corewar.h"

void clone_regs(const int old[REG_NUMBER], int new[REG_NUMBER])
{
    int i;

    i = 0;
    while (i < REG_NUMBER)
    {
        new[i] = old[i];
        i++;
    }
}

void clone_car(t_car *old, t_car *new)
{
    new->pos = old->pos;
    new->last_live = old->last_live;
    new->carry = old->carry;
    new->id = old->id;
    new->oper = old->oper;
    clone_regs(old->regs, new->regs);
}