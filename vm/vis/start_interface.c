/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:00:58 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 22:03:19 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	draw_commands(void)
{
	move(COMM_ST_Y, STATS_ST_X);
	printw("go to next step");
	move(COMM_ST_Y, COMM_ST_X_2);
	printw("<ENTER>");
	move(COMM_ST_Y + 1, STATS_ST_X);
	printw("run / pause");
	move(COMM_ST_Y + 1, COMM_ST_X_2);
	printw("<SPACE>");
	call_it_pause(1);
	move(COMM_ST_Y + 2, STATS_ST_X);
	printw("skip empty cycles");
	move(COMM_ST_Y + 2, COMM_ST_X_2);
	printw("<S>");
	call_it_skip_cycles(0);
}

static void	draw_statistic()
{
	move(STATS_ST_Y + 1, STATS_ST_X);
	printw("last alive:");
	move(STATS_ST_Y + 2, STATS_ST_X);
	printw("cycle:");
	move(STATS_ST_Y + 2, STATS_ST_X_2);
	printw("%d", 0);
	move(STATS_ST_Y + 4, STATS_ST_X_2);
	printw("overall");
//	move(STATS_ST_Y + 5, STATS_ST_X);
//	printw("undefined");
//	move(STATS_ST_Y + 5, STATS_ST_X_2);
//	printw("%3d", 0);
}

static void	draw_start_screen(t_cbox *cbox)
{
	attron(COLOR_PAIR(2));
	draw_horiz_line(0, 0, ALL_W, '#');
	draw_horiz_line(ALL_H - 1, 0, ALL_W, '#');
	draw_vert_line(1, 0, ALL_H - 2, '#');
	draw_vert_line(1, STATS_ST_X - STATS_PADDING - 1, ALL_H - 2, '#');
	draw_vert_line(1, ALL_W - 1, ALL_H - 2, '#');
	draw_horiz_line(STATS_ST_Y - STATS_PADDING - 1, STATS_ST_X, STATS_W, '#');
	draw_horiz_line(CHAMP_ST_Y - STATS_PADDING - 1, STATS_ST_X, STATS_W, '#');
	attroff(COLOR_PAIR(2));

	draw_commands();
	move(STATS_ST_Y - 1, STATS_ST_X);
	printw("ARENA");
	draw_statistic();
	move(CHAMP_ST_Y - 1, STATS_ST_X);
	printw("CHAMPIONS");

	move(ARENA_ST, ARENA_ST);
	draw_bytes((t_draw_bytes){cbox->arena.arena, 0, MEM_SIZE, ARENA_ST}, 0);
}

void	start_interface(t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, FALSE);
	cbox->vbox.pause = 1;
	noecho();
	clear();

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_GREEN, COLOR_BLACK);
	init_pair(11, COLOR_CYAN, COLOR_BLACK);
	init_pair(12, COLOR_YELLOW, COLOR_BLACK);
	init_pair(13, COLOR_BLUE, COLOR_BLACK);
	init_pair(20, COLOR_WHITE, COLOR_GREEN);
	init_pair(21, COLOR_WHITE, COLOR_CYAN);
	init_pair(22, COLOR_WHITE, COLOR_YELLOW);
	init_pair(23, COLOR_WHITE, COLOR_BLUE);

	draw_start_screen(cbox);
	catch_keyboard(&cbox->vbox);
}
