/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:35:12 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:35:14 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../assembler.h"
#define AFF_T_DIR_SIZE 1

t_b_command     *aff(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    ft_ptr_vec_pushback(champ->command_vec, byte_command);
    byte_command = ((t_b_command*)(champ->command_vec->data[champ->command_vec->length - 1]));
    byte_command->command_code = 0x10;
    byte_command->cumulative_size = champ->command_size;
    byte_command->arg1 = get_arg(command[0], AFF_T_DIR_SIZE, champ);
    champ->command_size += (byte_command->arg1->size + 2);
    byte_command->arg_type_code = (byte_command->arg1->type << (unsigned int) 6);
    return (byte_command);
}
