/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:08:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/13 00:17:24 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void catch_pause(t_vbox *vbox)
{
	if (vbox->pause)
	{
		nodelay(stdscr, TRUE);
		vbox->pause = 0;
	}
	else
	{
		nodelay(stdscr, FALSE);
		vbox->pause = 1;
	}
	call_it_pause(vbox->pause);
}

static void catch_skip_cycles(t_vbox *vbox)
{
	vbox->skip_cycles = vbox->skip_cycles ? 0 : 1;
	call_it_skip_cycles(vbox->skip_cycles);
	catch_keyboard(vbox);
}

static void	catch_change_time(t_vbox *vbox, int *time, int change, char offset)
{
	*time += change;
	if (*time < 0)
		*time = 0;
	call_downtime(*time, offset);
	catch_keyboard(vbox);
}

void	catch_keyboard(t_vbox *vbox)
{
	int key;

	key = getch();
	if (key == ' ')
		catch_pause(vbox);
	else if (key == 's')
		catch_skip_cycles(vbox);
	else if (key == KEY_LEFT)
		catch_change_time(vbox, &vbox->downtime, -10000, DOWNTIME_H);
	else if (key == KEY_RIGHT)
		catch_change_time(vbox, &vbox->downtime ,10000, DOWNTIME_H);
	else if (key == KEY_DOWN)
		catch_change_time(vbox, &vbox->downtime_on_check, -10000, CH_DOWNTIME_H);
	else if (key == KEY_UP)
		catch_change_time(vbox, &vbox->downtime_on_check ,10000, CH_DOWNTIME_H);
	else
		usleep(vbox->downtime);
	//todo manage other keys
//	else if (key == ERR || key == KEY_ENTER)
//		return ;
//	else
//		catch_keyboard(vbox);
}
