/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:55:44 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 22:11:37 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	call_it_alive(int player, t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	attron(COLOR_PAIR(20 + player - 1));
	move(STATS_ST_Y + 1, STATS_ST_X_2);

	printw("#%d", player);
	attroff(COLOR_PAIR(20 + player - 1));
	refresh();
	catch_keyboard(&cbox->vbox);
}

void	show_cycle(t_cbox *cbox)
{
	int	cycle;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	if (!cbox->cycle_counter)
	{
		move(STATS_ST_Y + 5 + cbox->vbox.undefined, STATS_ST_X);
		printw("undefined");
		change_car_count(1000, cbox, 0);
	}
	if (cbox->vbox.skip_cycles)
	{
		cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
		if (!cbox->eventloop[cycle]->len)
			return ;
	}
	move(STATS_ST_Y + 2, STATS_ST_X_2);
	printw("%ld", cbox->cycle_counter);
	refresh();
	catch_keyboard(&cbox->vbox);
}

void	change_car_count(int player, t_cbox *cbox, int change)
{
	int real;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	if (validate_user(cbox, player))
	{
		player -= 1;
		real = cbox->vbox.aliases[player];
	}
	else
		real = cbox->vbox.undefined;
	cbox->vbox.all_alive[real] += change;
	move(STATS_ST_Y + 5 + real, STATS_ST_X_2);
	attron(COLOR_PAIR(10 + real));
	printw("%-10d", cbox->vbox.all_alive[real]);
	attroff(COLOR_PAIR(10 + real));
	refresh();
}

void	car_change_player(int reg, int old_player, int new_player, t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	if (reg != 1)
		return ;
	change_car_count(old_player, cbox, -1);
	change_car_count(new_player, cbox, 1);
}