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


int			ft_is_numeric(char *str)
{
	while(*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int amount_real_bytes(unsigned int num) {
    int amount;

    amount = 0;
    if (!num)
        return (0);
    while (num > 0)
    {
        amount++;
        num >>= 8;
    }
    if (amount % 2 == 0)
        return (3 - amount);
    else
        return (4 - amount);
}

void    reg_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int r_val;

    r_val = ft_atoi(++arg);
    arg_parse->size = 1;
    arg_parse->type = T_REG;
    arg_parse->bin = r_val; // one byte
    write(1, &arg_parse->bin, arg_parse->size);
    printf("\nsize %d\n type %u\n", arg_parse->size, arg_parse->type);
}

void    dir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int dir_val;

    dir_val = ft_atoi(++arg);
    arg_parse->size = dir_size;
    arg_parse->type = T_DIR;
    arg_parse->bin = dir_val << 8 * amount_real_bytes(dir_val);
    write(1, &arg_parse->bin, arg_parse->size);
    printf("\nsize %d\n type %u\n", arg_parse->size, arg_parse->type);
}

void    indir_arg(t_arg *arg_parse, int dir_size, char *arg)
{
    int ind_val;
    ind_val = ft_atoi(arg);
    arg_parse->type = T_IND;
    arg_parse->size = 2;
    arg_parse->bin = ind_val << 8 * amount_real_bytes(ind_val);
    write(1, &arg_parse->bin, arg_parse->size);
    printf("size %d\n type %u\n", arg_parse->size, arg_parse->type);
    //indirect
}

void    label_arg(t_arg *arg_parse, int dir_size, char *arg, int pos)
{
    //мы должны знать вместо какого аргумента он тут стоит
    printf("LABEL %s\n", ++arg);
    arg_parse->label->name = arg;
    arg_parse->label->position = pos;

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
t_arg		get_arg(char *arg, int pos, int dir_size, )
{
	t_arg *arg_parse;

	arg_parse = (t_arg *)ft_memalloc(sizeof(t_arg));
	if (arg[0] == 'r')
		reg_arg(arg_parse, dir_size, arg);
	else if (arg[0] == '%')
        dir_arg(arg_parse, dir_size, arg);
	else if (arg[0] == ':')
        label_arg(arg_parse, dir_size, arg, pos);
	else if (ft_is_numeric(arg))
        indir_arg(arg_parse, dir_size, arg);
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
	arg = get_arg(command->arg1, command->position, LIVE_T_DIR_SIZE);
	foo->command_size += arg->size; //  увеличиваем размер команды в байтах
	// add in vector arg
	command->position += arg->size;
	arg = get_arg(command->arg2, command->position, LIVE_T_DIR_SIZE);
	command->position += arg->size;
    foo->command_size += arg->size;
    // add in vector arg
    arg = get_arg(command->arg3, command->position, LIVE_T_DIR_SIZE);
	command->position += arg->size;
    foo->command_size += arg->size;

    // add in vector arg
//	// собрать массив из меток
	return (foo);
}

int main(int argc, char **argv)
{
	int i;

	i = 1;
	//while (i < argc)
	get_arg(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
	//printf("%s\n", int_to_bin(ft_atoi(argv[1]), ft_atoi(argv[2])));
	return (0);
}
