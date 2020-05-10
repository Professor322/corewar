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

# define ARENA_PADDING 1
# define ARENA_ST (1 + ARENA_PADDING)
# define ARENA_H 64
# define ARENA_W (ARENA_H * CELLS_PER_BYTE - 1)

# define STATS_PADDING 2
# define STATS_ST_X (ARENA_ST + ARENA_W + ARENA_PADDING + 1 + STATS_PADDING)
# define COMM_ST_Y (1 + STATS_PADDING)
# define COMM_H 12
# define COMM_ST_X_2 (STATS_ST_X + 20)
# define COMM_ST_X_3 (STATS_ST_X + 30)
# define STATS_ST_Y (COMM_ST_Y + COMM_H + STATS_PADDING * 2)
# define STATS_W 50
# define STATS_ST_X_2 (STATS_ST_X + 12)

# define ALL_H (ARENA_H + 2 * ARENA_PADDING + 2)
# define ALL_W (STATS_ST_X + STATS_W + STATS_PADDING + 1)

# define CHAMP_H 4
# define CHAMP_ST_Y (ALL_H - STATS_PADDING * 2 - CHAMP_H * 4)

struct s_cbox;

typedef struct	s_vbox
{
	unsigned char	pause;
	unsigned char	skip_cycles;
	unsigned char	aliases[4];
	int 			all_alive[4];
	unsigned char	undefined;
}				t_vbox;

typedef struct	s_draw_bytes
{
	unsigned char *arena;
	unsigned int start;
	int len;
	int cur_line;
}				t_draw_bytes;

/*
** external interface
*/

void	start_interface(struct s_cbox *cbox);
void	finish_interface(struct s_cbox *cbox);
void	color_bytes(unsigned int index, int len, int player, struct s_cbox *cbox);
//void	show_byte(char ch, int player, struct s_cbox *cbox);
void	draw_champion(int number, unsigned int start_cell, struct s_cbox *cbox);
void	place_car(unsigned int place, int player, struct s_cbox *cbox);
void	remove_car(unsigned int place, int player, struct s_cbox *cbox);
void	drive_car(unsigned int old_place, unsigned int new_place, int player, struct s_cbox *cbox);
void	call_it_alive(int player, struct s_cbox *cbox);
void	change_car_count(int player, struct s_cbox *cbox, int change);
void	car_change_player(int reg, int old_player, int new_player, struct s_cbox *cbox);
void	show_cycle(struct s_cbox *cbox);


void	draw_horiz_line(int y, int x, int len, char symb);
void	draw_vert_line(int y, int x, int len, char symb);
void 	draw_one_byte(unsigned char byte, int color);
void	draw_bytes(t_draw_bytes draw, int color);
int		move_to_cell(unsigned int cell);



void	call_it_pause(int pause);
void	call_it_skip_cycles(int skip);
//void	add_one_car(int player, t_vbox *vbox)

void	catch_keyboard(t_vbox *vbox);

#endif
