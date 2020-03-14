/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:50:18 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/14 18:07:33 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

void		write_string(int fd, size_t str_len, size_t limit, char *str)
{
	char	*temp_str;

	temp_str = ft_strnew(limit - str_len);
	write(fd, str, str_len);
	write(fd, temp_str, limit - str_len);
	ft_strdel(&temp_str);
}

void		write_rubbish_in_file(int fd, t_champ *champ)
{
	const size_t	name_len = ft_strlen(champ->name);
	char			*temp_str;
	const int		magic = reverse_int(COREWAR_EXEC_MAGIC);

	write(fd, &magic, 4);
	write_string(fd, ft_strlen(champ->name), PROG_NAME_LENGTH, champ->name);
	write_string(fd, 0, 4, 0);
	champ->command_size = reverse_int(champ->command_size);
	write(fd, &champ->command_size, 4);
	write_string(fd, ft_strlen(champ->comment), COMMENT_LENGTH, champ->comment);
	write_string(fd, 0, 4, 0);
}

int			substitute_label(t_ht *champ_label, t_arg *arg, t_champ *champ)
{
	t_node		*hash;
	int			bin_label;
	int			hash_size;

	hash = ht_find_node(champ_label, arg->label->name);
	if (!hash)
		error_manager(LABELS_WITHOUT_COMMAND, &champ);
	hash_size = hash->command->cumulative_size;
	bin_label = hash_size - arg->label->cumulate_size;
	bin_label = bin_label < 0 ? ~(bin_label * -1) + 1 : bin_label;
	if (arg->size == 4)
		return (reverse_int(bin_label));
	else if (arg->size == 2)
		return (reverse_short((short)bin_label));
	else
		return (bin_label);
}

void		write_exec_code_in_file(int fd, t_pvec *command_vec, t_champ *champ)
{
	const int	len = command_vec->length;
	t_b_command	*c_vec;
	t_arg		*arg;
	int			i;
	int			j;

	i = -1;
	write_rubbish_in_file(fd, champ);
	while (++i < len)
	{
		c_vec = ((t_b_command *)command_vec->data[i]);
		write(fd, &(c_vec->command_code), 1);
		if (c_vec->arg_type_code)
			write(fd, &(c_vec->arg_type_code), 1);
		j = -1;
		while (++j < 3)
		{
			arg = &(c_vec->args[j]);
			if (arg->type == 0)
				continue;
			if (arg->is_label)
				arg->bin = substitute_label(champ->labels, arg, champ);
			write(fd, &arg->bin, arg->size);
		}
	}
}
