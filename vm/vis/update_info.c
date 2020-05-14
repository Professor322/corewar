/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:38:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/14 23:10:18 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	call_it_pause(int pause)
{
	attron((pause ? COLOR_PAIR(RED) : COLOR_PAIR(GREEN)));
	mvprintw(COMM_ST + PAUSE_H, STATS_X_4, pause ? "pause" : "run  ");
	attroff((pause ? COLOR_PAIR(RED) : COLOR_PAIR(GREEN)));
	refresh();
}

void	call_downtime(int microsec, char offset)
{
	mvprintw(COMM_ST + offset, STATS_X_4, "%-10d", microsec / 1000);
	refresh();
}

void	call_it_skip_cycles(int skip)
{
	attron((skip ? COLOR_PAIR(GREEN) : COLOR_PAIR(RED)));
	mvprintw(COMM_ST + SKIP_H, STATS_X_4, skip ? "++" : "xx");
	attroff((skip ? COLOR_PAIR(GREEN) : COLOR_PAIR(RED)));
	refresh();
}

void	count_to_check(int check)
{
	if (!check) {
		attron(COLOR_PAIR(RED));
		mvprintw(MAIN_ST + CHECK_H, STATS_X_2, "CHECK                ");
		attroff(COLOR_PAIR(RED));
	}
	else
		mvprintw(MAIN_ST + CHECK_H, STATS_X_2, "CHECK in %4d cycles", check);
	refresh();
}
