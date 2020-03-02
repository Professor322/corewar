/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:35:57 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:35:59 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"
#define  LDI_T_DIR_SIZE 2

t_b_command     *ldi(char **command, t_champ *champ)
{
    t_b_command *byte_command;

//    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
//        return (NULL);
//    ft_ptr_vec_pushback(champ->command_vec, byte_command);
//    byte_command = ((t_b_command*)(champ->command_vec->data[champ->command_vec->length - 1]));
//    byte_command->command_code = 10;
//    byte_command->cumulative_size = champ->command_size;
//    byte_command->arg1 = get_arg(command[0], LDI_T_DIR_SIZE,  champ);
//    champ->command_size += (byte_command->arg1->size + 1);
//    byte_command->arg2 = get_arg(command[1], LDI_T_DIR_SIZE,  champ);
//    champ->command_size += (byte_command->arg2->size + 1);
//	byte_command->arg3 = get_arg(command[2], LDI_T_DIR_SIZE,  champ);
//	champ->command_size += (byte_command->arg3->size);
//    byte_command->arg_type_code = (byte_command->arg1->type << (unsigned int)6) +
//                                  (byte_command->arg2->type << (unsigned int)4) +
//                                  (byte_command->arg3->type << (unsigned int)2);
    byte_command = compile(LDI_COMMAND_CODE, champ, LDI_T_DIR_SIZE, command);
    return (byte_command);
}

