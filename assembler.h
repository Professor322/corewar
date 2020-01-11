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

# define BYTE 8
# define COMMANDS_NUM 16

enum e_arg_type
{
	T_LABEL,
	T_REG,
	T_DIR,
	T_IND
};

typedef struct	s_label 	// структура для сохранения одной метки
{
	char	*name;			// имя метки
	int		position;		// позиция вызова метки
	int		size;			// размер аргумента
}				t_label;

typedef struct	s_arg		// структура одного аргумента
{
	enum e_arg_type	type;
	t_label 		*label;
	int			    bin;	// значение
	int 			size;	// размер в байтах
}				t_arg;

typedef struct	s_foo		// структура, которую возвращают функции
{
	int 	command_size;	//размер команды а байтах
	t_pvec	*labels_vec;	//вектор меток, заканчивается нуллом
	t_pvec   *args_vec; // вектор структур с аргументами
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

extern t_pair	*g_commands[16];


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
void    add(t_command *command, t_foo *foo);
void    aff(t_command *command, t_foo *foo);
void    and(t_command *command, t_foo *foo);
void    fork(t_command *command, t_foo *foo);
void    help_command(t_command *command, t_foo *foo);
void    ld(t_command *command, t_foo *foo);
void    ldi(t_command *command, t_foo *foo);
void    lfork(t_command *command, t_foo *foo);
void    live(t_command *command, t_foo *foo);
void    live(t_command *command, t_foo *foo);
void    lld(t_command *command, t_foo *foo);
void    lldi(t_command *command, t_foo *foo);
void    or(t_command *command, t_foo *foo);
void    st(t_command *command, t_foo *foo);
void    sti(t_command *command, t_foo *foo);
void    sub(t_command *command, t_foo *foo);
void    xor(t_command *command, t_foo *foo);
void    zjmp(t_command *command, t_foo *foo);

#endif
