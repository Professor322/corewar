/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:38:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/13 00:10:17 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	call_it_pause(int pause)
{
	attron((pause ? COLOR_PAIR(3) : COLOR_PAIR(4)));
	mvprintw(COMM_ST + PAUSE_H, STATS_X_4, pause ? "pause" : "run  ");
	attroff((pause ? COLOR_PAIR(3) : COLOR_PAIR(4)));
	refresh();
}

void	call_downtime(int microsec, char offset)
{
	mvprintw(COMM_ST + offset, STATS_X_4, "%d", microsec / 1000);
	refresh();
}

void	call_it_skip_cycles(int skip)
{
	attron((skip ? COLOR_PAIR(4) : COLOR_PAIR(3)));
	mvprintw(COMM_ST + SKIP_H, STATS_X_4, skip ? "++" : "xx");
	attroff((skip ? COLOR_PAIR(4) : COLOR_PAIR(3)));
	refresh();
}

void	count_to_check(int check)
{
	if (!check) {
		attron(COLOR_PAIR(3));
		mvprintw(MAIN_ST + CHECK_H, STATS_X_2, "CHECK                ");
		attroff(COLOR_PAIR(3));
	}
	else
		mvprintw(MAIN_ST + CHECK_H, STATS_X_2, "CHECK in %4d cycles", check);
	refresh();
}
