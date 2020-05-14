/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:00:58 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/14 23:57:39 by mbartole         ###   ########.fr       */
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
	short	color;

	color = 10 * MY_BLACK + MY_WHITE;
	attron(COLOR_PAIR(color));
	draw_horiz_line(0, 0, ALL_W, '#');
	draw_horiz_line(ALL_H - 1, 0, ALL_W, '#');
	draw_vert_line(1, 0, ALL_H - 2, '#');
	draw_vert_line(1, STATS_X - STATS_PADDING - 1, ALL_H - 2, '#');
	draw_vert_line(1, ALL_W - 1, ALL_H - 2, '#');
	draw_horiz_line(LOG_BAR, STATS_X, STATS_W, '#');
	draw_horiz_line(MAIN_BAR, STATS_X, STATS_W, '#');
	draw_horiz_line(CHAMP_BAR, STATS_X, STATS_W, '#');
	attroff(COLOR_PAIR(color));

	draw_commands(&cbox->vbox);
	mvprintw(LOG_ST - 2, STATS_X, "LOG");
	draw_main(cbox);

	move(ARENA_ST, ARENA_ST);
	draw_bytes((t_draw_bytes){cbox->arena.arena, 0, MEM_SIZE, ARENA_ST}, 10*MY_WHITE+MY_BLACK);
}

static void		init_start_colors(void)
{
	short	colors[7];
	int 	i;
	int 	j;

	start_color();
	colors[1] = COLOR_CYAN;
	colors[2] = COLOR_GREEN;
	colors[3] = COLOR_BLUE;
	colors[4] = COLOR_YELLOW;
	colors[5] = COLOR_WHITE;
	colors[6] = COLOR_BLACK;
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	i = 0;
	while (++i < 7)
	{
		j = 0;
		while (++j < 7) {
			init_pair(10 * i + j, colors[i], colors[j]);
		}
	}
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

	init_start_colors();
	draw_start_screen(cbox);
	catch_keyboard(&cbox->vbox);
}
