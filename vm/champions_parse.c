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

void    reverse_int(unsigned int *to_reverse)
{
    unsigned char   *original;
	int				i;
	unsigned char   tmp;

	original = (unsigned char *)to_reverse;
	i = -1;
	while (++i < 2)
    {
	    tmp = original[i];
	    original[i] = original[3 - i];
	    original[3 - i] = tmp;
    }
}

char    *invalid_champion(t_champ *champ)
{
    reverse_int(&champ->magic);
    if (champ->magic != COREWAR_EXEC_MAGIC)
        return "Error: File %s has an invalid header";
    if (champ->comm[COMMENT_LENGTH] != 0)
        return "Error: "; // todo
    if (champ->name[PROG_NAME_LENGTH] != 0)
        return "Error: "; // todo
    reverse_int(&champ->code_size);
    if (champ->code_size > CHAMP_MAX_SIZE)
    {
        ft_printf("Champion size limit is %d. ", CHAMP_MAX_SIZE);
        return "File %s size exceed max limit";
    }
    return NULL;
}


char    *get_champion(int fd, t_champ *champ, unsigned char *place)
{
    int             real_size;
    char            *error;

    real_size = read(fd, champ, HEADER_SIZE);
    if (real_size < HEADER_SIZE)
        return "Error: File %s is too small to be a champion";
    if ((error = invalid_champion(champ)))
        return error;
    real_size = read(fd, place, champ->code_size);
    if (real_size != champ->code_size)
        return "Error: File %s has a code size that differs from what its header says";
    return NULL;
}


void	init_champion(char *file, t_cbox *cbox, int cell, t_champ *champ)
{
	int     fd;
	char    *msg;

	if ((fd = open(file, O_RDONLY)) < 0)
		exit(clean_all(cbox, INPUT_ERROR));
	else
	{
	    if ((msg = get_champion(fd, champ, &(cbox->arena.arena[cell]))))
		    cw_exit(cbox, msg, file);
		close(fd);
	}
}

