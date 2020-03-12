/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:31:34 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/12 22:14:18 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	get_champion(char *file, t_champ *champ, int i, t_cbox *cbox)
{
	int fd;

	if (file == NULL)
		exit(clean_all(cbox, INPUT_ERROR));
	if ((fd = open(file, O_RDONLY)) < 0)
		exit(clean_all(cbox, INPUT_ERROR));
	champ->id = i + 1;
	init_champion(fd, cbox, i);
	close(fd);
}

void	greet_champions(t_champ *champs, int size)
{
	int 	i;

	ft_printf("{YELLOW}Introducing contestants...\033[00m\n\n");
	i = -1;
	while (++i < size)
		if (champs[i].id)
			ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
					  champs[i].id, champs[i].code_size,
					  champs[i].name, champs[i].comm);
}

void	greet_winner(t_arena *arena)
{
	t_champ *champ;

	champ = arena->last_alive;
	ft_printf("Player %d, \"%s\", has won !\n", champ->id, champ->name);
}
