/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 21:50:33 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/16 21:53:58 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include <ncurses.h>

# define VIS_FLAG "-vis"
# define VIS_FLAG_EXIST 32

# define ARENA_IN_BYTES 64
# define CELLS_PER_BYTE 3

# define MY_BLACK 6
# define MY_WHITE 5
# define RED 3
# define GREEN 4
# define RED_W 2

# define ARENA_PADDING 1
# define ARENA_ST (1 + ARENA_PADDING)
# define ARENA_H 64
# define ARENA_W (ARENA_H * CELLS_PER_BYTE - 1)

# define STATS_PADDING 2
# define STATS_X (ARENA_ST + ARENA_W + ARENA_PADDING + 1 + STATS_PADDING)
# define STATS_X_2 (STATS_X + 12)
# define STATS_X_3 (STATS_X + 25)
# define STATS_X_4 (STATS_X + 42)
# define STATS_W 50

# define COMM_ST (1 + STATS_PADDING)
# define COMM_H 8

# define MAIN_BAR (COMM_ST + COMM_H + STATS_PADDING)
# define MAIN_ST (MAIN_BAR + STATS_PADDING + 1)

# define ALL_H (ARENA_H + 2 * ARENA_PADDING + 2)
# define ALL_W (STATS_X + STATS_W + STATS_PADDING + 1)

# define CHAMP_H 4
# define CHAMP_ST (ALL_H - STATS_PADDING - CHAMP_H * 4)
# define CHAMP_BAR (CHAMP_ST - STATS_PADDING)

# define LOG_H 1
# define LOG_BAR (CHAMP_BAR - STATS_PADDING * 2 - LOG_H)
# define LOG_ST (LOG_BAR + STATS_PADDING)

# define NEXT_H 0
# define PAUSE_H 2
# define DOWNTIME_H 4
# define CH_DOWNTIME_H 6
# define SKIP_H 8

# define LAST_H 0
# define CYCLE_H 0
# define ALIVES_H 3
# define CHECK_H 12
# define TO_DIE_H 3
# define NBR_LIVE_H 7
# define NBR_CHECKS_H 5

struct s_cbox;

typedef struct	s_vchamp
{
	int				alive_cars;
	unsigned char	place;
}				t_vchamp;

typedef struct	s_vbox
{
	unsigned char	pause;
	unsigned char	skip_cycles;
	int				downtime;
	int				downtime_on_check;
	unsigned char	champs_count;
	unsigned char	colors[1024 * 4];
	t_vchamp		champs[5];
}				t_vbox;

typedef struct	s_draw_bytes
{
	unsigned int	start;
	int				len;
	int				cur_line;
	int				player;
}				t_draw_bytes;

/*
** external interface
*/

void			start_interface(struct s_cbox *cbox);
void			finish_interface(struct s_cbox *cbox);
void			color_bytes(unsigned int index, int len, int player,
				struct s_cbox *cbox);
void			draw_champion(int number, unsigned int start_cell,
				struct s_cbox *cbox);
void			place_car(unsigned int place, int player, struct s_cbox *cbox,
				char *mode);
void			drive_car(unsigned int old_place, unsigned int new_place,
				int player, struct s_cbox *cbox);
void			call_it_alive(int player, struct s_cbox *cbox);
void			change_car_count(int player, struct s_cbox *cbox, int change);
void			car_change_player(int reg, int old_player, int new_player,
				struct s_cbox *cbox);
void			show_cycle(struct s_cbox *cbox);
void			show_deaths(struct s_cbox *cbox);
void			show_nbr_checks(struct s_cbox *cbox);
void			show_nbr_lives(struct s_cbox *cbox);
void			show_cycles_to_die(struct s_cbox *cbox);

void			draw_horiz_line(int y, int x, int len, char symb);
void			draw_vert_line(int y, int x, int len, char symb);
int				move_to_cell(unsigned int cell);
void			clear_line(int offset);

short			get_text_color(int player, struct s_cbox *cbox);
int				set_new_color(int player, struct s_cbox *cbox, int index,
				char *mode);
void			write_to_log(int player, struct s_cbox *cbox, char *mode);

void			call_it_pause(int pause);
void			call_downtime(int milisec, char offset);
void			call_it_skip_cycles(int skip);
void			count_to_check(int check);

void			catch_keyboard(t_vbox *vbox);

#endif
