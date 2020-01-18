/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:35:48 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:35:52 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"
#define LD_T_DIR_SIZE 4

t_b_command     *ld(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    byte_command->command_code = 2;

    byte_command->arg1 = get_arg(command[0], LD_T_DIR_SIZE, champ->labels_vec);
    champ->command_size += (byte_command->arg1->size + 1);
    byte_command->arg2 = get_arg(command[1], LD_T_DIR_SIZE, champ->labels_vec);
    champ->command_size += (byte_command->arg2->size + 1);
    byte_command->arg_type_code = (byte_command->arg1->type << (unsigned int) 6) +
                                  (byte_command->arg2->type << (unsigned int) 4);
    // add in vector arg
    ft_ptr_vec_pushback(champ->command_vec, byte_command);
}
