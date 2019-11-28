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
	char *comamnds[COMMANDS_NUM] = {"live", "ld" ,"st","add", "sub", "and", "or", "xor",
					   "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	int		i;

	i = -1;
	while (++i < COMMANDS_NUM)
	{
		if (!ft_strncmp(comamnds[i], it_begin, it_end - it_begin))
			return (i);
	}
	return (-1);
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

char	*get_label(char **line)
{
	char  *end_of_label = ft_strchr(*line, ':');
	char	*label;

	if (is_label(*line, end_of_label))
	{
		*end_of_label = '\0';
		label = ft_strdup(*line);
		*line = (end_of_label + 1) && *(end_of_label + 1) != '\0' ?
				end_of_label + 1 : NULL;
		return (label);
	}
	return (NULL);
}

void	delete_comment(char *line)
{
	char  *comment_start = ft_strchr(line, '#');

	if (comment_start)
		*comment_start = '\0';
}


int	 get_command_name(char **line)
{
	char	*end;
	char	*begin;

	end = ft_strtrim(*line);
	begin = end;
	while (*end && *end != '\t' && *end != ' ' && *end != '%')
		end++;
	*line = end;
	return (is_command(begin, end));
}

char	**get_args(char *line)
{
	char **args = ft_strsplit(line, ',');
	char **it = args;

	while (*it)
	{
		*it = ft_strtrim(*it);
		it++;
	}
	return (args);
}

/**
 * написать функицю трим, которая не будет выделять память для нового указателя
 */

/**
 *
 * написать юнит тесты для проверки каждого аспекта парсинга
 */

void	parse(int fd)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		ft_memdel((void**)&line);
	}
}