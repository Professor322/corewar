/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:55:20 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/02 20:55:22 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

void        indir_arg(t_arg *arg_parse, char *arg)
{
    unsigned int    ind_val;
    int             temp;

    temp = ft_atoi(arg);
    ind_val = temp < 0 ? ~((temp * -1)) + 1 : temp;
    arg_parse->type = T_IND;
    arg_parse->size = 2;
    arg_parse->bin = reverse_short((short)ind_val);

}

void        label_init(t_arg *arg, int size, char *l_name, t_champ *champ)
{
    t_b_command     *byte_command;
    const size_t    index = champ->command_vec->length - 1;

    byte_command = (t_b_command*)(champ->command_vec->data[index]);
    if (!(arg->label = (t_label *)ft_memalloc(sizeof(t_label))))
        error_manager(MALLOC_ERROR, &champ);
    arg->label->name = ft_strdup(l_name);
    arg->label->cumulate_size = byte_command->cumulative_size;
    arg->is_label = 1;
    arg->size = size;
    ft_ptr_vec_pushback(champ->labels_vec, arg);
}

void        dir_arg(t_arg *arg_parse, int dir_size, char *arg, t_champ *champ)
{
    unsigned int   dir_val;
    int             temp;

    if (arg[1] && arg[1] == ':')
        label_init(arg_parse, dir_size, arg + 2, champ);
    else
    {
        temp = ft_atoi(++arg);
        dir_val = temp < 0 ? ~(temp * -1) + 1 : temp;
        arg_parse->bin = dir_size == 4 ? reverse_int((int)dir_val) :
                         reverse_short((short)dir_val);
        arg_parse->size = dir_size;
    }
    arg_parse->type = T_DIR;
}

void        reg_arg(t_arg *arg_parse, char *arg, t_champ *champ)
{
    int r_val;

    if (arg[1] && arg[1] == ':')
        label_init(arg_parse, 1, arg + 2, champ);
    else
    {
        r_val = ft_atoi(++arg);
        arg_parse->size = 1;
        arg_parse->type = T_REG;
        arg_parse->bin = r_val;
    }
    arg_parse->type = T_REG;
}

t_b_command     *compile(int cmd_code, t_champ *champ, int d_size, char **cmd)
{
    t_b_command     *b_cmd;
    int             i;
    unsigned int    byte_shift;
    const size_t    index = champ->command_vec->length;

    if (!(b_cmd = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        error_manager(MALLOC_ERROR, &champ);
    ft_ptr_vec_pushback(champ->command_vec, b_cmd);
    b_cmd = ((t_b_command*)(champ->command_vec->data[index]));
    b_cmd->command_code = cmd_code;
    b_cmd->cumulative_size = champ->command_size;
    i = -1;
    byte_shift = 6;
    while (*cmd)
    {
        i++;
        b_cmd->args[i] = *(get_arg(*cmd, d_size, champ, &b_cmd->args[i]));
        if ((*cmd && i != 0) || i > 0)
        {   if (i == 1)
                b_cmd->arg_type_code += b_cmd->args[i - 1].type << byte_shift;
            byte_shift -= 2;
            b_cmd->arg_type_code += b_cmd->args[i].type << byte_shift;
        }
        champ->command_size += (b_cmd->args[i].size + (i < 2));
        cmd++;
    }
    return (b_cmd);
}
