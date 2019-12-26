/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:36:36 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:36:37 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"
#define 4 OR_T_DIR_SIZE

void        or(t_command *command, t_foo *foo)
{
    t_arg *arg;

    arg = get_arg(command->arg1, command->position, OR_T_DIR_SIZE, foo->labels_vec);
    foo->command_size += arg->size; //  увеличиваем размер команды в байтах
    // add in vector arg
    ft_ptr_vec_pushback(foo->args_vec, arg);
    command->position += arg->size;

    arg = get_arg(command->arg2, command->position, OR_T_DIR_SIZE, foo->labels_vec);
    command->position += arg->size;
    foo->command_size += arg->size;
    // add in vector arg
    ft_ptr_vec_pushback(foo->args_vec, arg);

    arg = get_arg(command->arg3, command->position, OR_T_DIR_SIZE, foo->labels_vec);
    command->position += arg->size;
    foo->command_size += arg->size;
    // add in vector arg
    ft_ptr_vec_pushback(foo->args_vec, arg);
}

