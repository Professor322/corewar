/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:08:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 16:48:00 by mbartole         ###   ########.fr       */
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

void	catch_keyboard(t_vbox *vbox)
{
	int key;

	key = getch();
	if (key == ' ')
		catch_pause(vbox);
	else if (key == 's')
		catch_skip_cycles(vbox);
	//todo manage other keys
//	else if (key == ERR || key == KEY_ENTER)
//		return ;
//	else
//		catch_keyboard(vbox);
}
