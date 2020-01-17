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

void        write_string(size_t str_len, size_t limit, char *str)
{
    char            *temp_str;

    temp_str = ft_strnew(limit - str_len);
    write(fd, str, str_len);
    write(fd, temp_str, limit - str_len);
    ft_strdel(temp_str);
}

void        write_rubbish_in_file(int fd, t_champ *champ)
{
    const size_t    name_len = ft_strlen(name);
    char            *temp_str;

    // write magic num
    write(fd, COREWAR_EXEC_MAGIC, 4);
    // write name champion
    write_string(ft_strlen(name), PROG_NAME_LENGTH, name);
    // write 4 NULL
    write_string(0, 4, NUll);
    // write champion exec code size
    write(fd, &champ->command_size, 4);
    // write champion_comment
    write_string(ft_strlen(comment), COMMENT_LENGTH, comment);
    // write 4 NULL
    write_string(0, 4, NUll);

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
        write(fd, &(c_vec->command_code), 1);
        if (c_vec->arg_type_code)
            write(fd, &(c_vec->arg_type_code), 1);
        arg = ((t_arg*)c_vec->arg1);
        write(fd, &arg->bin, arg->size);
        arg = ((t_arg*)c_vec->arg2);
        write(fd, &arg->bin, arg->size);
        arg = ((t_arg*)c_vec->arg3);
        write(fd, &arg->bin, arg->size);
    }
//write(fd, &test, 1);
}
/*
int        main()
{
    t_foo           *foo;
    int             fd;

    fd = open(filename, O_CREAT | O_WRONLY, 0644);
    write_in_file_command(fd, foo->command_vec, "/Users/jziemann/corewar/src/mat.s");
    return (0);
}
*/
