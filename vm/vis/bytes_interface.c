/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:38:45 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/13 01:38:43 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	color_bytes(unsigned int index, int len, int player, t_cbox *cbox)
{
	int color;
	int cur_line;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	index = index % MEM_SIZE;
	color = 1;
	if (validate_user(cbox, player))
		color = 10 + player - 1;

	cur_line = move_to_cell(index);
	draw_bytes((t_draw_bytes){cbox->arena.arena, index, len, cur_line}, color);
	mvprintw(LOG_ST, STATS_X, "color bytes | player %d, color %d            ", player, color);
//	mvprintw(LOG_ST, STATS_X, "%s write bytes to arena", cbox->champs[player - 1].name);
}

void	draw_champion(int number, unsigned int start_cell, t_cbox *cbox)
{
	int i;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	cbox->vbox.aliases[number] = cbox->vbox.undefined;
	i = move_to_cell(start_cell);
	draw_bytes((t_draw_bytes){cbox->arena.arena, start_cell, cbox->champs[number].code_size, i}, 10 + number);
	move(MAIN_ST + ALIVES_H + 1 + cbox->vbox.undefined, STATS_X);
	printw("player #%d", number + 1);
	change_car_count(number + 1, cbox, 0);
	move(CHAMP_ST + cbox->vbox.undefined * CHAMP_H + 1, STATS_X);
	printw("Player");
	move(CHAMP_ST + cbox->vbox.undefined * CHAMP_H + 2, STATS_X);
	printw("name:");
	move(CHAMP_ST + cbox->vbox.undefined * CHAMP_H + 3, STATS_X);
	printw("slogan:");
	attron(COLOR_PAIR(10 + number));
	move(CHAMP_ST + cbox->vbox.undefined * CHAMP_H + 1, STATS_X_2);
	printw("#%d", number + 1);
	move(CHAMP_ST + cbox->vbox.undefined * CHAMP_H + 2, STATS_X_2);
	printw("%s", cbox->champs[number].name);
	move(CHAMP_ST + cbox->vbox.undefined * CHAMP_H + 3, STATS_X_2);
	cbox->champs[number].comm[27] = 0;
	printw("%s", cbox->champs[number].comm);
	if (cbox->champs[number].comm[21])
		printw("...");
	attroff(COLOR_PAIR(10 + number));
	refresh();
	cbox->vbox.undefined++;
	catch_keyboard(&cbox->vbox);
}
