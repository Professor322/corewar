/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:37:47 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:37:50 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"
#define 2 ZJMP_T_DIR_SIZE

void        sub(t_command *command, t_foo *foo)
{
    t_arg *arg;

    arg = get_arg(command->arg1, command->position, ZJMP_T_DIR_SIZE, foo->labels_vec);
    foo->command_size += arg->size; //  увеличиваем размер команды в байтах
    // add in vector arg
    ft_ptr_vec_pushback(foo->args_vec, arg);
    command->position += arg->size;
}
