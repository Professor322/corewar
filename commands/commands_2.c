/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:47:29 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/02 20:47:31 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

t_b_command     *or(char **command, t_champ *champ)
{
    t_b_command *b_command;
    t_arg       *args;

    b_command = compile(OR_COMMAND_CODE, champ, OR_T_DIR_SIZE, command);
    args = b_command->args;
    if (args[2].type != T_REG)
        //exit() TODO free memory
    return (b_command);
}

t_b_command     *st(char **command, t_champ *champ)
{
    t_b_command *b_command;
    t_arg       *args;

    b_command = compile(ST_COMMAND_CODE, champ, ST_T_DIR_SIZE, command);
    args = b_command->args;
    if (args[0].type != T_REG || args[1].type == T_DIR)
        //exit() TODO free memory
    return (b_command);
}

t_b_command     *sti(char **command, t_champ *champ)
{
    t_b_command *b_command;
    t_arg       *args;

    b_command = compile(STI_COMMAND_CODE, champ, STI_T_DIR_SIZE, command);
    args = b_command->args;
    if (args[0].type != T_REG || args[2].type == T_IND)
        //exit() TODO free memory
    return (b_command);
}

t_b_command     *sub(char **command, t_champ *champ)
{
    t_b_command *b_command;
    t_arg       *args;

    b_command = compile(SUB_COMMAND_CODE, champ, SUB_T_DIR_SIZE, command);
    if (args[0].type != T_REG || args[1].type != T_REG || args[2].type != T_REG)
        //exit() TODO free memory
    return (b_command);
}

t_b_command     *xor(char **command, t_champ *champ)
{
    t_b_command *b_command;
    t_arg       *args;

    b_command = compile(XOR_COMMAND_CODE, champ, XOR_T_DIR_SIZE, command);
    args = b_command->args;
    if (args[2].type != T_REG)
        //exit() TODO free memory
    return (b_command);
}
