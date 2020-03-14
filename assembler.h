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
#define REGISTER_CHAR			'r'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define TOKEN_STARTER			'.'
#define NEW_LINE				'\n'
#define NAME_CMD_STRING			".name"
#define NAME_CMD_LEN			5
#define COMMENT_CMD_STRING		".comment"
#define COMMENT_CMD_LEN			8
# define QUOTE					'"'

#define COMMANDS_NUM			16
#define PROG_NAME_LENGTH		(128)
#define COMMENT_LENGTH			(2048)
#define COREWAR_EXEC_MAGIC		0xea83f3

#define END_LINE				'\0'
#define COR						4

#define ADD_COMMAND_CODE 0x04
#define AFF_COMMAND_CODE 0x10
#define AND_COMMAND_CODE 0x06
#define FORK_COMMAND_CODE 0x0c
#define LD_COMMAND_CODE 0x02
#define LDI_COMMAND_CODE 0x0a
#define LFORK_COMMAND_CODE 0x0f
#define LIVE_COMMAND_CODE 0x01
#define LLD_COMMAND_CODE 0x0d
#define LLDI_COMMAND_CODE 0x0e
#define OR_COMMAND_CODE 0x07
#define ST_COMMAND_CODE 0x03
#define STI_COMMAND_CODE 0x0b
#define SUB_COMMAND_CODE 0x05
#define XOR_COMMAND_CODE 0x08
#define ZJMP_COMMAND_CODE 0x09

#define LIVE_T_DIR_SIZE 4
#define  ADD_T_DIR_SIZE 1
#define AFF_T_DIR_SIZE 1
#define AND_T_DIR_SIZE 4
#define FORK_T_DIR_SIZE 2
#define LD_T_DIR_SIZE 4
#define LDI_T_DIR_SIZE 2
#define LFORK_T_DIR_SIZE 2
#define LLD_T_DIR_SIZE 4
#define LLDI_T_DIR_SIZE 2
#define OR_T_DIR_SIZE 4
#define ST_T_DIR_SIZE 4
#define STI_T_DIR_SIZE 2
#define SUB_T_DIR_SIZE 4
#define XOR_T_DIR_SIZE 4
#define ZJMP_T_DIR_SIZE 2


enum e_arg_type
{
	T_LABEL,
	T_REG,
	T_DIR,
	T_IND
};

enum e_error_type
{
	UNKNOWN_TOKEN = 4,
	NO_CHAMP_NAME,
	NO_CHAMP_COMMENT,
	WRONG_LENGTH_OF_NAME,
	WRONG_LENGTH_OF_COMMENT,
	INCORRECT_SYNTAX,
	NON_EXISTING_COMMAND,
	NON_EXISTING_LABEL,
	WRONG_NUMBER_OF_ARGS,
	WRONG_TYPE_OF_ARGS,
	LABELS_WITHOUT_COMMAND,
	NO_BACKSLASH,
	NO_FILE,
	MALLOC_ERROR,
	UNEXPECTED_END_OF_FILE
};

enum e_header_token
{
	NAME,
	COMMENT
};

typedef struct	s_champ
{
	t_pvec	*temp_labels;
	t_ht	*labels;
    int		command_size;
    t_pvec	*labels_vec;
    t_pvec	*command_vec;
	char	*name;
	char	*comment;
	char	*line;
	int 	fd_input;
	int 	fd_output;
	size_t	counter;
}				t_champ;

typedef struct s_label t_label;

typedef struct	s_arg
{
	enum e_arg_type	type;
	t_label			*label;
	unsigned int	bin;
	int				size;
	char			is_label;
}				t_arg;

typedef struct s_byte_command
{
    int				command_code;
    unsigned int	arg_type_code;
    int				cumulative_size;
	t_arg			args[4];
}               t_b_command;


typedef	struct	s_command
{
	char 			*name;
	int				name_len;
	int				num_of_args;
	t_b_command*	(*func)(char**, t_champ*);
}				t_command;

typedef struct	s_label
{
    char 	*name;
    int		cumulate_size;
}				t_label;

typedef struct	s_node
{
	char		*name;
	t_b_command	*command;
}				t_node;

typedef	struct	s_header
{
	char	*token;
	size_t	token_len;
	size_t	len;
}				t_header;

extern	t_command g_commands[COMMANDS_NUM];
extern 	t_header	g_header[2];

///hashtable
int		ht_insert_node(t_ht *hashtable, t_node *node);
int				ht_enlarge(t_ht *ht);
t_node		*ht_find_node(t_ht *ht, char *name);
///new parse
int 	read_line(t_champ **champ_ptr);
void 	parse_header(t_champ **champ_ptr);
void 	parse(t_champ **champ_ptr);
void 	parse_exec(t_champ **champ_ptr);
///parse
void	ft_parse(int fd, t_champ **champ);
void 	skip_spaces(char **line);
char 	*is_label(char *line);
int 	is_command(char **line);
void	parse_label(t_champ *champ, char **line, char *label_end);
char	**parse_command(char *line, const int cmd, t_champ **champ);
char 	*parse_arg(char **line);
void	compile_command(const int cmd, char **args, t_champ *champ);
void 	get_header(int fd, t_champ *champ);
///writing
void      		write_exec_code_in_file(int fd, t_pvec *command_vec, t_champ *champ);
void			ft_exit(char *str);
t_arg		    *get_arg(char *arg, int dir_size, t_champ *champ, t_arg *arg_parse);
void            *dir_arg(t_arg *arg_parse, int size, char *arg, t_champ *champ);
void            reg_arg(t_arg *arg_parse, char *arg);
void           	*label_init(t_arg *arg, int size, char *l_name, t_champ *champ);
void            indir_arg(t_arg *arg_parse, char *arg);
int             ft_is_numeric(char *str);
int             reverse_int(int s);
short           reverse_short(short s);
t_b_command 	*init_b_cmd(int cmd_code, t_champ *champ, char **cmd);
t_b_command     *compile(int cmd_code, t_champ *champ, int d_size, char **cmd);
///commands
t_b_command     *add(char **command, t_champ *champ);
t_b_command     *aff(char **command, t_champ *champ);
t_b_command     *and(char **command, t_champ *champ);
t_b_command     *ft_fork(char **command, t_champ *champ);
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

///error management
void	error_manager(enum e_error_type error_type, t_champ **champ);
void	help(void);
///memory freeing
void	finish_him(t_champ **champ);
void 	free_memory(t_champ **champ);

#endif