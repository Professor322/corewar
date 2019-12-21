/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:39:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/23 18:24:24 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define HEX "0123456789abcdef"

int 	clean_all(t_cbox *cbox, char code_exit)
{
	// TODO clean: arena->arena, timeline[i], champs[i]->code
	return (code_exit);
}

void	dump_arena(unsigned char *arena)
{
	int i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!(i % 64))
			ft_printf("\n%#.4x : ", i);
//		ft_printf("%c%c ", HEX[arena[i] / 16], HEX[arena[i] % 16]);
		ft_printf("%08b ", arena[i]);
	}
}