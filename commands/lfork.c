/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:36:06 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:36:08 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"
#define LFORK_T_DIR_SIZE 2

t_b_command     *lfork(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    byte_command->command_code = 15;
    ft_int_vec_pushback(champ->cumulative_size, champ->command_size);
    byte_command->arg1 = get_arg(command[0], LFORK_T_DIR_SIZE, champ->labels_vec);
//    byte_command->command_size += arg->size; //  увеличиваем размер команды в байтах
    champ->command_size += (byte_command->arg1->size + 1);
    // add in vector arg
    ft_ptr_vec_pushback(champ->command_vec, byte_command);
    //command->position += arg->size;
    return (byte_command);
}

