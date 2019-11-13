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
	char *result = ft_strnew(8);
	int i = -1;

	while (++i < 8) {
		result[8 - i - 1] = (n % (int)2) + '0';
		n /= 2;
	}
	return result;
}

void	commands_array_init(void)
{
	static char *commands[16] = {"live", "ld", "st", "add", "sub", "and", "or", "xor", "zjmp", "ldi", "sti", "fork",
	"lld", "lldi", "lfork", "aff"};
	int i = -1;

	while (++i < 16)
		g_commands[i] = create_pair(ft_strdup(commands[i]), dec_to_bin(i + 1));
	i = -1;
	while (++i < 16)
		printf("command: |%s| bin_to_dec: |%s|\n", g_commands[i]->key, g_commands[i]->value);
}



void	parse(int fd)
{
	char *line;

	line = NULL;
	commands_array_init();
	/*while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
	}*/
}