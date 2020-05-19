//
// Created by Virgil Legros on 01/03/2020.
//

#include "../includes/assembler.h"

void	add_full_line(t_champ **champ_ptr, t_cvec **content, char **line, const enum e_header_token token)
{
	const char *back_slash = "\n";

	ft_chr_vec_pushback(*content, *line);
	ft_chr_vec_pushback(*content, (char*)back_slash);
	if ((*content)->length > g_header[token].len)
	{
		ft_chr_vec_del(content);
		if (token == COMMENT)
			error_manager(WRONG_LENGTH_OF_COMMENT, champ_ptr);
		else if (token == NAME)
			error_manager(WRONG_LENGTH_OF_NAME, champ_ptr);
	}
	ft_memdel((void**)&((*champ_ptr)->line));
	read_line(champ_ptr);
	*line = (*champ_ptr)->line;
}

void	add_until_quote(t_cvec **content, char **line, char **closing_quote)
{
	**closing_quote = END_LINE;
	ft_chr_vec_pushback(*content, *line);

}

char	*parse_content(t_champ **champ_ptr, char **line, const enum e_header_token token)
{
	t_cvec	*content;
	char	*closing_quote;
	char 	*output;

	closing_quote = NULL;
	if (!(content = ft_chr_vec_init(START_CAP)))
		error_manager(MALLOC_ERROR, champ_ptr);
	while (*line && !closing_quote) {
		if ((closing_quote = ft_strchr(*line, QUOTE)))
			add_until_quote(&content, line, &closing_quote);
		else
			add_full_line(champ_ptr, &content, line, token);
	}
	if (!*line || !(output = ft_strnew(content->length))) {
		ft_chr_vec_del(&content);
		if (!*line)
			error_manager(UNEXPECTED_END_OF_FILE, champ_ptr);
		if (!(output = ft_strnew(content->length)))
			error_manager(MALLOC_ERROR, champ_ptr);
	}
	ft_strcpy(output, content->data);
	ft_chr_vec_del(&content);
	return output;
}

void 	parse_token(t_champ **champ_ptr, const enum e_header_token token, char *line)
{
	t_champ *champ;

	champ = *champ_ptr;
	line  = line + g_header[token].token_len;
	skip_spaces(&line);
	if (*line++ == QUOTE)
	{
		if (token == NAME && !champ->name)
			champ->name = parse_content(champ_ptr, &line, token);
		else if (token == COMMENT && !champ->comment)
			champ->comment = parse_content(champ_ptr, &line, token);
	}
	else
	{
		if (token == NAME)
			error_manager(NO_CHAMP_NAME, champ_ptr);
		else if (token == COMMENT)
			error_manager(NO_CHAMP_COMMENT, champ_ptr);
	}

}

void 	parse_header(t_champ **champ_ptr)
{
	t_champ *champ;
	char *line;

	champ = *champ_ptr;
	if (!champ->line)
		return ;
	line = champ->line;
	skip_spaces(&line);
	if (!*line || *line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return ;
	if (*line == TOKEN_STARTER)
	{
		if (!ft_strncmp(line, g_header[NAME].token,
				g_header[NAME].token_len))
		{
			parse_token(champ_ptr, NAME, line);
			return ;
		} else if (!ft_strncmp(line, g_header[COMMENT].token,
				g_header[COMMENT].token_len))
		{
			parse_token(champ_ptr, COMMENT, line);
			return ;
		} else
			error_manager(UNKNOWN_TOKEN, champ_ptr);
	} else
		error_manager(INCORRECT_SYNTAX, champ_ptr);
}
