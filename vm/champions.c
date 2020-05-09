/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:31:34 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/09 21:31:37 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	greet_champions(t_cbox *cbox)
{
	int	i;

	if (cbox->flags & VIS_FLAG_EXIST)
		return ;
	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < MAX_PLAYERS)
		if (cbox->champs[i].code_size)
			ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
					i + 1, cbox->champs[i].code_size,
					cbox->champs[i].name, cbox->champs[i].comm);
}

int		count_champions(t_champ *champs)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (++i < MAX_PLAYERS)
		if (champs[i].code_size)
			n++;
	return (n);
}

void	greet_winner(t_cbox *cbox)
{
	t_champ champ;

	champ = cbox->champs[cbox->arena.last_alive - 1];
	if (cbox->flags & VIS_FLAG_EXIST)
		return ;
	ft_printf("Contestant %d, \"%s\", has won !\n",
			cbox->arena.last_alive, champ.name);
}
