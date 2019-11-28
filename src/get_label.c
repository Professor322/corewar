//
// Created by professor on 28.11.19.
//
#include "../assembler.h"

int		is_label(const char *it_begin, const char *it_end)
{
	if (it_end)
	{
		while (it_begin != it_end)
		{
			if (*it_begin == ' ' || *it_begin == '\t')
				return (0);
			it_begin++;
		}
		return (1);
	}
	return (0);
}

char	*get_label(char **line)
{
	char  *end_of_label = ft_strchr(*line, ':');
	char	*label;

	if (is_label(*line, end_of_label))
	{
		*end_of_label = '\0';
		label = ft_strdup(*line);
		*line = (end_of_label + 1) && *(end_of_label + 1) != '\0' ?
				end_of_label + 1 : NULL;
		return (label);
	}
	return (NULL);
}
