//
// Created by Virgil Legros on 16/01/2020.
//
#include "../assembler.h"

int 	is_command(char **line)
{
	int i;

	i = -1;
	skip_spaces(line);
	while (++i < COMMANDS_NUM)
		if (!ft_strncmp(*line, g_commands[i].name, g_commands[i].name_len))
			return (i);
	return (-1);
}

char 	*parse_arg(char **line)
{
	char *arg_start;
	char *arg_end;

	arg_start = *line;
	while (ft_isspace(*arg_start))
		arg_start++;
	arg_end = arg_start;
	while (!ft_isspace(*arg_end) &&
		*arg_end != SEPARATOR_CHAR &&
		*arg_end != COMMENT_CHAR &&
		*arg_end != ALT_COMMENT_CHAR)
		arg_end++;
	*line = ft_strchr(*line, SEPARATOR_CHAR) + 1;
	*arg_end = '\0';
	return (ft_strdup(arg_start));
}

char	**parse_command(char *line, const int cmd)
{
	int i;
	char **args;

	line = line + g_commands[cmd].name_len;
	args = (char**)ft_memalloc(sizeof(char*) * g_commands[cmd].num_of_args);
	i = -1;
	while(++i < g_commands[cmd].num_of_args)
		args[i] = parse_arg(&line);
	return (args);
}

t_node	*create_node(char *label, t_b_command *command)
{
	t_node *new_label;

	if (!(new_label = (t_node*)ft_memalloc(sizeof(t_node))))
	{
		///exit
	}
	new_label->name = label;
	new_label->command = command;
	return (new_label);
}

void	compile_command(const int cmd, char **args, t_champ *champ, char *line)
{
	t_b_command *compiled_command =
			g_commands[cmd].func(parse_command(line, cmd), champ);
	while (champ->temp_labels->length)
	{
		ht_insert_node(champ->labels,
				create_node(ft_ptr_vec_popback(champ->temp_labels), compiled_command));
	}
}