/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:45:56 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 20:15:33 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	place_car(unsigned int place, int player, t_cbox *cbox, char *mode)
{
	int 			color;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	color = set_new_color(player, cbox, place, mode);
	move_to_cell(place);
	chgat(2, 0, color, NULL);
	refresh();
	catch_keyboard(&cbox->vbox);
}

void	drive_car(unsigned int old_place, unsigned int new_place, int player, t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	place_car(old_place, player, cbox, "pop");
	place_car(new_place, player, cbox, "put");
}


static void		draw_one_byte(unsigned char byte, int color)
{
	attron(COLOR_PAIR(color));
	addch(HEX[byte / 16]);
	addch(HEX[byte % 16]);
	attroff(COLOR_PAIR(color));
	refresh();
}

static void	draw_bytes(t_draw_bytes draw, t_cbox *cbox)
{
	unsigned int	i;
	int 			first;
	unsigned int	finish;
	short 			color;


	i = draw.start;
	first = 1;
	finish = draw.start + draw.len;
	while (i < finish)
	{
		if (i >= MEM_SIZE)
		{
			i = i % MEM_SIZE;
			finish = finish % MEM_SIZE;
			draw.cur_line = ARENA_ST;
		}
		if (!first && !(i % ARENA_IN_BYTES))
			move(++draw.cur_line, ARENA_ST);
		color = set_new_color(draw.player, cbox, i, "bytes");
		draw_one_byte(cbox->arena.arena[i], color);
		addch(' ');
		i++;
		first = 0;
	}
}

void	color_bytes(unsigned int index, int len, int player, t_cbox *cbox)
{
	int cur_line;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	cur_line = move_to_cell(index);
	draw_bytes((t_draw_bytes){index, len, cur_line, player}, cbox);
	catch_keyboard(&cbox->vbox);
}

void	draw_champion(int number, unsigned int start_cell, t_cbox *cbox)
{
	short color;
	unsigned char	place;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	place = cbox->vbox.champs_count++;
	cbox->vbox.champs[number].place = place + 1;
	color_bytes(start_cell, cbox->champs[number].code_size, number + 1, cbox);
	mvprintw(MAIN_ST + ALIVES_H + 2 + place, STATS_X, "player #%d", number + 1);
	change_car_count(number + 1, cbox, 0);
	mvprintw(CHAMP_ST + place * CHAMP_H + 1, STATS_X, "Player");
	mvprintw(CHAMP_ST + place * CHAMP_H + 2, STATS_X, "name:");
	mvprintw(CHAMP_ST + place * CHAMP_H + 3, STATS_X, "slogan:");
	color = get_text_color(number + 1, cbox);
	attron(COLOR_PAIR(color));
	mvprintw(CHAMP_ST + place * CHAMP_H + 1, STATS_X_2, "#%d", number + 1);
	cbox->champs[number].name[27] = 0;
	mvprintw(CHAMP_ST + place * CHAMP_H + 2, STATS_X_2, "%s", cbox->champs[number].name);
	if (cbox->champs[number].name[21])
		printw("...");
	cbox->champs[number].comm[27] = 0;
	mvprintw(CHAMP_ST + place * CHAMP_H + 3, STATS_X_2, "%s", cbox->champs[number].comm);
	if (cbox->champs[number].comm[21])
		printw("...");
	attroff(COLOR_PAIR(color));
	refresh();
}
