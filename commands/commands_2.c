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
    t_b_command *byte_command;

    byte_command = compile(OR_COMMAND_CODE, champ, OR_T_DIR_SIZE, command);
    return (byte_command);
}

t_b_command     *st(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(ST_COMMAND_CODE, champ, ST_T_DIR_SIZE, command);
    return (byte_command);
}

t_b_command     *sti(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(STI_COMMAND_CODE, champ, STI_T_DIR_SIZE, command);
    return (byte_command);
}

t_b_command     *sub(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(SUB_COMMAND_CODE, champ, SUB_T_DIR_SIZE, command);
    return (byte_command);
}

t_b_command     *xor(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(XOR_COMMAND_CODE, champ, XOR_T_DIR_SIZE, command);
    return (byte_command);
}
