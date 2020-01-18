//
// Created by Virgil Legros on 16/01/2020.
//
#include "../assembler.h"

///не менять порядок
t_command g_commands[COMMANDS_NUM] = {
		{"live", 4, 1, live},
		{"lldi", 4, 3, lldi},
		{"lld", 3, 2, lld},
		{"ld",   2, 2, ld},
		{"sti",  3, 3, sti},
		{"st",   2, 2, st},
		{"add",  3, 3, add},
		{"sub",  3, 3, sub},
		{"and",  3,3, and},
		{"or",   2, 3, or},
		{"xor",  3, 3, xor},
		{"zjmp", 4, 1, zjmp},
		{"ldi",  3, 3, ldi},
		{"fork", 4, 1, ft_fork},
		{"lfork", 5, 1, lfork},
		{"aff", 3, 2, aff}
};

void 	skip_spaces(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

void 	get_line(t_champ *champ, char *line)
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
		get_line(champ, line);
		ft_memdel((void**)&line);
	}
}

void 	ft_parse(int fd, t_champ *champ)
{
	get_exec(fd, champ);
}

