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
    byte_command->command_code = 16;
    byte_command->arg1 = get_arg(command[0], command->position, LIVE_T_DIR_SIZE, champ->labels_vec);
    champ->command_size += (byte_command->arg1->size + 1);
//    byte_command->command_size += arg->size; //  увеличиваем размер команды в байтах
    // add in vector arg
    ft_ptr_vec_pushback(champ->command_vec, byte_command);
    //command->position += arg->size;
    return (byte_command);
}