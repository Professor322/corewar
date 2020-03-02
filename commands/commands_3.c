/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:47:35 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/02 20:47:37 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

t_b_command     *ldi(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(LDI_COMMAND_CODE, champ, LDI_T_DIR_SIZE, command);
    return (byte_command);
}

t_b_command     *lfork(char **command, t_champ *champ)
{
    t_b_command *b_command;

    b_command = compile(LFORK_COMMAND_CODE, champ, LFORK_T_DIR_SIZE, command);
    return (b_command);
}

t_b_command     *live(char **command, t_champ *champ)
{
    t_b_command *b_command;

    b_command = compile(LIVE_COMMAND_CODE, champ, LIVE_T_DIR_SIZE, command);
    return (b_command);
}

t_b_command     *lld(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(LLD_COMMAND_CODE, champ, LLD_T_DIR_SIZE, command);
    return (byte_command);
}

t_b_command     *lldi(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(LLDI_COMMAND_CODE, champ, LLDI_T_DIR_SIZE, command);
    return (byte_command);
}
