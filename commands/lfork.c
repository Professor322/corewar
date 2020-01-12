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

t_b_command     *lfork(t_command *command, t_foo *foo)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    byte_command->command_code = 15;
    byte_command->arg1 = get_arg(command->args[0], command->position, LIVE_T_DIR_SIZE, foo->labels_vec);
//    byte_command->command_size += arg->size; //  увеличиваем размер команды в байтах
    // add in vector arg
    ft_ptr_vec_pushback(foo->command_vec, byte_command);
    //command->position += arg->size;
}

