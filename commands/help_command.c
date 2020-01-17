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

int			ft_is_numeric(char *str)
{
    while(*str)
        if (!ft_isdigit(*str++))
            return (0);
    return (1);
}

unsigned int       amount_real_bytes(unsigned int num, unsigned int size)
{
    unsigned int amount;

    amount = 0;
    if (!num)
        return (0);
    while (num > 0)
    {
        amount++;
        num >>= 8;
    }
//    printf("\nsize: %d\n amount : %d\n", size, amount);
//    printf("real_bytes: %d\n", size - amount);
    return (size - amount);
}

void        reg_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int r_val;

    r_val = ft_atoi(++arg);
    arg_parse->size = 1;
    arg_parse->type = T_REG;
    arg_parse->bin = r_val; // one byte
//    write(1, &arg_parse->bin, arg_parse->size);
//    printf("\nsize %d\n type %u\n", arg_parse->size, arg_parse->type);
}

void        dir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    unsigned int dir_val;

    dir_val = ft_atoi(++arg);
    arg_parse->size = dir_size;
    arg_parse->type = T_DIR;
    arg_parse->bin = dir_val << 8 * amount_real_bytes(dir_val, dir_size);
//    write(1, &arg_parse->bin, arg_parse->size);
//    printf("\nsize %d\n type %u\n", arg_parse->size, arg_parse->type);
}

void        indir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int ind_val;
    ind_val = ft_atoi(arg);
    arg_parse->type = T_IND;
    arg_parse->size = 2;
    arg_parse->bin = ind_val << 8 * amount_real_bytes(ind_val, arg_parse->size);
//    write(1, &arg_parse->bin, arg_parse->size);
//    printf("size %d\n type %u\n", arg_parse->size, arg_parse->type);
    //indirect
}

void        label_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    arg_parse->label = (t_label *)ft_memalloc(sizeof(t_label));
    //мы должны знать вместо какого аргумента он тут стоит
//    printf("LABEL %s\n", ++arg);
    arg_parse->label->name = ft_strdup(arg);
    //arg_parse->label->position = pos;
    arg_parse->type = T_LABEL;
    arg_parse->size = dir_size;
    arg_parse->label->size = dir_size; //label
}
/**
 * определяем к какому типу относится аргументы
 * является ли он меткой
 * кодируем в бинарный вид
 * @param agr аргумент команды
 * @param pos
 * @param dir_size
 * @return pointer !!
 */
t_arg		*get_arg(char *arg, int dir_size, t_pvec *label_vec)
{
    t_arg *arg_parse;

    arg_parse = (t_arg *)ft_memalloc(sizeof(t_arg));
    if (arg[0] == 'r')
    {
        if (arg[1] == ':')
        {
            label_arg(arg_parse, 1, arg + 2);
            ft_ptr_vec_pushback(label_vec, arg_parse);
        }
        else
        {
            reg_arg(arg_parse, dir_size, arg); // unused dir_size
        }
    }
    else if (arg[0] == '%')
    {
        if (arg[1] == ':')
        {
            label_arg(arg_parse, dir_size, arg + 2);
            ft_ptr_vec_pushback(label_vec, arg_parse);
        }
        else
        {
            dir_arg(arg_parse, dir_size, arg);
        }
    }
    else if (arg[0] == ':')
    {
        label_arg(arg_parse, 2, arg);

        ft_ptr_vec_pushback(label_vec, arg_parse);
    }
    else if (ft_is_numeric(arg))
        indir_arg(arg_parse, dir_size, arg); // unused dir_size
    else
    {

        printf("GOVNO");
        exit(0);
    }
    return (arg_parse);
}
