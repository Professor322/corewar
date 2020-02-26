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

t_b_command     *zjmp(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    ft_ptr_vec_pushback(champ->command_vec, byte_command);
    byte_command = ((t_b_command*)(champ->command_vec->data[champ->command_vec->length - 1]));
    byte_command->command_code = 9;
    //ft_int_vec_pushback(champ->cumulative_size, champ->command_size);
    byte_command->cumulative_size = champ->command_size;
    byte_command->arg1 = get_arg(command[0], ZJMP_T_DIR_SIZE, champ, byte_command);
    // add in vector arg
    ///ft_ptr_vec_pushback(champ->command_vec, byte_command);
    champ->command_size += (byte_command->arg1->size + 1);
    return (byte_command);
}
