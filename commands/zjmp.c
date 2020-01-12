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
#define ZJMP_T_DIR_SIZE 2

t_b_command     *(t_command *command, t_foo *foo)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    byte_command->command_code = 9;
    arg = get_arg(command->args[0], command->position, ZJMP_T_DIR_SIZE, foo->labels_vec);
    // add in vector arg
    ft_ptr_vec_pushback(foo->command_vec, byte_command);
}
