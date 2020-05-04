/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:40 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 20:16:57 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR
# define COREWAR

# include "libft.h"
# include "pque.h"
# include "vector.h"
# include "op.h"
# include <fcntl.h>
# include <stdio.h>

# define SIZE_OF_QUE 100
# define SIZE_OF_EVENTLOOP 1000
# define SIZE_OF_CARS 1000

# define NUMBER_OF_OPERATIONS 16
# define CW_MAX_ARGS 4
# define POS(x) ((x) % MEM_SIZE)
# define REG(x) ((x) - 1)
# define IND_OFFSET(x)  ((x) % IDX_MOD)

#define T_REG_BYTE_SIZE						1
#define T_DIR_BYTE_SIZE						4
#define T_IND_BYTE_SIZE						2

# define OP_BYTE_OFFSET 1

# define LIVE_COMMAND_CODE					1
# define LD_COMMAND_CODE					2
# define ST_COMMAND_CODE					3
# define ADD_COMMAND_CODE					4
# define SUB_COMMAND_CODE					5
# define AND_COMMAND_CODE					6
# define OR_COMMAND_CODE					7
# define XOR_COMMAND_CODE					8
# define ZJMP_COMMAND_CODE					9
# define LDI_COMMAND_CODE					10
# define STI_COMMAND_CODE					11
# define FORK_COMMAND_CODE					12
# define LLD_COMMAND_CODE					13
# define LLDI_COMMAND_CODE					14
# define LFORK_COMMAND_CODE					15
# define AFF_COMMAND_CODE					16

# define DUMP_FLAG "-dump"
# define N_FLAG "-n"
# define V_FLAG "-v"
# define A_FLAG "-a"
# define V_FLAG_DEATHS 8
# define V_FLAG_OPER 4
# define V_FLAG_CYCLES 2
# define A_FLAG_EXIST 16

# define HEADER_SIZE    (sizeof(unsigned int) * 4 + PROG_NAME_LENGTH + COMMENT_LENGTH)

struct s_car;
struct s_cbox;

typedef enum	e_arg_type
{
	NONE = 0b00,
	REG = 0b01,
	DIR = 0b10,
	IND = 0b11
}				t_arg_type;

typedef struct	s_arg		// структура одного аргумента
{
	enum e_arg_type	type;
	int 			size;	// размер в байтах
	int 			value;
}				t_arg;

typedef struct	s_champ
{
    unsigned int    magic;
	char 			name[PROG_NAME_LENGTH + 4];
    unsigned int 	code_size;
	char 			comm[COMMENT_LENGTH + 4];
}				t_champ;

typedef struct	s_arena
{
	unsigned char 	arena[MEM_SIZE];
	int		last_alive;  // real number of champion (1, 2, .. )
	size_t 	last_check;
	int 	cycles_to_die;
	size_t 	live_count;
	size_t 	checks_count; 
}				t_arena;

typedef enum	e_boolean
{
	FALSE,
	TRUE
}				t_boolean;

typedef struct	s_oper
{
	char 		name[6];
	void		(*f)(struct s_car*, struct s_cbox*);
	int 		delay;
	t_boolean 	has_type_byte;
	int 		t_dir_size;
	int         args_amount;
}				t_oper;

typedef struct	s_car
{
	size_t			id;
	unsigned char 	carry;
	t_oper	 		oper;
	unsigned int	pos;
	int 			regs[REG_NUMBER];
	ssize_t			last_live;
	int 			in_event_loop; // starts with 1, never equal 0 except dead car
}				t_car;

typedef struct	s_cbox
{
	t_arena		arena;  // just arena
	t_champ		champs[MAX_PLAYERS];  // array of champions (not-existing are NULLs)
	t_vector	*eventloop[SIZE_OF_EVENTLOOP];  // array of bin-heaps with priority
	size_t		car_counter;
	size_t 		cycle_counter;
	t_vector	*dead_cars; // vector of ponters to dead(free) cars
	t_vector	*cars; // vector of pointers to all cars
	t_vector	*rip; // vector for refresh heap in event_loop in death case
    unsigned int    flags;
}				t_cbox;

typedef struct	s_carbox
{
	t_car		*car;
	t_cbox		*cbox;
	int 		op_command_code;
}				t_carbox;

