/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 15:21:53 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 17:12:39 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	show_cycles_to_die(t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	mvprintw(MAIN_ST + TO_DIE_H, STATS_X_4, "%d    ", cbox->arena.cycles_to_die);
	refresh();
}

void	show_nbr_lives(t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	if (!cbox->arena.live_count)
		mvprintw(MAIN_ST + NBR_LIVE_H, STATS_X_4, "%10s", " ");
	if (cbox->arena.live_count >= NBR_LIVE)
	{
		attron(COLOR_PAIR(GREEN));
		mvprintw(MAIN_ST + NBR_LIVE_H, STATS_X_4, "%2d ", cbox->arena.live_count);
		attroff(COLOR_PAIR(GREEN));
	}
	else
		mvprintw(MAIN_ST + NBR_LIVE_H, STATS_X_4, "%2d ", cbox->arena.live_count);

	printw("/ %d", NBR_LIVE);
	refresh();
}

void	show_nbr_checks(t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	mvprintw(MAIN_ST + NBR_CHECKS_H, STATS_X_4, "%2d checks",
			 MAX_CHECKS - cbox->arena.checks_count);
	refresh();
}
