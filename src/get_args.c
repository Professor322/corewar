//
// Created by professor on 28.11.19.
//
#include "../assembler.h"

char	**get_args(char *line)
{
	char **args = ft_strsplit(line, ',');
	char **it = args;

	while (*it)
	{
		*it = ft_strtrim(*it);
		it++;
	}
	return (args);
}
