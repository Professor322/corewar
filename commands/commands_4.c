/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:57:38 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/02 20:57:39 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

t_b_command     *zjmp(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    byte_command = compile(ZJMP_COMMAND_CODE, champ, ZJMP_T_DIR_SIZE, command);
    return (byte_command);
}
