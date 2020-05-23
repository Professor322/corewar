/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:08:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 21:22:38 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	catch_pause(t_vbox *vbox)
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
	return (1);
}

static void	catch_skip_cycles(t_vbox *vbox)
{
	vbox->skip_cycles = vbox->skip_cycles ? 0 : 1;
	call_it_skip_cycles(vbox->skip_cycles);
}

static void	catch_change_time(int *time, int change, char offset)
{
	*time += change;
	if (*time < 0)
		*time = 0;
	call_downtime(*time, offset);
}

void		catch_keyboard(t_vbox *vbox)
{
	int key;

	key = getch();
	while (key != ERR)
	{
		if (key == KEY_ENTER || key == '\n')
			return ;
		if (key == ' ' && catch_pause(vbox))
			return ;
		if (key == 's')
			catch_skip_cycles(vbox);
		else if (key == KEY_LEFT)
			catch_change_time(&vbox->downtime, -10000, DOWNTIME_H);
		else if (key == KEY_RIGHT)
			catch_change_time(&vbox->downtime, 10000, DOWNTIME_H);
		else if (key == KEY_DOWN)
			catch_change_time(&vbox->downtime_on_check, -10000, CH_DOWNTIME_H);
		else if (key == KEY_UP)
			catch_change_time(&vbox->downtime_on_check, 10000, CH_DOWNTIME_H);
		key = getch();
	}
	usleep(vbox->downtime);
}
