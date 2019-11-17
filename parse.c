/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:20:23 by vlegros           #+#    #+#             */
/*   Updated: 2019/11/13 19:20:23 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_pair	*g_commands[16];


char	*dec_to_bin(int n) {
	char *result = ft_strnew(BYTE);
	int i = -1;

	while (++i < BYTE) {
		result[BYTE - i - 1] = (n % (int)2) + '0';
		n /= 2;
	}
	return result;
}

int 	find_command(char *command)
{
	int i = -1;

	while (++i < COMMANDS_NUM) {
		if (!ft_strcmp(g_commands[i]->key, command))
			return (i);
	}
	return (-1);
}


/**
 * t_reg - starts with 'r' or label code '01'
 * t_dir - start with % or label code '10'
 * t_ind - starts with nothing or label code '11'
 */


/**
 * 1) лейбл
 * 		1.1) считывается до ':'
 * 		1.2) пропускаются ' ' и '\t'
 * 2) команда и ее аргументы
 * 		2.1)  команда считывается до {'%', ' ', '\t'}
 * 		2.2)  проверка на валидность считанной команды
 * 		2.3)  если "стоп символ" был '%', то разделение начинается с него
 * 			  иначе, со следующего символа
 * 			  разделить команды по ','
 * 3) комментарий
 * 		3.1) хз
 */

int 	is_command(const char *it_begin, const char *it_end)
{
	if (it_end)
	{
		while (it_begin != it_end)
		{
			if (*it_begin == ' ' || *it_begin == '\t')
				return (0);
			it_begin++;
		}
		return (1);
	}
	return (0);
}

int		is_label(const char *it_begin, const char *it_end)
{
	if (it_end)
	{
		while (it_begin != it_end)
		{
			if (*it_begin == ' ' || *it_begin == '\t')
				return (0);
			it_begin++;
		}
		return (1);
	}
	return (0);
}

char	*get_label(char *line)
{
	char  *end_of_label = ft_strchr(line, ':');

	if (is_label(line, end_of_label))
	{
		*end_of_label = '\0';
		///add label to array of labels
		//printf("%s\n", line);
		return (end_of_label + 1) && *(end_of_label + 1) != '\0' ?
		end_of_label + 1 : NULL;
	}
	return line;
}

void	delete_comment(char *line)
{
	char  *comment_start = ft_strchr(line, '#');

	if (comment_start)
		*comment_start = '\0';
}

void	get_command(char *line)
{
	char *command = ft_strtrim(line);

	if (is_command())
	{

	}
	ft_memdel((void**)&command);
}

void	parse(int fd)
{
	char *line;
	char *to_parse;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		to_parse = get_label(line);
		if (to_parse)
		{
			delete_comment(to_parse);

		}
		ft_memdel((void**)&line);
	}
}