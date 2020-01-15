/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:50:18 by jziemann          #+#    #+#             */
/*   Updated: 2020/01/15 19:50:20 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

void        write_rubbish_in_file(int fd, t_foo *foo)
{

}

void        write_exec_code_in_file(int fd, t_pvec *command_vec, char *filename)
{
    const int       len = command_vec->length;
    t_b_command     *c_vec;
    t_arg           *arg;
    int             i;

    i = -1;
    while (++i < len)
    {
        c_vec = ((t_b_command *)command_vec->data[i]);
        if (c_vec->arg_type_code)
            write(1, &(c_vec->arg_type_code), 1);
        arg = ((t_arg*)c_vec->arg1);
        write(fd, &arg->bin, arg->size);
        arg = ((t_arg*)c_vec->arg2);
        write(fd, &arg->bin, arg->size);
        arg = ((t_arg*)c_vec->arg3);
        write(fd, &arg->bin, arg->size);
    }
//write(fd, &test, 1);
}

int        main()
{
    t_foo           *foo;
    int             fd;

    fd = open(filename, O_CREAT | O_WRONLY, 0644);
    write_in_file_command(fd, foo->command_vec, "/Users/jziemann/corewar/src/mat.s");
    return (0);
}

