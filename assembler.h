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
	int		size;			// размер аргумента ИЗЛИШНЕ
}				t_label;

typedef struct	s_arg		// структура одного аргумента
{
	enum e_arg_type	type;
	t_label 		*label;
	char			*bin;	// значение
	int 			size;	// размер в байтах
}				t_arg;

typedef struct	s_foo		// структура, которую возвращают функции
{
	int 	command_size;	//размер команды а байтах
	t_label	*labels;		// массив меток, заканчивается нуллом
}				t_foo;

typedef struct	s_command
{
	char	*bin;
	int 	position;
	char 	*arg1;
	char 	*arg2;
	char 	*arg3;
}				t_command;

typedef struct	s_pair
{
	char	*key;
	t_foo	*(*to_binary)(t_command command); // возвращает размер команды в байтах
}				t_pair;

extern t_pair	*g_commands[16];

void			parse(int fd);
void			ft_exit(char *str);



#endif
