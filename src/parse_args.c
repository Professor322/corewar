//
// Created by professor on 15.03.20.
//

#include "../includes/assembler.h"

int 	check_starter_token(const char starter)
{
	if (starter == DIRECT_CHAR)
		return (1);
	if (starter == REGISTER_CHAR)
		return (1);
	if (starter == LABEL_CHAR)
		return (1);
	if (ft_isdigit(starter) || starter == '-')
		return (1);
	return (0);
}

char 	*create_arg(char **line, const char *arg_start, char *arg_end)
{
	char *arg;
	const char chr = *arg_end;

	*arg_end = END_LINE;
	arg = ft_strdup(arg_start);
	*arg_end = chr;
	*line = *arg_end && *arg_end != COMMENT_CHAR ? arg_end : NULL;
	return arg;
}

char 	*check_arg_content(char **line)
{
	const char *arg_start = *line;
	char *arg_end;

	arg_end = *line;
	if (*arg_end == REGISTER_CHAR || *arg_end == DIRECT_CHAR)
		arg_end = (char*)arg_start + 1;
	if (!*arg_end)
		return NULL;
	if (*arg_end == LABEL_CHAR)
	{
		arg_end++;
		while (*arg_end && ft_strchr(LABEL_CHARS, *arg_end))
			arg_end++;
	}
	else
		while (*arg_end && (ft_isdigit(*arg_end) || *arg_end == '-'))
			arg_end++;
	if (*arg_end && !ft_isspace(*arg_end) &&
			*arg_end != SEPARATOR_CHAR &&
			*arg_end != COMMENT_CHAR)
		return NULL;

	return (create_arg(line, arg_start, arg_end));
}

char 	*parse_arg(char **line, const int arg_num)
{
	char *arg;

	if (!*line)
		return NULL;
	if (arg_num >= 1 && **line != SEPARATOR_CHAR)
		return NULL;
	if (arg_num >= 1)
		(*line)++;
	skip_spaces(line);
	if (*line && !check_starter_token(**line))
		return NULL;
	if (!(arg = check_arg_content(line)))
		return NULL;
	skip_spaces(line);
	return arg;
}

char 	**parse_args(t_champ **champ_ptr, char *line, const int cmd)
{
	int i;
	const int len = g_commands[cmd].num_of_args;
	char **args;
	char *temp;

	line = line + g_commands[cmd].name_len;
	if(!(args = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		error_manager(MALLOC_ERROR, champ_ptr);
	i = 0;
	while((temp = parse_arg(&line, i)))
	{
		if (i == g_commands[cmd].num_of_args)
		{
			ft_memdel((void**)&temp);
			ft_del_twodem_arr((void***)&args);
			error_manager(WRONG_NUMBER_OF_ARGS, champ_ptr);
		}
		args[i] = temp;
		i++;
	}
	if (i < len)
	{
		ft_del_twodem_arr((void***)&args);
		error_manager(WRONG_NUMBER_OF_ARGS, champ_ptr);
	}
	args[i] = NULL;
	return args;
}
