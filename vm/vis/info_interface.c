/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:55:44 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/17 14:19:28 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	call_it_alive(int player, t_cbox *cbox)
{
	short color;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	color = get_text_color(player, NULL);
	attron(COLOR_PAIR(color));
	mvprintw(MAIN_ST + LAST_H, STATS_X_2, "#%d", player);
	attroff(COLOR_PAIR(color));
	refresh();
	write_to_log(player, cbox, "alive");
	catch_keyboard(&cbox->vbox);
}

void	show_cycle(t_cbox *cbox)
{
	int	cycle;
	int to_check;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	if (!cbox->cycle_counter)
	{
		cbox->vbox.champs[4].place = cbox->vbox.champs_count + 1;
		mvprintw(MAIN_ST + ALIVES_H + 2 + cbox->vbox.champs_count,
				STATS_X, "undefined");
		change_car_count(1000, cbox, 0);
	}
	to_check = ((int)((cbox->cycle_counter + 1) - cbox->arena.last_check) -
				cbox->arena.cycles_to_die);
	if (cbox->vbox.skip_cycles && to_check)
	{
		cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
		if (!cbox->eventloop[cycle]->len)
			return ;
	}
	mvprintw(MAIN_ST + CYCLE_H, STATS_X_4, "%ld", cbox->cycle_counter + 1);
	count_to_check(-to_check);
	refresh();
	usleep(cbox->vbox.downtime);
}

void	change_car_count(int player, t_cbox *cbox, int change)
{
	int place;
	int color;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	player = validate_user(cbox, player) ? player - 1 : 4;
	place = cbox->vbox.champs[player].place;
	cbox->vbox.champs[player].alive_cars += change;
	color = get_text_color(player + 1, NULL);
	attron(COLOR_PAIR(color));
	mvprintw(MAIN_ST + ALIVES_H + place + 1, STATS_X_2, "%-10d",
			cbox->vbox.champs[player].alive_cars);
	attroff(COLOR_PAIR(color));
	refresh();
}

void	car_change_player(int reg, int old_player, int new_player, t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	if (reg != 1)
		return ;
	change_car_count(old_player, cbox, -1);
	change_car_count(new_player, cbox, 1);
}

void	show_deaths(t_cbox *cbox)
{
	int dead;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;

//	clear_line(LOG_ST);
//	move(LOG_ST, STATS_X);
//	int i, sum, sum_vis;
//	i = -1; sum = 0;
//	while (++i < (int)cars_len(cbox->cars))
//		if (((t_car **)cbox->cars->cont)[i]) {
//			sum++;
//			printw("| %d |", )
//		}
//	i = -1; sum_vis = 0;
//	while (++i < 5)
//		sum_vis += cbox->vbox.champs[i].alive_cars;
//
//	if (sum != sum_vis)
//		attron(COLOR_PAIR(RED_W));
//	mvprintw(LOG_ST, STATS_X, "| cars on field %d | real cars %d", sum_vis, sum);
//	attroff(COLOR_PAIR(RED));

	dead = queue_len(cbox->rip);
	attron(COLOR_PAIR(RED));
	draw_horiz_line(MAIN_ST + CHECK_H, STATS_X, STATS_W, '#');
	draw_horiz_line(MAIN_ST + CHECK_H + 4, STATS_X, STATS_W, '#');
	attroff(COLOR_PAIR(RED));
	mvprintw(MAIN_ST + CHECK_H + 2, STATS_X, "dying processes: %-10d", dead);
	refresh();
	usleep(cbox->vbox.downtime_on_check);
	catch_keyboard(&cbox->vbox);
	if (! dead)
	{
		clear_line(MAIN_ST + CHECK_H);
		clear_line(MAIN_ST + CHECK_H + 2);
		clear_line(MAIN_ST + CHECK_H + 4);
		refresh();
	}
}
