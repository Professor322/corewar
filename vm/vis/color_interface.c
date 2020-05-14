/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:45:56 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/15 00:12:20 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	place_car(unsigned int place, int player, t_cbox *cbox)
{
	int 			color;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
//	color = 10 * MY_BLACK + MY_WHITE;
//	if (validate_user(cbox, player))
//		color = 20 + player - 1;
	move_to_cell(place);
//	short pair;
//	int y, x;
//	getyx(stdscr, y, x);
//	int attrs;
//	attrs = getattrs(stdscr);
//	int attr_get(attr_t *attrs, short *pair, void *opts);
//	mvprintw(LOG_ST, STATS_X, "Y %d | X %d | ATTRS %d                ",
//			y, x, attrs);
	color = set_new_color(player, cbox, place, "put_car");
	chgat(2, 0, color, NULL);
//	chgat(int n, attr_t attr, short pair, const void *opts);
	refresh();
	mvprintw(LOG_ST, STATS_X, "place car to %d | player %d, color %d        ", place, player, color);
	catch_keyboard(&cbox->vbox);
}

void	remove_car(unsigned int place, int player, t_cbox *cbox)
{
	int 			color;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
//	color = 10 * MY_WHITE + MY_BLACK;
	move_to_cell(place);
	color = set_new_color(player, cbox, place, "pop_car");
	chgat(2, 0, color, NULL);
	refresh();
	mvprintw(LOG_ST, STATS_X, "remove car from %d | player %d, color %d        ", place, player, color);
	catch_keyboard(&cbox->vbox);
}

void	drive_car(unsigned int old_place, unsigned int new_place, int player, t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	remove_car(old_place, player, cbox);
	place_car(new_place, player, cbox);
}

void	color_bytes(unsigned int index, int len, int player, t_cbox *cbox)
{
	int color;
	int cur_line;
	int i;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	index = index % MEM_SIZE;
//	color = 1;
//	if (validate_user(cbox, player))
//		color = 10 + player - 1;
	color = get_text_color(player, cbox);
	cur_line = move_to_cell(index);
	draw_bytes((t_draw_bytes){cbox->arena.arena, index, len, cur_line}, color);
	i = -1;
	while (++i < len)
		cbox->vbox.colors[index + i] = color;
	mvprintw(LOG_ST, STATS_X, "color bytes | player %d, color %d            ", player, color);
//	mvprintw(LOG_ST, STATS_X, "%s write bytes to arena", cbox->champs[player - 1].name);
}

void	draw_champion(int number, unsigned int start_cell, t_cbox *cbox)
{
	short color;
	unsigned char	place;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	place = cbox->vbox.champs_count++;
	cbox->vbox.champs[number].place = place + 1;
//	cbox->vbox.champ_count++;
//	init_colors(number, &cbox->vbox);
	color_bytes(start_cell, cbox->champs[number].code_size, number + 1, cbox);
//	i = move_to_cell(start_cell);
//	draw_bytes((t_draw_bytes){cbox->arena.arena, start_cell, cbox->champs[number].code_size, i}, 10 + number);
//	i = -1;
//	while (++i < (int)cbox->champs[number].code_size)
//		cbox->vbox.colors[start_cell + i] = 10 + number;
	mvprintw(MAIN_ST + ALIVES_H + 1 + place, STATS_X, "player #%d", number + 1);
	change_car_count(number + 1, cbox, 0);
	mvprintw(CHAMP_ST + place * CHAMP_H + 1, STATS_X, "Player");
	mvprintw(CHAMP_ST + place * CHAMP_H + 2, STATS_X, "name:");
	mvprintw(CHAMP_ST + place * CHAMP_H + 3, STATS_X, "slogan:");
	color = get_text_color(number + 1, cbox);
	attron(COLOR_PAIR(color));
	mvprintw(CHAMP_ST + place * CHAMP_H + 1, STATS_X_2, "#%d", number + 1);
	mvprintw(CHAMP_ST + place * CHAMP_H + 2, STATS_X_2, "%s", cbox->champs[number].name);
	cbox->champs[number].comm[27] = 0;
	mvprintw(CHAMP_ST + place * CHAMP_H + 3, STATS_X_2, "%s", cbox->champs[number].comm);
	if (cbox->champs[number].comm[21])
		printw("...");
	attroff(COLOR_PAIR(color));
	refresh();
//	cbox->vbox.undefined++;
	catch_keyboard(&cbox->vbox);
}
