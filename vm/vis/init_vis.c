/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:36:18 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 00:03:03 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	draw_start_screen(t_cbox *cbox)
{
	int	width;
	int heigth;

	if (!cbox)
		return ;
	attron(COLOR_PAIR(2));
	width = 3 + 2 * PADDING_ARENA + WIDTH_ARENA + WIDTH_STAT;
	heigth = 2 + 2 * PADDING_ARENA + HEIGHT_ARENA;
	draw_horiz_line(0, 0, width, '#');
	draw_horiz_line(heigth - 1, 0, width, '#');
	draw_vert_line(1, 0, heigth - 2, '#');
	draw_vert_line(1, START_STATS - 1, heigth - 2, '#');
	draw_vert_line(1, width - 1, heigth - 2, '#');

	move(1 + PADDING_ARENA, 1 + PADDING_ARENA);
	draw_bytes(cbox->arena.arena, MEM_SIZE, 1, 1 + PADDING_ARENA);

	draw_horiz_line(HEIGHT_STAT_ARENA, START_STATS, WIDTH_STAT, '#');
	move(HEIGHT_STAT_ARENA + PADDING_STATS, START_STATS + PADDING_STATS);
	printw("CHAMPIONS");
}

void	draw_start_champion(int number, int start_cell, t_cbox *cbox)
{
	int line;
	int raw;

	start_cell = start_cell % MEM_SIZE;
	line = start_cell / ARENA_IN_BYTES + PADDING_ARENA + 1;
	raw = start_cell % ARENA_IN_BYTES * CELLS_PER_BYTE + PADDING_ARENA + 1;
	attron(COLOR_PAIR(10 + number));
	mvprintw(4 + number, WIDTH_ARENA + 6, "cell %d, line %d, raw %d", start_cell, line, raw);
	move(line, raw);
	draw_bytes(&cbox->arena.arena[start_cell], cbox->champs[number].code_size, 10 + number, line);
	move(HEIGHT_STAT_ARENA + PADDING_STATS + number * HEIGHT_STAT_CHAMP, START_STATS + PADDING_STATS);
	printw("%s", cbox->champs[number].name);
	move(HEIGHT_STAT_ARENA + PADDING_STATS + number * HEIGHT_STAT_CHAMP + 1, START_STATS + PADDING_STATS);
	printw("%s", cbox->champs[number].comm);

}

void	init_vis(t_cbox *cbox)
{
	initscr();
//	cbreak();
	noecho();
	clear();

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(10, COLOR_GREEN, COLOR_BLACK);
	init_pair(11, COLOR_CYAN, COLOR_BLACK);
	init_pair(12, COLOR_YELLOW, COLOR_BLACK);
	init_pair(13, COLOR_BLUE, COLOR_BLACK);

	draw_start_screen(cbox);
}

void	exit_vis(void)
{
	getch();
	endwin();
}
