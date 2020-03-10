/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:40 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/10 22:45:44 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR
# define COREWAR

# include "libft.h"
# include "pque.h"
# include "vector.h"
# include "op.h"
# include <fcntl.h>

# define SIZE_OF_QUE 100
# define SIZE_OF_TIMELINE 1000

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
	unsigned char	id;
	char 			*name;
	char 			*comm;
	unsigned int 	code_size;
	unsigned char 			*code;
}				t_champ;

typedef struct	s_arena
{
	unsigned char 	*arena;
	t_champ	*last_alive;
	size_t 	cycle;
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
}				t_oper;

typedef struct	s_car
{
	size_t			id;
	unsigned char 	carry;
	t_oper	 		oper;
	unsigned int	pos;
	t_boolean 		is_alive;
	int 			regs[REG_NUMBER];
	size_t			last_live;
	int				next_time;
}				t_car;

typedef struct	s_cbox
{
	t_arena		arena;  // just arena
	t_champ		champs[MAX_PLAYERS];  // array of champions (not-existing are NULLs)
	int			champs_amount;
	t_vector	*timeline[SIZE_OF_TIMELINE];  // array of bin-heaps with priority
//	size_t		car_counter;
	size_t 		cycle_counter;
//	t_vector	free_cars; // ???
	t_vector	cars; // vector of pointers to all cars
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


void	init_timeline(t_cbox *cbox);
void	init_arena(int champs_count, t_cbox *cbox);


/*
** champions, champions_parse
*/
void			get_champion(char *file, t_champ *champ, int i, t_cbox *cbox);
void			greet_champions(t_champ *champs, int size);
void			greet_winner(t_arena* arena);
void			init_champion(int fd, t_cbox *cbox, int i);

t_car			*make_car(t_cbox *cbox, char player, unsigned int pos, int next_time);
void			print_car(t_car *car); // just for debug

t_oper			get_operation(char code);

unsigned char		do_the_fight(t_cbox *cbox);

int				clean_all(t_cbox *cbox, char code_exit);
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


#endif
