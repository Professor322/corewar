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

#include "../assembler.h"


void	delete_comment(char *line)
{
	char  *comment_start = ft_strchr(line, '#');

	if (comment_start)
		*comment_start = '\0';
}

/**
 * написать функицю трим, которая не будет выделять память для нового указателя
 */

/**
 * написать юнит тесты для проверки каждого аспекта парсинга +
 */


t_label		*create_label(char *name, t_b_command *command)
{
	t_label *label;

	label = (t_label*)ft_memalloc(sizeof(t_label));
	label->name = name;
	label->command = command;
	return (label);
}

void	parse(int fd)
{
	char *line;
	char *var_line;
	t_ht *labels = ft_ht_init();
	char *label;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		var_line = line;
		delete_comment(line);
		label = get_label(&var_line);

		get_command_name(&var_line);
		get_args(var_line);
		/// функцию получения имени и аргументов дописат
		ht_insert_label(label, /*функция, возвращающая t_b_command;
 * 								они принимает результаты get_command_name и get_args*/);

		ft_memdel((void**)&line);
	}
}