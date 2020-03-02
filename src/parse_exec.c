//
// Created by Virgil Legros on 02/03/2020.
//

#include "../assembler.h"

char 	*parse_arg(char **line)
{
	char	*arg_start;
	char	*arg_end;
	char	*sep;

	arg_start = *line;
	while (*arg_start && ft_isspace(*arg_start))
		arg_start++;
	arg_end = arg_start;
	while (*arg_end && !ft_isspace(*arg_end) &&
		   *arg_end != SEPARATOR_CHAR &&
		   *arg_end != COMMENT_CHAR &&
		   *arg_end != ALT_COMMENT_CHAR)
		arg_end++;
	if ((sep = ft_strchr(*line, SEPARATOR_CHAR)))
		*line = sep + 1;
	else
		*line = NULL;
	*arg_end = '\0';
	return (ft_strdup(arg_start));
}

char	**parse_args(t_champ **champ_ptr, char *line, const int cmd)
{
	int i;
	char **args;

	line = line + g_commands[cmd].name_len;
	if(!(args = (char**)ft_memalloc(sizeof(char*) * (g_commands[cmd].num_of_args + 1))))
		error_manager(MALLOC_ERROR, champ_ptr);
	i = -1;
	while(++i < g_commands[cmd].num_of_args)
		args[i] = parse_arg(&line);
	args[i] = NULL;
	return (args);
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
		lbl = is_label(champ_ptr, line);
		parse_label(champ_ptr, &line, lbl);
	}
	if (line)
	{
		cmd = is_command(&line);
		if (cmd < 0)
			error_manager(NON_EXISTING_COMMAND, champ_ptr);

	}

}
