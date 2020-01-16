/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:19:20 by vlegros           #+#    #+#             */
/*   Updated: 2019/11/11 22:19:20 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASSEMBLER_H
# define __ASSEMBLER_H

# include "./libft/includes/libft.h"
# include "../op.h"
# define BYTE 8
# define COMMANDS_NUM 16

enum e_arg_type
{
	T_LABEL,
	T_REG,
	T_DIR,
	T_IND
};


typedef struct s_label t_label;

typedef struct	s_arg		// структура одного аргумента
{
	enum e_arg_type	type;
	t_label 		*label;
	int			    bin;	// значение
	int 			size;	// размер в байтах
}				t_arg;

/**
 * структура для хранения конечного результата команды,
 * которую можно легко распечатать в байт код
 * в струтуре t_foo в вектооре command_vec будет лежать
 * одна структурка t_b_command
 */
typedef struct s_byte_command
{
    int     command_code;
    int     arg_type_code;
    int     command_size;
    t_arg   *arg1;
    t_arg   *arg2;
    t_arg   *arg3;
}               t_b_command;

typedef struct	s_foo		// структура, которую возвращают функции
{
	int 	command_size;	//размер команд а байтах
	t_pvec	*labels_vec;	//вектор меток, заканчивается нуллом
	t_pvec   *command_vec; // вектор структур с аргументами
}				t_foo;

typedef struct	s_command
{
	char	*bin;  ///?
	int 	position; ///?
	char 	**args;  ///сделал массив аргументов. осторожно!
}				t_command;

typedef struct s_pair
{
	void	*first;
	void	*second;
}				t_pair;

typedef struct	s_label 	// структура для сохранения одной метки
{
    char	*name;			// имя метки
    int		position;		// позиция вызова метки
    int		size;			// размер аргумента
    t_b_command *command;						// также здесь будет переменная, которая хранит в себе значение,
    // полученное после применения функции-команды
}				t_label;

typedef	struct	s_node
{
	char *name;
	void (*command)(t_command*, t_foo*);
}				t_node;


extern t_pair	*g_commands[16];

int		ht_help_insert(t_ht *hashtable, void *node, unsigned long index);
int		ht_command_enlarge(t_ht *ht);
int		ht_label_enlarge(t_ht *ht);
int		ht_insert_command(t_ht *hashtable, t_node *node);
int		ht_insert_label(t_ht *hashtable, t_label *node);
t_ht	*create_commands_ht(void);
char	*get_label(char **line);
int	 get_command_name(char **line);
t_command	*get_args(char *line);

void			parse(int fd);
void			ft_exit(char *str);
t_arg           *get_arg(char *arg, int pos, int dir_size, t_pvec *label_vec);
void            dir_arg(t_arg *arg_parse, int dir_size, char *arg);
void            reg_arg(t_arg *arg_parse, int dir_size, char *arg);
int             amount_real_bytes(unsigned int num, int size);
int             ft_is_numeric(char *str);
t_b_command     *add(t_command *command, t_foo *foo);
t_b_command     *aff(t_command *command, t_foo *foo);
t_b_command     *and(t_command *command, t_foo *foo);
t_b_command     *ft_fork(t_command *command, t_foo *foo);
t_b_command     *help_command(t_command *command, t_foo *foo);
t_b_command     *ld(t_command *command, t_foo *foo);
t_b_command     *ldi(t_command *command, t_foo *foo);
t_b_command     *lfork(t_command *command, t_foo *foo);
t_b_command     *live(t_command *command, t_foo *foo);
t_b_command     *live(t_command *command, t_foo *foo);
t_b_command     *lld(t_command *command, t_foo *foo);
t_b_command     *lldi(t_command *command, t_foo *foo);
t_b_command     *or(t_command *command, t_foo *foo);
t_b_command     *st(t_command *command, t_foo *foo);
t_b_command     *sti(t_command *command, t_foo *foo);
t_b_command     *sub(t_command *command, t_foo *foo);
t_b_command     *xor(t_command *command, t_foo *foo);
t_b_command     *zjmp(t_command *command, t_foo *foo);

#endif
