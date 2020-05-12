/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:58:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/11 00:46:58 by mbartole         ###   ########.fr       */
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
	if (color)
		attroff(COLOR_PAIR(color));
	refresh();
}

void	draw_bytes(t_draw_bytes draw, int color)
{
	unsigned int	i;
	int 			first;

	i = draw.start;
	first = 1;
	while (i < draw.start + draw.len)
	{
		if (i >= MEM_SIZE)
		{
			i = i % MEM_SIZE;
			draw.cur_line = ARENA_ST;
		}
		if (!first && !(i % ARENA_IN_BYTES))
			move(++draw.cur_line, ARENA_ST);
		draw_one_byte(draw.arena[i], color);
		addch(' ');
		i++;
		first = 0;
	}
}

int		move_to_cell(unsigned int cell)
{
	int line;
	int raw;

	cell = cell % MEM_SIZE;
	line = cell / ARENA_IN_BYTES + ARENA_ST;
	raw = cell % ARENA_IN_BYTES * CELLS_PER_BYTE + ARENA_ST;
//	if (cell && !(cell % ARENA_IN_BYTES))
//		line--;
	move(line, raw);
	return (line);
}
