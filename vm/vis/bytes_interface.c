/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:38:45 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 22:38:36 by mbartole         ###   ########.fr       */
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
		color = COLOR_PAIR(10 + player - 1);

	cur_line = move_to_cell(index);
//	attron(COLOR_PAIR(color));
	draw_bytes((t_draw_bytes){cbox->arena.arena, index, len, cur_line}, color);
}

void	draw_champion(int number, unsigned int start_cell, t_cbox *cbox)
{
	int i;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	cbox->vbox.aliases[number] = cbox->vbox.undefined;
	i = move_to_cell(start_cell);
	draw_bytes((t_draw_bytes){cbox->arena.arena, start_cell, cbox->champs[number].code_size, i}, 10 + number);
	move(STATS_ST_Y + 5 + cbox->vbox.undefined, STATS_ST_X);
	printw("player #%d", number + 1);
	change_car_count(number + 1, cbox, 0);
	move(CHAMP_ST_Y + cbox->vbox.undefined * CHAMP_H + 1, STATS_ST_X);
	printw("Player");
	move(CHAMP_ST_Y + cbox->vbox.undefined * CHAMP_H + 2, STATS_ST_X);
	printw("name:");
	move(CHAMP_ST_Y + cbox->vbox.undefined * CHAMP_H + 3, STATS_ST_X);
	printw("slogan:");
	attron(COLOR_PAIR(10 + number));
	move(CHAMP_ST_Y + cbox->vbox.undefined * CHAMP_H + 1, STATS_ST_X_2);
	printw("#%d", number + 1);
	move(CHAMP_ST_Y + cbox->vbox.undefined * CHAMP_H + 2, STATS_ST_X_2);
	printw("%s", cbox->champs[number].name);
	move(CHAMP_ST_Y + cbox->vbox.undefined * CHAMP_H + 3, STATS_ST_X_2);
	cbox->champs[number].comm[30] = 0;
	printw("%s", cbox->champs[number].comm);
	attroff(COLOR_PAIR(10 + number));
	refresh();
	cbox->vbox.undefined++;
	catch_keyboard(&cbox->vbox);
}
