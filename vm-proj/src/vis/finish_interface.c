/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:43:53 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 20:56:11 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm-proj/includes/corewar.h"

static void	meet_winner(t_cbox *cbox)
{
	int winner;
	int	color;

	winner = cbox->arena.last_alive;
	color = get_text_color(winner, NULL);
	attron(COLOR_PAIR(color));
	draw_horiz_line(MAIN_ST + CHECK_H, STATS_X, STATS_W, '#');
	draw_horiz_line(MAIN_ST + CHECK_H + 6, STATS_X, STATS_W, '#');
	mvprintw(MAIN_ST + CHECK_H + 2, STATS_X_2, "!!! GAME OVER !!!");
	mvprintw(MAIN_ST + CHECK_H + 4, STATS_X_2, "#%d %s wins",
			winner, cbox->champs[winner - 1].name);
	attroff(COLOR_PAIR(color));
	refresh();
}

void		finish_interface(t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	nodelay(stdscr, FALSE);
	if (cbox->cycle_counter)
	{
		call_it_pause(1);
		meet_winner(cbox);
		catch_keyboard(&cbox->vbox);
	}
	curs_set(1);
	clear();
	refresh();
	endwin();
}
