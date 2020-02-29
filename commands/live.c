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

//TODO check type command
t_b_command     *compile(int cmd_code, t_champ *champ, int d_size, char **cmd)
{
    t_b_command     *b_command;
    int             i;
    unsigned int    byte_shift;
    const size_t    index = champ->command_vec->length - 1;

    if (!(b_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    ft_ptr_vec_pushback(champ->command_vec, b_command);
    b_command = ((t_b_command*)(champ->command_vec->data[index]));
    b_command->command_code = cmd_code;
    b_command->cumulative_size = champ->command_size;
    i = 0;
    byte_shift = 6;
    while (*cmd)
    {
        b_command->args[i] = get_arg((*cmd)++, d_size, champ);
        if (*cmd || i > 0) {
            b_command->arg_type_code += b_command->args[i]->type << byte_shift;
            byte_shift -= 2;
        }
        champ->command_size += (b_command->args[i]->size + (i < 2));
        printf("%d\n", champ->command_size);
        i++;
    }
}

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
	// byte_command->args[0] = get_arg(command[0], LIVE_T_DIR_SIZE, champ);
    champ->command_size += (byte_command->arg1->size + 1);
	return (byte_command);
}
