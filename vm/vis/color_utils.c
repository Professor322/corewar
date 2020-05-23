/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:38:45 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/17 19:27:03 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short	get_text_color(int player, t_cbox *cbox)
{
	if (cbox && !validate_user(cbox, player))
		player = 5;
	return ((short)(player * 10 + MY_BLACK));
}

int		set_new_color(int player, t_cbox *cbox, int index, char *mode)
{
	int				text_color;
	int				back_color;
	unsigned char	color;

	player = validate_user(cbox, player) ? player : 5;
	color = cbox->vbox.colors[index];
	text_color = color ? color / 10 : MY_WHITE;
	back_color = color ? color % 10 : MY_BLACK;
	if (!ft_strcmp(mode, "put"))
		color = text_color * 10 + player;
	else if (!ft_strcmp(mode, "pop"))
		color = text_color * 10 + MY_BLACK;
	else if (!ft_strcmp(mode, "bytes"))
		color = player * 10 + back_color;
	cbox->vbox.colors[index] = color;
	if (color / 10 == color % 10)
		color = MY_BLACK * 10 + color % 10;
	return (color);
}
