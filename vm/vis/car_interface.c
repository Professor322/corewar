/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_interface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:45:56 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/13 01:56:56 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	place_car(unsigned int place, int player, t_cbox *cbox)
{
	int 			color;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	color = 2;
	if (validate_user(cbox, player))
		color = 20 + player - 1;
	move_to_cell(place);
	chgat(2, 0, color, NULL);
	refresh();
	mvprintw(LOG_ST, STATS_X, "place car to %d | player %d, color %d        ", place, player, color);
	catch_keyboard(&cbox->vbox);
}

void	remove_car(unsigned int place, int player, t_cbox *cbox)
{
	int 			color;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	color = 1;
	if (player < -1000)
		color = 1;
	// todo stack previous colors
	move_to_cell(place);
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
