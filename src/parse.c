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
 *
 * написать юнит тесты для проверки каждого аспекта парсинга +
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