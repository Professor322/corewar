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

int			ft_is_numeric(char *str)
{
	while(*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int amount_real_bytes(unsigned int num, int size) {
    int amount;

    amount = 0;
    if (!num)
        return (0);
    while (num > 0)
    {
        amount++;
        num >>= 8;
    }
    printf("\nsize: %d\n amount : %d\n", size, amount);
    printf("real_bytes: %d\n", size - amount);
    return (size - amount);
}

void    reg_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int r_val;

    r_val = ft_atoi(++arg);
    arg_parse->size = 1;
    arg_parse->type = T_REG;
    arg_parse->bin = r_val; // one byte
//    write(1, &arg_parse->bin, arg_parse->size);
    printf("\nsize %d\n type %u\n", arg_parse->size, arg_parse->type);
}

void    dir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int dir_val;

    dir_val = ft_atoi(++arg);
    arg_parse->size = dir_size;
    arg_parse->type = T_DIR;
    arg_parse->bin = dir_val << 8 * amount_real_bytes(dir_val, dir_size);
//    write(1, &arg_parse->bin, arg_parse->size);
    printf("\nsize %d\n type %u\n", arg_parse->size, arg_parse->type);
}

void    indir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int ind_val;
    ind_val = ft_atoi(arg);
    arg_parse->type = T_IND;
    arg_parse->size = 2;
    arg_parse->bin = ind_val << 8 * amount_real_bytes(ind_val, arg_parse->size);
//    write(1, &arg_parse->bin, arg_parse->size);
    printf("size %d\n type %u\n", arg_parse->size, arg_parse->type);
    //indirect
}

void    label_arg(t_arg *arg_parse, int dir_size, char *arg, int pos)
{
    arg_parse->label = (t_label *)ft_memalloc(sizeof(t_label));
    //мы должны знать вместо какого аргумента он тут стоит
//    printf("LABEL %s\n", ++arg);
    arg_parse->label->name = ft_strdup(arg);
    arg_parse->label->position = pos;
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
t_arg		*get_arg(char *arg, int pos, int dir_size, t_pvec *label_vec)
{
	t_arg *arg_parse;

	arg_parse = (t_arg *)ft_memalloc(sizeof(t_arg));
	if (arg[0] == 'r')
	{
        if (arg[1] == ':')
        {
            label_arg(arg_parse, 1, arg + 2, pos);
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
            label_arg(arg_parse, dir_size, arg + 2, pos);
            ft_ptr_vec_pushback(label_vec, arg_parse);
        }
        else
        {
            dir_arg(arg_parse, dir_size, arg);
        }
    }
	else if (arg[0] == ':')
	{
        label_arg(arg_parse, 2, arg, pos);

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

/**
 * получаем структуру вида
 * строчка  для записи команды в бинарном виде int *byte
 * позиция, начиная с которой надо записывать команду
 * три строчки, содержащие в себе аргументы
 *
 * возращаем структуру, в которой будет число, со-
 * держащие кол-во байт, занятое командой и массив струткут
 * поинетор на метки
 *
 * что происходит?
 * для каждого аргумента команды создаем структуру t_arg, которая
 * будет содержать информацию о типе, является ли это значение меткой и какой? , значение в бинарном виде, и размер??
 *
**/
t_foo		*live(t_command *command)
{
	t_foo *foo;
    t_arg *arg;

	foo = (t_foo *)ft_memalloc(sizeof(t_foo)); // must be the void vector
	foo->args_vec = ft_ptr_vec_init();
    foo->labels_vec = ft_ptr_vec_init();

	arg = get_arg(command->arg1, command->position, LIVE_T_DIR_SIZE, foo->labels_vec);
	foo->command_size += arg->size; //  увеличиваем размер команды в байтах
	// add in vector arg
	ft_ptr_vec_pushback(foo->args_vec, arg);
	command->position += arg->size;
//	arg = get_arg(command->arg2, command->position, LIVE_T_DIR_SIZE, foo->labels_vec);
//	command->position += arg->size;
//    foo->command_size += arg->size;
//    // add in vector arg
//    ft_ptr_vec_pushback(foo->args_vec, arg);
//    arg = get_arg(command->arg3, command->position, LIVE_T_DIR_SIZE, foo->labels_vec);
//	command->position += arg->size;
//    foo->command_size += arg->size;
//    // add in vector arg
//    ft_ptr_vec_pushback(foo->args_vec, arg);
//	// собрать массив из меток собран
	return (foo);
}

int main(int argc, char **argv)
{
	int i;

	i = 1;
	//while (i < argc)
	t_command command;
	command.arg1 = argv[1];
	command.arg2 = argv[2];
	command.arg3 = argv[3];
	command.position = 0;
	t_foo *foo = live(&command);
    printf("\ncommand_size: %d \n", foo->command_size);
    for(int i = 0; i < foo->args_vec->length; i++)
    {
        printf("\ntype :%d  size: %d\n", ((t_arg*)(foo->args_vec->data[i]))->type,  ((t_arg*)(foo->args_vec->data[i]))->size);
        write(1, &((t_arg*)(foo->args_vec->data[i]))->bin, ((t_arg*)(foo->args_vec->data[i]))->size);
        printf("\n");
    }
    for (i = 0; i < foo->labels_vec->length; i++)
    {
        printf("LABEL name : %s  size : %d\n", ((t_label *)(((t_arg *)(foo->labels_vec->data[i]))->label))->name,
         ((t_label *)(((t_arg *)(foo->labels_vec->data[i]))->label))->size);
    }
	// get_arg(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
	//printf("%s\n", int_to_bin(ft_atoi(argv[1]), ft_atoi(argv[2])));
	return (0);
}