typedef enum	e_code_exit
{
	SUCCESS,
	MALLOC_ERROR,
	INPUT_ERROR,
}				t_code_exit;

typedef struct	s_valid_args
{
	t_arg_type	*args;
	int 		valid; //boolean
}				t_valid_args;

/*
** champions, champions_parse
*/
void			greet_champions(t_champ *champs);
int				count_champions(t_champ *champs);
void			greet_winner(t_cbox* cbox);
void			init_champion(char *file, t_cbox *cbox, int cell, t_champ *champ);

/*
** cars
*/
t_car			*fetch_free_car(t_cbox *cbox);
void			make_car(t_cbox *cbox, char player, unsigned int pos);
void			reschedule_car(t_cbox *cbox, t_car *car, int time_delta);
void			print_car(t_car *car); // just for debug

/*
**
*/
int				parse_input(char **argv, int argc, t_cbox *cbox);

t_oper			get_operation(char code);

unsigned char		do_the_fight(t_cbox *cbox);

int				clean_all(t_cbox *cbox, char code_exit);
void            cw_exit(t_cbox *cbox, char *msg, char *file);
void 			dump_arena(unsigned char *arena);

int				prepare_arguments(t_carbox *carbox, t_arg args[CW_MAX_ARGS], int (*validate_permitted_types)(t_arg*));

int				get_default_arg_size(t_arg_type type);
void			cw_get_arg_types(t_car *car, t_cbox *cbox, t_arg *args);
int				get_arg_values(t_car *car, t_cbox *cbox, t_arg *args);
int 			get_int_from_arg(t_car *car, t_cbox *cbox, t_arg arg);

void	 		move_car(t_car *car, t_arg *args);

int				get_int_from_bytes(unsigned char *arr, unsigned int pos, int size);
void			write_int_to_bytes(unsigned char *arr, unsigned int pos, unsigned int val);
void	write_to_reg(t_car *car, int reg, int value);
int 	read_from_reg(t_car *car, int reg);
int		get_arg_size(t_car *car, t_arg_type type);



int				valid_reg_number(int value);
int				validate_command_byte(t_carbox *carbox);
int				validate_user(t_cbox *cbox, int value);

void		exec_command(t_carbox *carbox,
						 void (*op_unique_commands)(t_car*, t_cbox*, t_arg[CW_MAX_ARGS]),
						 int (*validate_permitted_types)(t_arg*));


void        clone_regs(const int old[REG_NUMBER], int new[REG_NUMBER]);
void        clone_car(t_car *old, t_car *new);

/*
 * OPERATIONS
 */

void			ft_live(t_car *car, t_cbox *cbox);
void			ft_ld(t_car *car, t_cbox *cbox);
void			ft_st(t_car *car, t_cbox *cbox);
void			ft_add(t_car *car, t_cbox *cbox);
void			ft_sub(t_car *car, t_cbox *cbox);
void			ft_and(t_car *car, t_cbox *cbox);
void			ft_or(t_car *car, t_cbox *cbox);
void			ft_xor(t_car *car, t_cbox *cbox);
void			ft_zjmp(t_car *car, t_cbox *cbox);
void			ft_ldi(t_car *car, t_cbox *cbox);
void			ft_sti(t_car *car, t_cbox *cbox);
void			ft_fork(t_car *car, t_cbox *cbox);
void			ft_lld(t_car *car, t_cbox *cbox);
void			ft_lldi(t_car *car, t_cbox *cbox);
void			ft_lfork(t_car *car, t_cbox *cbox);
void			ft_aff(t_car *car, t_cbox *cbox);


int				logical_validate_permitted_types(t_arg *args);
int				sub_add_validate_permitted_types(t_arg *args);

int             get_fd_debug(void);
void            print_cars(t_cbox *);
void	        print_car_without_reg(t_car *car);
void            print_eventloop(t_cbox *cbox);
int             countdown(int setup);
size_t          cars_len(t_vector *cars_vec);
void            print_cur_eventloop(t_cbox *cbox);
void			print_bytes(t_cbox *cbox, t_car *car, int bytes_amount);
void    		print_full_eventloop(t_cbox *cbox);

void			car_to_vec(t_car *car, t_vector *target, t_cbox *cbox, char type);

#endif
