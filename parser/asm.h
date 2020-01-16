//
// Created by Virgil Legros on 16/01/2020.
//

#ifndef ASM_ASM_H
#define ASM_ASM_H

#include "libft.h"

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
#define ALC_COMMENT_CHAR		';'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define COMMANDS_NUM			16

#define TRUE					1
#define FALSE					0
typedef struct	s_champ
{
	t_pvec	*temp_labels; ///временные лейблы, у которых еще не была определена операция
	t_pvec	*file_labels; /// последовательность вызова лейблов в файле
	t_ht	*labels; /// словарь готовых лейблов

}				t_champ;

typedef	struct	s_command
{
	char	*name;
	int		name_len;
	int 	num_of_args
	///args
}				t_command;

extern	t_command g_commands[COMMANDS_NUM];

void	ft_parse(int fd);
void 	skip_spaces(char **line);
char 	*is_label(char *line);
int 	is_command(char **line);
void	parse_label(t_champ *champ, char **line, char *label_end);
char 	*parse_arg(char **line);

#endif //ASM_ASM_H
