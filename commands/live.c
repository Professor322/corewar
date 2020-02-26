/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:42:57 by jziemann          #+#    #+#             */
/*   Updated: 2019/11/17 17:43:30 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"
# define LIVE_T_DIR_SIZE 4


t_b_command     *live(char **command, t_champ *champ)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    ft_ptr_vec_pushback(champ->command_vec, byte_command);
    byte_command = ((t_b_command*)(champ->command_vec->data[champ->command_vec->length - 1]));
    byte_command->command_code = 1;
    byte_command->cumulative_size = champ->command_size;
	byte_command->arg1 = get_arg(command[0], LIVE_T_DIR_SIZE, champ);
    champ->command_size += (byte_command->arg1->size + 1);
	return (byte_command);
}
