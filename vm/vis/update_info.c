/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:38:14 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/10 20:03:31 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	call_it_pause(int pause)
{
	move(COMM_ST_Y + 1, COMM_ST_X_3);
	attron((pause ? COLOR_PAIR(3) : COLOR_PAIR(4)));
	printw(pause ? "pause" : "run  ");
	attroff((pause ? COLOR_PAIR(3) : COLOR_PAIR(4)));
}

void	call_it_skip_cycles(int skip)
{
	move(COMM_ST_Y + 2, COMM_ST_X_3);;
	attron((skip ? COLOR_PAIR(4) : COLOR_PAIR(3)));
	printw(skip ? "++" : "xx");
	attroff((skip ? COLOR_PAIR(4) : COLOR_PAIR(3)));
}

