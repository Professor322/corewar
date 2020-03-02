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

//TODO check type command
t_b_command     *compile(int cmd_code, t_champ *champ, int d_size, char **cmd)
{
    t_b_command     *b_command;
    int             i;
    unsigned int    byte_shift;
    const size_t    index = champ->command_vec->length;

    if (!(b_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    ft_ptr_vec_pushback(champ->command_vec, b_command);
    b_command = ((t_b_command*)(champ->command_vec->data[index]));
    b_command->command_code = cmd_code;
    b_command->cumulative_size = champ->command_size;
    i = -1;
    byte_shift = 6;
    while (*cmd) // *cmd
    {
        b_command->args[++i] = *(get_arg(*cmd, d_size, champ));
        if ((*cmd && i != 0) || i > 0)
        {   if (i == 1)
            {
                b_command->arg_type_code += b_command->args[i - 1].type << byte_shift;
                printf("type %d\t byte shift: %d\n",b_command->args[i - 1].type,  b_command->arg_type_code);
            }
            byte_shift -= 2;
            b_command->arg_type_code += b_command->args[i].type << byte_shift;
            printf("type %d\t byte shift: %d\n",b_command->args[i].type,  b_command->arg_type_code);
        }
        champ->command_size += (b_command->args[i].size + (i < 2));
        printf("%i %d [%d]\n", i,champ->command_size,  b_command->arg_type_code);
        cmd++;
    }
    return (b_command);
}

t_b_command     *live(char **command, t_champ *champ)
{
//    t_b_command *byte_command;
//
//    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
//        return (NULL);
//    ft_ptr_vec_pushback(champ->command_vec, byte_command);
//    byte_command = ((t_b_command*)(champ->command_vec->data[champ->command_vec->length - 1]));
//    byte_command->command_code = 1;
//    byte_command->cumulative_size = champ->command_size;
//	byte_command->arg1 = get_arg(command[0], LIVE_T_DIR_SIZE, champ);
//	// byte_command->args[0] = get_arg(command[0], LIVE_T_DIR_SIZE, champ);
//    champ->command_size += (byte_command->arg1->size + 1);
	return (compile(LIVE_COMMAND_CODE, champ, LIVE_T_DIR_SIZE, command));
}
