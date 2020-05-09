/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:58:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/09 23:10:38 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	draw_horiz_line(int y, int x, int len, char symb)
{
	int i;

	i = -1;
	move(y, x);
	while (++i < len)
	{
		addch(symb);
		refresh();
	}
}

void	draw_vert_line(int y, int x, int len, char symb)
{
	int i;

	i = -1;
	while (++i < len)
		mvaddch(y + i, x, symb);
	refresh();
}

void 	draw_one_byte(unsigned char byte, int color)
{
	if (color)
		attron(COLOR_PAIR(color));

	addch(HEX[byte / 16]);
	addch(HEX[byte % 16]);
	refresh();
}

void	draw_bytes(unsigned char *arena, int len, int color, int cur_line)
{
	int	i;

	if (color)
		attron(COLOR_PAIR(color));
	i = -1;
	while (++i < len)
	{
		if (i && !(i % 64))
			move(++cur_line, 2);
		draw_one_byte(arena[i], 0);
		addch(' ');
	}
}
