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

void        write_string(int fd, size_t str_len, size_t limit, char *str)
{
    char            *temp_str;

    temp_str = ft_strnew(limit - str_len);
    write(fd, str, str_len);
    write(fd, temp_str, limit - str_len);
    ft_strdel(&temp_str);
}

void        write_rubbish_in_file(int fd, t_champ *champ)
{
    const size_t    name_len = ft_strlen(champ->name);
    char            *temp_str;
    const int       magic = reverse_int(COREWAR_EXEC_MAGIC);

    // write magic num
    write(fd, &magic, 4);
    // write name champion
    write_string(fd, ft_strlen(champ->name), PROG_NAME_LENGTH, champ->name);
    // write 4 NULL
    write_string(fd, 0, 4, 0);
    // write champion exec code size
    champ->command_size = reverse_int(champ->command_size);
    write(fd, &champ->command_size, 4);
    // write champion_comment
    write_string(fd, ft_strlen(champ->comment), COMMENT_LENGTH, champ->comment);
    // write 4 NULL
    write_string(fd, 0, 4, 0);

}

void    printHashtable(t_ht* champ_label) {
    int i = -1;
    while (++i < champ_label->loaded->length) {
        t_list *temp = champ_label->table[champ_label->loaded->data[i]];
        while (temp) {
            t_node* elem = temp->content;
            printf("name: %s size: %d\n", elem->name, elem->command->cumulative_size);
            temp = temp->next;
        }
    }
}

int        substitute_label(t_ht *champ_label, t_arg *arg)
{
    //write(1,"HHH", 3);
    printHashtable(champ_label);
    const int   hash_size = ht_find_node(champ_label,arg->label->name)->command->cumulative_size;
    int         bin_label;

    bin_label =  hash_size - arg->label->cumulate_size;//* (arg->label->is_after == '1' ? 1 : -1);
    bin_label = bin_label < 0 ? ~(bin_label * -1) + 1 : bin_label;
    if (arg->size == 4)
        return (reverse_int(bin_label));

    else if (arg->size == 2)
        return (reverse_short((short)bin_label));

    else
        return (bin_label);
}

void        write_exec_code_in_file(int fd, t_pvec *command_vec, char *filename, t_champ *champ)
{
    const int       len = command_vec->length;
    t_b_command     *c_vec;
    t_arg           *arg;
    int             i;

    i = -1;
    write_rubbish_in_file(fd, champ);
    while (++i < len)
    {
        c_vec = ((t_b_command *)command_vec->data[i]);
        write(fd, &(c_vec->command_code), 1);
        if (c_vec->arg_type_code)
            write(fd, &(c_vec->arg_type_code), 1);
        arg = ((t_arg*)c_vec->arg1);
        if (arg->is_label)
          arg->bin = substitute_label(champ->labels, arg);
        write(fd, &arg->bin, arg->size);
        arg = ((t_arg*)c_vec->arg2);
        if (arg)
        {
            if (arg->is_label)
                arg->bin = substitute_label(champ->labels, arg);
            write(fd, &arg->bin, arg->size);
        }
        arg = ((t_arg*)c_vec->arg3);
        if (arg)
        {
            if (arg->is_label)
                arg->bin = substitute_label(champ->labels, arg);
            write(fd, &arg->bin, arg->size);
        }
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
