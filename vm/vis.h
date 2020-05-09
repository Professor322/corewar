/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:27:42 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/09 18:58:44 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include <ncurses.h>
//# include "stdlib.h"
//# include "signal.h"

# define VIS_FLAG "-vis"
# define VIS_FLAG_EXIST 32

# define ARENA_IN_BYTES 64
# define CELLS_PER_BYTE 3

# define START_ARENA 1
# define WIDTH_STAT 50
# define HEIGHT_ARENA 64
# define WIDTH_ARENA 191
# define PADDING_ARENA 1

# define START_STATS (START_ARENA + 2 * PADDING_ARENA + WIDTH_ARENA + 1)
# define HEIGHT_STAT_ARENA 30
# define HEIGHT_STAT_CHAMP 8


# define PADDING_STATS 2

struct s_cbox;

void	exit_vis(void);

/*
** utils
*/

void	draw_horiz_line(int y, int x, int len, char symb);
void	draw_vert_line(int y, int x, int len, char symb);
void 	draw_one_byte(unsigned char byte, int color);
void	draw_bytes(unsigned char *arena, int len, int color, int cur_line);

void	draw_start_champion(int number, int start_cell, struct s_cbox *cbox);

#endif
