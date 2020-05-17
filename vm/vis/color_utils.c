/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:38:45 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 21:02:59 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short get_text_color(int player, t_cbox *cbox)
{
	if (cbox)
		return ((short)((validate_user(cbox, player) ? player : 5) * 10 + MY_BLACK));
	return ((short)(player * 10 + MY_BLACK));
}

int		set_new_color(int player, t_cbox *cbox, int index, char *mode)
{
	int				text_color;
	int				back_color;
	unsigned char	color;

	player = validate_user(cbox, player) ? player : 5;
	color = cbox->vbox.colors[index];
	text_color = color ? color / 10 : MY_WHITE;
	back_color = color ? color % 10 : MY_BLACK;
	if (!ft_strcmp(mode, "put"))
		color = text_color * 10 + player;
	else if (!ft_strcmp(mode, "pop"))
		color = text_color * 10 + MY_BLACK;
	else if (!ft_strcmp(mode, "bytes"))
		color = player * 10 + back_color;
	cbox->vbox.colors[index] = color;
	int x, y;
	getyx(stdscr, y, x);
	mvprintw(LOG_ST, STATS_X, "%*s", STATS_W + 22, "");
	refresh();
	mvprintw(LOG_ST, STATS_X, "cycle %d | %s | place %d |player %d | mem color "
						   "%d | ",
						   cbox->cycle_counter, mode, index, player, color);
	refresh();
	if (color / 10 == color % 10)
		color = MY_BLACK * 10 + color % 10;
	printw("use color %d", color);
	move(y, x);
	return (color);
}
