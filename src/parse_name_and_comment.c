//
// Created by Virgil Legros on 17/01/2020.
//

#include "../assembler.h"

int	parse_name(int fd, t_champ *champ)
{
	char *line;
	char *unstable_line;
	char *name_start;
	char *name_end;

	line = NULL;
	get_next_line(fd, &line);
	unstable_line = line;
	skip_spaces(&unstable_line);
	if (!*line || *line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return (0);
	if (!ft_strncmp(unstable_line, NAME_CMD_STRING, NAME_CMD_LEN))
	{
		if (*(unstable_line + NAME_CMD_LEN + 1) != QUOTE &&
			!ft_isspace(*(unstable_line + NAME_CMD_LEN + 1)))
		{
			///error
		}
		if ((name_start = ft_strchr(unstable_line, QUOTE)))
			name_start += 1;
		if (unstable_line + 1 && (name_end = ft_strchr(unstable_line + 1, QUOTE)))
			name_end -= 1;
		if (name_start && name_end)
		{
			*name_end = END_LINE;
			champ->name = ft_strdup(name_start);
			if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
			{
				///error
			}
			return (1);
		}
		else
		{
			///error
		}
	}
	return (0);
}