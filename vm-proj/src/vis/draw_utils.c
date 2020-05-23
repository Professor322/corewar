/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:58:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 19:46:53 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm-proj/includes/corewar.h"

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

int		move_to_cell(unsigned int cell)
{
	int line;
	int raw;

	cell = cell % MEM_SIZE;
	line = cell / ARENA_IN_BYTES + ARENA_ST;
	raw = cell % ARENA_IN_BYTES * CELLS_PER_BYTE + ARENA_ST;
	move(line, raw);
	return (line);
}

void	clear_line(int offset)
{
	mvprintw(offset, STATS_X, "%*s", STATS_W, "");
	refresh();
}
