//
// Created by Virgil Legros on 16/01/2020.
//
#include "asm.h"

t_command g_commands[COMMANDS_NUM] = {
		{"live", 4, 1},
		{"ld",   2, 2},
		{"st",   2, 2},
		{"add",  3, 3},
		{"sub",  3, 3},
		{"and",  3,3},
		{"or",   2, 3},
		{"xor",  3, 3},
		{"zjmp", 4, 1},
		{"ldi",  3, 3},
		{"sti",  3, 3},
		{"fork", 4, 1},
		{"lld", 3, 2},
		{"lldi", 4, 3},
		{"lfork", 5, 2},
		{"aff", 3, 2},
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
	if (!*line || *line == COMMENT_CHAR || *line == ALC_COMMENT_CHAR)
		return ;
	if ((lbl = is_label(line)))
		parse_label(champ, &line, lbl);
	if ((cmd  = is_command(&line)))
	{

	}
}

void 	ft_parse(int fd)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{

		ft_memdel((void**)&line);
	}
}
