/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 19:38:49 by vlegros           #+#    #+#             */
/*   Updated: 2020/05/22 20:05:31 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void		skip_spaces(char **line)
{
	if (!line)
		return ;
	if (!*line)
		return ;
	while (**line && ft_isspace(**line))
		(*line)++;
}

int			read_line(t_champ **champ_ptr)
{
	const int v = get_next_line((*champ_ptr)->fd_input, &((*champ_ptr)->line));

	if (v > 0)
		(*champ_ptr)->counter++;
	return (v);
}

char		*is_label(char *line)
{
	const char *lb = ft_strchr(line, LABEL_CHAR);

	while (line != lb && ft_strchr(LABEL_CHARS, *line))
		line++;
	return (line == lb ? (char*)lb : NULL);
}

int			is_command(char **line)
{
	int		i;
	char	c;

	i = -1;
	skip_spaces(line);
	while (++i < COMMANDS_NUM)
		if (!ft_strncmp(*line, g_commands[i].name,
				g_commands[i].name_len))
		{
			c = *(*line + g_commands[i].name_len);
			return (ft_isspace(c) || c == '%' ? i : -1);
		}
	return (-1);
}

void		finish_him(t_champ **champ)
{
	if (*champ)
		free_memory_and_close_fd(champ);
	exit(1);
}
