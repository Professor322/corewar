/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:36:43 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:36:44 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"
#define 4 ST_T_DIR_SIZE

void        st(t_command *command, t_foo *foo)
{
    t_arg *arg;

    arg = get_arg(command->arg1, command->position, ST_T_DIR_SIZE, foo->labels_vec);
    foo->command_size += arg->size; //  увеличиваем размер команды в байтах
    // add in vector arg
    ft_ptr_vec_pushback(foo->args_vec, arg);
    command->position += arg->size;
    arg = get_arg(command->arg2, command->position, ST_T_DIR_SIZE, foo->labels_vec);
    command->position += arg->size;
    foo->command_size += arg->size;
    // add in vector arg
    ft_ptr_vec_pushback(foo->args_vec, arg);
}

