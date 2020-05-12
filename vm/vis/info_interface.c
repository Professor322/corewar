/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:55:44 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/13 00:21:09 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	call_it_alive(int player, t_cbox *cbox)
{
	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	attron(COLOR_PAIR(20 + player - 1));
	mvprintw(MAIN_ST + LAST_H, STATS_X_2, "#%d", player);
//	mvprintw(LOG_ST, STATS_X, "%s called alive", cbox->champs[player - 1].name);
	attroff(COLOR_PAIR(20 + player - 1));
	refresh();
	catch_keyboard(&cbox->vbox);
}

void	show_cycle(t_cbox *cbox)
{
	int	cycle;
	int to_check;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	if (!cbox->cycle_counter)
	{
		mvprintw(MAIN_ST + ALIVES_H + 1 + cbox->vbox.undefined, STATS_X, "undefined");
		change_car_count(1000, cbox, 0);
	}
	to_check = ((int)((cbox->cycle_counter + 1) - cbox->arena.last_check) -
				cbox->arena.cycles_to_die);
	if (cbox->vbox.skip_cycles && to_check)
	{
		cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
		if (!cbox->eventloop[cycle]->len)
			return ;
	}
	mvprintw(MAIN_ST + CYCLE_H, STATS_X_2, "%ld", cbox->cycle_counter);
	count_to_check(-to_check);
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

	attron(COLOR_PAIR(10 + real));
	mvprintw(MAIN_ST + ALIVES_H + 1 + real, STATS_X_2, "%-10d", cbox->vbox.all_alive[real]);
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

void	show_deaths(unsigned char first, t_cbox *cbox)
{
	int dead;

	if (!(cbox->flags & VIS_FLAG_EXIST))
		return ;
	dead = queue_len(cbox->rip);
	if (dead || first) {
		attron(COLOR_PAIR(3));
		mvprintw(MAIN_ST + DYING_H, STATS_X, "dying processes:");
		mvprintw(MAIN_ST + DYING_H, STATS_X_3, "%5d", dead);
		attroff(COLOR_PAIR(3));
	} else{
		mvprintw(MAIN_ST + DYING_H, STATS_X, "%48s", "");
	}
	refresh();
	if (first)
		usleep(cbox->vbox.downtime_on_check);
}
