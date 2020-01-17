//
// Created by Virgil Legros on 16/01/2020.
//
#include "../assembler.h"

t_command g_commands[COMMANDS_NUM] = {
		{"live", 4, 1, live},
		{"ld",   2, 2, ld},
		{"st",   2, 2, st},
		{"add",  3, 3, add},
		{"sub",  3, 3, sub},
		{"and",  3,3, and},
		{"or",   2, 3, or},
		{"xor",  3, 3, xor},
		{"zjmp", 4, 1, zjmp},
		{"ldi",  3, 3, ldi},
		{"sti",  3, 3, sti},
		{"fork", 4, 1, ft_fork},
		{"lld", 3, 2, lld},
		{"lldi", 4, 3, lldi},
		{"lfork", 5, 2, lfork},
		{"aff", 3, 2, aff}
};

t_champ *champ_init()
{
	t_champ	*champ;

	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	champ->temp_labels = ft_ptr_vec_init();
	champ->file_labels = ft_ptr_vec_init();
	champ->labels = ft_ht_init();
	return (champ);
}

void 	skip_spaces(char **line)
{
	char *ln;

	ln = *line;
	while (ft_isspace(*ln))
		ln++;
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
	if ((cmd  = is_command(&line)))
	{

	}
}

void 	ft_parse(int fd, t_champ *champ)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		get_line(champ, line);
		ft_memdel((void**)&line);
	}
}
