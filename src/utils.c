//
// Created by Virgil Legros on 16/01/2020.
//
#include "../includes/assembler.h"

t_command g_commands[COMMANDS_NUM] = {
		{"live", 4, 1, live},
		{"lldi", 4, 3, lldi},
		{"lld", 3, 2, lld},
		{"ldi",  3, 3, ldi},
		{"ld",   2, 2, ld},
		{"sti",  3, 3, sti},
		{"st",   2, 2, st},
		{"add",  3, 3, add},
		{"sub",  3, 3, sub},
		{"and",  3,3, and},
		{"or",   2, 3, or},
		{"xor",  3, 3, xor},
		{"zjmp", 4, 1, zjmp},
		{"fork", 4, 1, ft_fork},
		{"lfork", 5, 1, lfork},
		{"aff", 3, 1, aff}
};

t_header g_header[2] = {
		{NAME_CMD_STRING, NAME_CMD_LEN, PROG_NAME_LENGTH},
		{COMMENT_CMD_STRING, COMMENT_CMD_LEN, COMMENT_LENGTH}
};

void 	skip_spaces(char **line)
{
	if (!*line)
		return ;
	while (**line && ft_isspace(**line))
		(*line)++;
}

int 	read_line(t_champ **champ_ptr)
{
	const int value = get_next_line((*champ_ptr)->fd_input, &((*champ_ptr)->line));

	if (value > 0)
		(*champ_ptr)->counter++;
	return value;
}

char		*is_label(char *line)
{
	const char *lb = ft_strchr(line, LABEL_CHAR);

	while (line != lb && ft_strchr(LABEL_CHARS, *line))
		line++;
	return (line == lb ? (char*)lb : NULL);
}

int 	is_command(char **line)
{
	int i;
//	char c;

	i = -1;
	skip_spaces(line);
	while (++i < COMMANDS_NUM)
		if (!ft_strncmp(*line, g_commands[i].name,
				g_commands[i].name_len)) {
		//	c = *(*line + g_commands[i].name_len);

			return (i);
		}
	return (-1);
}
