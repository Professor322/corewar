/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/28 18:40:12 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR
# define COREWAR

# include "libft.h"
# include "pque.h"
# include "vector.h"
# include "op.h"

# define SIZE_OF_QUE 100
# define SIZE_OF_TIMELINE 1000

# define NUMBER_OF_OPERATIONS 16

struct s_car;

typedef struct	s_champ
{
	unsigned char	id;
	char 	*name;
	char 	*comm;
	unsigned int 	code_size;
	char 	*code;
}				t_champ;

typedef struct	s_arena
{
	unsigned char 	*arena;
	t_champ	*last_alive;
	size_t 	cycle;
	size_t 	cycles_to_die;
	size_t 	live_count;
	size_t 	checks_count;
}				t_arena;

typedef struct	s_oper
{
	char 	name[5];
	void	(*f)(struct s_car*);
	int 	delay;
}				t_oper;

typedef struct	s_car
{
	size_t			id;
	unsigned char 	carry;
	struct s_oper 	oper;
	unsigned int	pos;
	char 			regs[REG_NUMBER];
}				t_car;

typedef struct	s_cbox
{
	t_arena		arena;  // just arena
	t_champ		champs[MAX_PLAYERS];  // array of champions (not-existing are NULLs)
	t_vector	*timeline[SIZE_OF_TIMELINE];  // array of bin-heaps with priority
	size_t		carry_counter;
	size_t 		cycle_counter;
}				t_cbox;

typedef enum	e_code_exit
{
	SUCCESS,
	MALLOC_ERROR
}				t_code_exit;

void			get_champion(char *file, t_champ *champ, int i, t_cbox *cbox);
void			greet_champions(t_champ *champs, int size);

t_car			*make_car(t_cbox *cbox, char player, unsigned int pos);
void			print_car(t_car *car); // just for debug

t_oper			get_operation(char code);

int				do_the_fight(t_cbox *cbox);

int				clean_all(t_cbox *cbox, char code_exit);
void 			dump_arena(unsigned char *arena);

#endif