//
// Created by Virgil Legros on 18/01/2020.
//

#include "../assembler.h"

char	*parse_content(char *line, int fd, enum e_header_token token)
{
	t_cvec *content = ft_chr_vec_init(START_CAP);
	int closing_quote_found;
	char *output;
	const char back_slash = '\n';

	closing_quote_found = FALSE;
	while (!closing_quote_found)
	{
		if (*line != QUOTE) {
			if (*line)
				ft_chr_vec_pushback(content, line++);
			else
			{
				ft_chr_vec_pushback(content, (char*)&back_slash);
				get_next_line(fd, &line);
			}
			int l = g_header[token].len;
			if (content->length > g_header[token].len)
			{
				///error
				break ;
			}
		}
		else
			closing_quote_found = TRUE;
	}
	output = ft_strnew(content->length);
	ft_strcpy(output, content->data);
	ft_chr_vec_del(&content);
	return (output);
}

void	parse_token(t_champ *champ, char *line, int fd, enum e_header_token token)
{
	line = line + g_header[token].token_len;
	skip_spaces(&line);
	if (*line++ == QUOTE)
	{
		if (token == NAME)
			champ->name = parse_content(line, fd, token);
		else if (token == COMMENT)
			champ->comment = parse_content(line, fd, token);
	}
	else
	{
		///error
	}
}

int		get_header_line(t_champ *champ, char *line, int fd)
{
	if (!line)
		return (0);
	skip_spaces(&line);
	if (!*line || *line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return (0);
	if (!ft_strncmp(line, g_header[NAME].token, g_header[NAME].token_len))
	{
		parse_token(champ, line, fd, NAME);
		return (1);
	}
	if (!ft_strncmp(line, g_header[COMMENT].token, g_header[COMMENT].token_len))
	{
		parse_token(champ, line, fd, COMMENT);
		return (1);
	}
	return (0);
}

void	parse_header(t_champ *champ, int fd)
{
	char *line;

	while (!champ->comment && !champ->name && get_next_line(fd, &line))
	{
		if (!get_header_line(champ, line, fd))
			ft_memdel((void**)&line);
	}
}

