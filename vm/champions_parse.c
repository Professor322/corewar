/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:07:38 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/10 23:21:17 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					get4byte(t_cbox *cbox, int fd)
{
	size_t			size;
	unsigned char	buffer[4];
	int				i;

	i = 4;
	size = 0;
	while (--i >= 0)
		size += read(fd, &buffer[i], 1);
	if (size < 4)
		clean_all(cbox, INPUT_ERROR);
	return (*(int*)buffer);
}

char				*get_str(int fd, size_t len, t_cbox *cbox)
{
	int				size;
	char			*buffer;

	if (!(buffer = (char*)malloc(sizeof(char) * (len + 1))))
		clean_all(cbox, MALLOC_ERROR);
	size = read(fd, buffer, len);
	if (size < (int)len)
		clean_all(cbox, INPUT_ERROR); // exact size
	buffer[size] = '\0';
	return (buffer);
}

unsigned char		*get_code(int fd, size_t len, t_cbox *cbox)
{
	int				size;
	unsigned char	*buffer;

	if (!(buffer = (unsigned char*)malloc(sizeof(char) * len)))
		clean_all(cbox, MALLOC_ERROR);
	size = read(fd, buffer, len);
	if (size < (int)len || (read(fd, buffer, len) != 0))
		clean_all(cbox, INPUT_ERROR);  // exact size, end of file
	return (buffer);
}

void	init_champion(int fd, t_cbox *cbox, int i)
{
	int code_size;

	if (get4byte(cbox, fd) != COREWAR_EXEC_MAGIC) // magic header
		clean_all(cbox, INPUT_ERROR);
	cbox->champs[i].name = get_str(fd, 128, cbox);  // name
	if (get4byte(cbox, fd) != 0)
		clean_all(cbox, INPUT_ERROR);  // null
	code_size = get4byte(cbox, fd);  // code size
	if (code_size > CHAMP_MAX_SIZE)
		clean_all(cbox, INPUT_ERROR);
	cbox->champs[i].code_size = code_size;
	cbox->champs[i].comm = get_str(fd, COMMENT_LENGTH, cbox); // comment
	if (get4byte(cbox, fd) != 0)
		clean_all(cbox, INPUT_ERROR);  // null
	cbox->champs[i].code = get_code(fd, code_size, cbox); // exec code
}
