//
// Created by professor on 28.11.19.
//
#include "../assembler.h"

t_command*	get_args(char *line)
{
	char **args = ft_strsplit(line, ',');
	char **it = args;
	t_command *command;

	command = (t_command*)ft_memalloc(sizeof(t_command));
	while (*it)
	{
		ft_strtrim(*it);
		it++;
	}
	command->args = args;
	return (command);
}
