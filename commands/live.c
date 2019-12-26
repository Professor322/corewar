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
void        live(t_command *command, t_foo *foo)
{
	// t_foo *foo;
    t_arg *arg;

	// foo = (t_foo *)ft_memalloc(sizeof(t_foo)); // must be the void vector
	//foo->args_vec = ft_ptr_vec_init();
    //foo->labels_vec = ft_ptr_vec_init();

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
	//return (foo);
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
