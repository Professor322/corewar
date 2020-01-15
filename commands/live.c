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
t_b_command     *live(t_command *command, t_foo *foo)
{
    t_b_command *byte_command;

    if (!(byte_command = (t_b_command *)ft_memalloc(sizeof(t_b_command))))
        return (NULL);
    byte_command->command_code = 1;
	byte_command->arg1 = get_arg(command->args[0], command->position, LIVE_T_DIR_SIZE, foo->labels_vec);
//    byte_command->command_size += arg->size; //  увеличиваем размер команды в байтах
	// add in vector arg
	ft_ptr_vec_pushback(foo->command_vec, byte_command);
	//command->position += arg->size;
	return (byte_command);
}

int main(int argc, char **argv)
{
	int i;
	t_foo *foo;
    t_command *command;

    foo = (t_foo *)ft_memalloc(sizeof(t_foo));
    foo->command_vec = ft_ptr_vec_init();
    foo->labels_vec = ft_ptr_vec_init();
	i = 1;
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->args = (char **)malloc(sizeof(char*) * 3);
	command->args[0] = ft_strdup(argv[1]);
    command->args[1] = ft_strdup(argv[2]);
    command->args[2] = ft_strdup(argv[3]);
//	live(&command, foo);

    ldi(command, foo);
    for(int i = 0; i < foo->command_vec->length; i++)
    {
//        printf("\ntype :%d  size: %d\n", ((t_arg*)(foo->args_vec->data[i]))->type,  ((t_arg*)(foo->args_vec->data[i]))->size);
       // write(1, &((t_arg*)(foo->args_vec->data[i]))->bin, ((t_arg*)(foo->args_vec->data[i]))->size);
        write(1, &((t_b_command*)(foo->command_vec->data[i]))->command_code, 1);
        if ((((t_b_command*)(foo->command_vec->data[i]))->arg_type_code))
            write(1, &((t_b_command*)(foo->command_vec->data[i]))->arg_type_code, 1);
        write(1, &((t_arg*)(((t_b_command*)(foo->command_vec->data[i]))->arg1))->bin,
                  ((t_arg*)(((t_b_command*)(foo->command_vec->data[i]))->arg1))->size);
        write(1, &((t_arg*)(((t_b_command*)(foo->command_vec->data[i]))->arg2))->bin,
              ((t_arg*)(((t_b_command*)(foo->command_vec->data[i]))->arg2))->size);
        write(1, &((t_arg*)(((t_b_command*)(foo->command_vec->data[i]))->arg3))->bin,
              ((t_arg*)(((t_b_command*)(foo->command_vec->data[i]))->arg3))->size);
//        printf("\n");
    }
//    for (i = 0; i < foo->labels_vec->length; i++)
//    {
//        printf("LABEL name : %s  size : %d\n", ((t_label *)(((t_arg *)(foo->labels_vec->data[i]))->label))->name,
//         ((t_label *)(((t_arg *)(foo->labels_vec->data[i]))->label))->size);
//    }
	return (0);
}
