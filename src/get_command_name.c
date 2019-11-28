//
// Created by professor on 28.11.19.
//
#include "../assembler.h"

int 	is_command(const char *it_begin, const char *it_end)
{
	char *comamnds[COMMANDS_NUM] = {"live", "ld" ,"st","add", "sub", "and", "or", "xor",
									"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	int		i;

	i = -1;
	while (++i < COMMANDS_NUM)
	{
		if (!ft_strncmp(comamnds[i], it_begin, it_end - it_begin))
			return (i);
	}
	return (-1);
}


int	 get_command_name(char **line)
{
	char	*end;
	char	*begin;

	end = ft_strtrim(*line);
	begin = end;
	while (*end && *end != '\t' && *end != ' ' && *end != '%')
		end++;
	*line = end;
	return (is_command(begin, end));
}
