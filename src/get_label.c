//
// Created by Virgil Legros on 16/01/2020.
//

#include "../assembler.h"
/*
char		*is_label(char *line)
{
	const char *lb = ft_strchr(line, LABEL_CHAR);

	while (line != lb && ft_strchr(LABEL_CHARS, *line))
		line++;
	return (line == lb ? (char*)lb : NULL);
}*/

void	parse_label(t_champ *champ, char **line, char *label_end)
{
	char *label;

	*label_end = '\0';
	if (!(label = ft_strdup(*line)))
	{
		/// exit
	}
	ft_ptr_vec_pushback(champ->temp_labels, label);
	*line = label_end + 1 && *(label_end + 1) ? label_end + 1 : NULL;
}