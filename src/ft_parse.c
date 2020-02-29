//
// Created by Virgil Legros on 16/01/2020.
//
#include "../assembler.h"

///не менять порядок
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
	while (**line && ft_isspace(**line))
		(*line)++;
}

void 	get_exec_line(t_champ *champ, char *line)
{
	char	*lbl;
	int		cmd;

	if (!line)
		return ;
	skip_spaces(&line);
	if (!*line || *line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return ;
	if ((lbl = is_label(line)))
		parse_label(champ, &line, lbl);
	if (line && (cmd  = is_command(&line)) >= 0)
		compile_command(cmd, parse_command(line, cmd), champ);
}


void	get_exec(int fd, t_champ *champ)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		get_exec_line(champ, line);
		ft_memdel((void**)&line);
	}
}

void 	ft_parse(int fd, t_champ *champ)
{
	get_header(fd, champ);
	get_exec(fd, champ);
}

