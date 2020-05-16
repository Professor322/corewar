/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:00:58 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 20:09:16 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	draw_commands(t_vbox *vbox)
{
	mvprintw(COMM_ST + NEXT_H, STATS_X, "GO TO NEXT STEP");
	mvprintw(COMM_ST + NEXT_H, STATS_X_3, "ENTER");
	mvprintw(COMM_ST + PAUSE_H, STATS_X, "RUN / PAUSE");
	mvprintw(COMM_ST + PAUSE_H, STATS_X_3, "SPACE");
	call_it_pause(vbox->pause);
	mvprintw(COMM_ST + DOWNTIME_H, STATS_X, "SET DOWNTIME");
	mvprintw(COMM_ST + DOWNTIME_H, STATS_X_3, "LEFT / RIGHT");
	call_downtime(vbox->downtime, DOWNTIME_H);
	mvprintw(COMM_ST + CH_DOWNTIME_H, STATS_X, "SET DOWNTIME ON CHECK");
	mvprintw(COMM_ST + CH_DOWNTIME_H, STATS_X_3, "UP / DOWN");
	call_downtime(vbox->downtime_on_check, CH_DOWNTIME_H);
	mvprintw(COMM_ST + SKIP_H, STATS_X, "SKIP EMPTY CYCLES");
	mvprintw(COMM_ST + SKIP_H, STATS_X_3, "S");
	call_it_skip_cycles(vbox->skip_cycles);
}

static void	draw_main(t_cbox *cbox)
{
	mvprintw(MAIN_ST + LAST_H, STATS_X, "LAST ALIVE:");
	mvprintw(MAIN_ST + CYCLE_H, STATS_X_3, "CYCLE:");
	mvprintw(MAIN_ST + CYCLE_H, STATS_X_2, "%d", 0);
	mvprintw(MAIN_ST + ALIVES_H, STATS_X, "ALIVE PROCESSES");
	mvprintw(MAIN_ST + TO_DIE_H, STATS_X_3, "CYCLES TO DIE:");
	show_cycles_to_die(cbox);
	mvprintw(MAIN_ST + NBR_LIVE_H, STATS_X_3, "LIVES");
	show_nbr_lives(cbox);
	mvprintw(MAIN_ST + NBR_CHECKS_H, STATS_X_3, "AUTO DECREASE in");
	show_nbr_checks(cbox);
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
	mvprintw(LOG_BAR, STATS_X, "LOG ");
	draw_horiz_line(MAIN_BAR, STATS_X, STATS_W, '#');
	draw_horiz_line(CHAMP_BAR, STATS_X, STATS_W, '#');
	mvprintw(CHAMP_BAR, STATS_X, "CHAMPIONS  ");
	attroff(COLOR_PAIR(color));
	draw_commands(&cbox->vbox);
	draw_main(cbox);
	move(ARENA_ST, ARENA_ST);
	color_bytes(0, MEM_SIZE, 1000, cbox);
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
	init_pair(RED_W, COLOR_RED, COLOR_WHITE);
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
	curs_set(0);
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, FALSE);
	cbox->vbox.pause = 1;
	cbox->vbox.downtime = 1000;
	cbox->vbox.downtime_on_check = 1000000;
	noecho();
	clear();
	init_start_colors();
	draw_start_screen(cbox);
}
