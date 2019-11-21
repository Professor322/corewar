/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:39:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/21 17:19:44 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define HEX "0123456789abcdef"

int 	clean_all(s_arena *arena, char code_exit)
{
	free(arena);
	return (code_exit);
}

void	dump_arena(char *arena)
{
	int i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_printf("%c%c ", HEX[arena[i] / 16], HEX[arena[i] % 16]);
		if (!i || !((i + 1) % 64))
			ft_printf("\n%#.4x : ", i + 1);

	}
}
