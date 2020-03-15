/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:07:38 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 19:53:11 by mbartole         ###   ########.fr       */
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
		exit(clean_all(cbox, INPUT_ERROR));
	return (*(int*)buffer);
}

char				*get_str(int fd, size_t len, t_cbox *cbox)
{
	int				size;
	char			*buffer;

	if (!(buffer = (char*)malloc(sizeof(char) * (len + 1))))
		exit(clean_all(cbox, MALLOC_ERROR));
	size = read(fd, buffer, len);
	if (size < (int)len)
		exit(clean_all(cbox, INPUT_ERROR)); // exact size
	buffer[size] = '\0';
	return (buffer);
}

void get_code(int fd, size_t len, t_cbox *cbox, unsigned char *place)
{
	size_t				size;
//	unsigned char	*buffer;

//	if (!(buffer = (unsigned char*)malloc(sizeof(char) * len)))
//		exit(clean_all(cbox, MALLOC_ERROR));
	size = read(fd, place, len);
	if (size < len) //todo: || (read(fd, buffer, len) != 0))
		exit(clean_all(cbox, INPUT_ERROR));  // exact size, end of file
//	return (buffer);
}

void	get_champion(int fd, t_cbox *cbox, t_champ *champ, int cell)
{
	int code_size;

	if (get4byte(cbox, fd) != COREWAR_EXEC_MAGIC) // magic header
		exit(clean_all(cbox, INPUT_ERROR));
	champ->name = get_str(fd, 128, cbox);  // name
	if (get4byte(cbox, fd) != 0)
		exit(clean_all(cbox, INPUT_ERROR));  // null
	code_size = get4byte(cbox, fd);  // code size
	if (code_size > CHAMP_MAX_SIZE)
		exit(clean_all(cbox, INPUT_ERROR));
	champ->code_size = code_size;
	champ->comm = get_str(fd, COMMENT_LENGTH, cbox); // comment
	if (get4byte(cbox, fd) != 0)
		exit(clean_all(cbox, INPUT_ERROR));  // null
//	cbox->champs[i].code = get_code(fd, code_size, cbox); // exec code
	get_code(fd, code_size, cbox, &(cbox->arena.arena[cell]));
//	ft_memmove(&(cbox->arena.arena[cell]), cbox->champs[i].code, cbox->champs[i].code_size);
}

void	init_champion(char *file, t_cbox *cbox, int cell, t_champ *champ)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		exit(clean_all(cbox, INPUT_ERROR));
	else
	{
		get_champion(fd, cbox, champ, cell);
		close(fd);
	}
}
