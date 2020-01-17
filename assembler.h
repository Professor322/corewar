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

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define ALT_COMMENT_CHAR		';'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define COMMANDS_NUM			16
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

#define TRUE					1
#define FALSE					0
typedef struct	s_champ
{
	t_pvec	*temp_labels; ///временные лейблы, у которых еще не была определена операция
	t_pvec	*file_labels; /// последовательность вызова лейблов в файле
	t_ht	*labels; /// словарь готовых лейблов
    int 	command_size;	//размер команд а байтах
    t_pvec	*labels_vec;	//вектор меток, заканчивается нуллом
    t_pvec   *command_vec; // вектор структур с командами

}				t_champ;


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
    unsigned int     arg_type_code;
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


typedef	struct	s_command
{
	char	*name;
	int		name_len;
	int 	num_of_args;
	t_b_command* (*func)(char**, t_champ*);
	///args
}				t_command;

typedef struct	s_label 	// структура для сохранения одной метки
{
    char	*name;			// имя метки
    int		position;		// позиция вызова метки
    int		size;			// размер аргумента
    t_b_command *command;						// также здесь будет переменная, которая хранит в себе значение,
    // полученное после применения функции-команды
}				t_label;

typedef struct	s_node       ///элемент хэштаблицы
{
	char	*name;
	t_b_command *command;
}				t_node;

extern	t_command g_commands[COMMANDS_NUM];

///hashtable
int		ht_insert_node(t_ht *hashtable, t_node *node);
int				ht_enlarge(t_ht *ht);
t_node		*ht_find_node(t_ht *ht, char *name);
///parse
void	ft_parse(int fd, t_champ *champ);
void 	skip_spaces(char **line);
char 	*is_label(char *line);
int 	is_command(char **line);
void	parse_label(t_champ *champ, char **line, char *label_end);
char	**parse_command(char *line, const int cmd);
char 	*parse_arg(char **line);
void	compile_command(const int cmd, char **args, t_champ *champ);

void        write_exec_code_in_file(int fd, t_pvec *command_vec, char *filename);
void			parse(int fd);
void			ft_exit(char *str);
t_arg           *get_arg(char *arg, int dir_size, t_pvec *label_vec);
void            dir_arg(t_arg *arg_parse, int dir_size, char *arg);
void            reg_arg(t_arg *arg_parse, int dir_size, char *arg);
unsigned int    amount_real_bytes(unsigned int num, unsigned int size);
int             ft_is_numeric(char *str);

t_b_command     *add(char **command, t_champ *champ);
t_b_command     *aff(char **command, t_champ *champ);
t_b_command     *and(char **command, t_champ *champ);
t_b_command     *ft_fork(char **command, t_champ *champ);
t_b_command     *help_command(char **command, t_champ *champ);
t_b_command     *ld(char **command, t_champ *champ);
t_b_command     *ldi(char **command, t_champ *champ);
t_b_command     *lfork(char **command, t_champ *champ);
t_b_command     *live(char **command, t_champ *champ);
t_b_command     *live(char **command, t_champ *champ);
t_b_command     *lld(char **command, t_champ *champ);
t_b_command     *lldi(char **command, t_champ *champ);
t_b_command     *or(char **command, t_champ *champ);
t_b_command     *st(char **command, t_champ *champ);
t_b_command     *sti(char **command, t_champ *champ);
t_b_command     *sub(char **command, t_champ *champ);
t_b_command     *xor(char **command, t_champ *champ);
t_b_command     *zjmp(char **command, t_champ *champ);

#endif
