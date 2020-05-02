/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:39:01 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 20:32:54 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define HEX "0123456789abcdef"

int 	clean_all(t_cbox *cbox, char code_exit)
{
//	size_t j;
	int 	i;

	i = -1;
	while (++i < SIZE_OF_EVENTLOOP)
		ft_vdel(&cbox->eventloop[i]);
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		free(cbox->champs[i].name);
		free(cbox->champs[i].comm);
	}
	ft_vdel(&cbox->dead_cars);
//	j = 0;
//	while(j < cbox->cars->len)
//	{
//		free(&((t_car **)cbox->cars->cont)[i]);
//	}
//	ft_vdel(&cbox->dead_cars);
//	if (!code_exit)
//		ft_printf("\n{GREEN}success\033[00m\n");
//	else
//		ft_printf("\n{RED}%c\033[00m\n", code_exit);
	return code_exit;
}

void	dump_arena(unsigned char *arena)
{
	int i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!i)
			ft_printf("0x%#.4x : ", i);
		else if (!(i % 64))
			ft_printf("\n%#.4x : ", i);
		ft_printf("%c%c ", HEX[arena[i] / 16], HEX[arena[i] % 16]);
//		ft_printf("%08b ", arena[i]);
	}
	ft_printf("\n");
}