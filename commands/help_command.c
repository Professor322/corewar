/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:46:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/12/26 20:46:34 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

short	reverse_short(short s)
{
    unsigned char c1, c2;

    c1 = s & 0xff;
    c2 = (s >> 8) & 0xff;
    return ((c1 << 8) + c2);
}

int		reverse_int(int s)
{
    unsigned short c1, c2;

    c1 = reverse_short(s & 0xffff);
    c2 = reverse_short( (s >> 16) & 0xffff);
    return ((c1 << 16) + c2);
}

int			ft_is_numeric(char *str)
{
    if (*str == '-')
        str++;
    while(*str)
        if (!ft_isdigit(*str++))
            return (0);
    return (1);
}

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

void        *label_init(t_arg *arg, int size, char *l_name, t_champ *champ)
{
    t_b_command     *byte_command;
    const size_t    index = champ->command_vec->length - 1;

    byte_command = (t_b_command*)(champ->command_vec->data[index]);
    if (!(arg->label = (t_label *)ft_memalloc(sizeof(t_label))))
        //exit, free, TODO
        return (NULL);
    arg->label->name = ft_strdup(l_name);
    arg->label->cumulate_size = byte_command->cumulative_size;
    arg->is_label = 1;
    arg->size = size;
    arg->label->size = size;
    arg->label->is_after = !ht_find_node(champ->labels, l_name) ? '1' : '0';
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

t_arg		*get_arg(char *arg, int dir_size, t_champ *champ)
{
    t_arg *arg_parse;

    if (!(arg_parse = (t_arg *)ft_memalloc(sizeof(t_arg))))
        //free exit()
        return (NULL);
    if (*arg && *arg == 'r')
        reg_arg(arg_parse, arg, champ);
    else if (*arg && *arg == '%')
        dir_arg(arg_parse, dir_size, arg, champ);
    else if (*arg && *arg == ':')
    {
        label_init(arg_parse, 2, arg + 1, champ);
        arg_parse->type = T_IND;
    }
    else if (ft_is_numeric(arg))
        indir_arg(arg_parse, arg);
    return (arg_parse);
}
