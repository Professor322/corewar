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

t_pair	*create_pair(char *command_name, char *byte_code)
{
	t_pair *pair;

	if (!(pair = (t_pair *) malloc(sizeof(t_pair))))
		return (NULL);
	pair->key = command_name;
	pair->value = byte_code;
	return (pair);
}

char	*dec_to_bin(int n) {
	char *result = ft_strnew(BYTE);
	int i = -1;

	while (++i < BYTE) {
		result[BYTE - i - 1] = (n % (int)2) + '0';
		n /= 2;
	}
	return result;
}

void	commands_array_init(void)
{
	static char *commands[COMMANDS_NUM] = {"live", "ld", "st", "add", "sub", "and", "or", "xor", "zjmp", "ldi", "sti", "fork",
	"lld", "lldi", "lfork", "aff"};
	int i = -1;

	while (++i < COMMANDS_NUM)
		g_commands[i] = create_pair(ft_strdup(commands[i]), dec_to_bin(i + 1));

	/*
	i = -1;
	while (++i < 16)
		printf("command: |%s| bin_to_dec: |%s|\n", g_commands[i]->key, g_commands[i]->value);*/
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


int	command_or_label(char *line)
{
	int i;
	size_t len = ft_strlen(line);

	i = -1;
	while ((size_t)++i < len)
	{
		/**
		 *  возвращаем структуру, где первое значение типа bool: 1 - метка, 0 - команда
		 *  если метка, вернуть значение метки
		 *  если команда, вернуть преобразованное значение
		 */
		if (line[i] == ':') {
			/**
			 * проверить, что стоит дальше: либо команда, либо конец строки
			 * если команда, то ее в функицю обработки
			 * если пустая строка закончить чтение
			 * вернуть значение метки (?)
			 */
			return (1);
		} else if (line[i] == '%' || line[i] == ' ') {
			/**
			 * отправить в функцию обработки команды (?)
			 * вернуть преобразованное в байт код значение
			 */
			return (0);
		}
	}
}

void	parse(int fd)
{
	char *line;

	line = NULL;
	commands_array_init();
	int i = 1;
	while (get_next_line(fd, &line))
	{
		printf("line: %d %d\n",i++,command_or_label((line)));
	}
}