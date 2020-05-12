/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:00:58 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/13 00:12:24 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	draw_commands(t_vbox *vbox)
{
	mvprintw(COMM_ST + NEXT_H, STATS_X, "go to next step");
	mvprintw(COMM_ST + NEXT_H, STATS_X_3, "ENTER");
	mvprintw(COMM_ST + PAUSE_H, STATS_X, "run / pause");
	mvprintw(COMM_ST + PAUSE_H, STATS_X_3, "SPACE");
	call_it_pause(vbox->pause);
	mvprintw(COMM_ST + DOWNTIME_H, STATS_X, "set downtime");
	mvprintw(COMM_ST + DOWNTIME_H, STATS_X_3, "left / right");
	call_downtime(vbox->downtime, DOWNTIME_H);
	mvprintw(COMM_ST + CH_DOWNTIME_H, STATS_X, "set downtime on check");
	mvprintw(COMM_ST + CH_DOWNTIME_H, STATS_X_3, "up / down");
	call_downtime(vbox->downtime_on_check, CH_DOWNTIME_H);
	mvprintw(COMM_ST + SKIP_H, STATS_X, "skip empty cycles");
	mvprintw(COMM_ST + SKIP_H, STATS_X_3, "S");
	call_it_skip_cycles(vbox->skip_cycles);
}

static void	draw_main(t_cbox *cbox)
{
	mvprintw(MAIN_ST + LAST_H, STATS_X, "last alive:");
	mvprintw(MAIN_ST + CYCLE_H, STATS_X, "cycle:");
	mvprintw(MAIN_ST + CYCLE_H, STATS_X_2, "%d", 0);
	mvprintw(MAIN_ST + ALIVES_H, STATS_X_2, "ALIVE PROCESSES");
	count_to_check(cbox->arena.cycles_to_die);
}

static void	draw_start_screen(t_cbox *cbox)
{
	attron(COLOR_PAIR(2));
	draw_horiz_line(0, 0, ALL_W, '#');
	draw_horiz_line(ALL_H - 1, 0, ALL_W, '#');
	draw_vert_line(1, 0, ALL_H - 2, '#');
	draw_vert_line(1, STATS_X - STATS_PADDING - 1, ALL_H - 2, '#');
	draw_vert_line(1, ALL_W - 1, ALL_H - 2, '#');
	draw_horiz_line(LOG_BAR, STATS_X, STATS_W, '#');
	draw_horiz_line(MAIN_BAR, STATS_X, STATS_W, '#');
	draw_horiz_line(CHAMP_BAR, STATS_X, STATS_W, '#');
	attroff(COLOR_PAIR(2));

	draw_commands(&cbox->vbox);
	mvprintw(LOG_ST - 2, STATS_X, "LOG");
	draw_main(cbox);
//	mvprintw(CHAMP_ST - 1, STATS_X, "CHAMPIONS");

	move(ARENA_ST, ARENA_ST);
	draw_bytes((t_draw_bytes){cbox->arena.arena, 0, MEM_SIZE, ARENA_ST}, 0);
}

static void		init_colors(void)
{
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
	cbox->vbox.downtime = 10000;
	cbox->vbox.downtime_on_check = 1000000;
	noecho();
	clear();

	init_colors();
	draw_start_screen(cbox);
	catch_keyboard(&cbox->vbox);
}
