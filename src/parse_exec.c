//
// Created by Virgil Legros on 02/03/2020.
//

#include "../assembler.h"


void	parse_label(t_champ **champ_ptr, char **line, char *label_end)
{
	char *label;
	t_champ *champ;

	champ = *champ_ptr;
	*label_end = END_LINE;
	if (!(label = ft_strdup(*line)))
		error_manager(MALLOC_ERROR, champ_ptr);
	ft_ptr_vec_pushback(champ->temp_labels, label);
	*line = label_end + 1 && *(label_end + 1) ? label_end + 1 : NULL;
}

void 	parse_exec(t_champ **champ_ptr)
{
	char	*lbl;
	int 	cmd;
	t_champ *champ;
	char 	*line;

	champ = *champ_ptr;
	if (!champ->line)
		return ;
	line = champ->line;
	skip_spaces(&line);
	if (!*line || *line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return ;
	cmd = is_command(&line);
	if (cmd < 0)
	{
		if (!(lbl = is_label(line)))
			error_manager(INCORRECT_SYNTAX, champ_ptr);
		parse_label(champ_ptr, &line, lbl);
	}
	skip_spaces(&line);
	if (line && *line && *line != COMMENT_CHAR && *line != ALT_COMMENT_CHAR)
	{
		cmd = is_command(&line);
		if (cmd < 0)
			error_manager(NON_EXISTING_COMMAND, champ_ptr);
		compile_command(champ_ptr, cmd, parse_args(champ_ptr, line, cmd));
	}
}
