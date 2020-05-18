//
// Created by Virgil Legros on 29/02/2020.
//

#include "../includes/assembler.h"

void	error_message(int line_num, const char *message)
{
	ft_printf("{RED}%s\nline num: %d{GREY}\n", message, line_num);
}

void	help(void)
{
	ft_printf("Program takes 1 argument\n");
	ft_printf("{YELLOW}./asm {BLUE}[file_to_compile].s{GREY}\n");
}

void	error_manager(enum e_error_type error_type, t_champ **champ)
{
	if (error_type == NO_FILE)
		error_message((*champ)->counter, "No file to compile");
	else if (error_type == MALLOC_ERROR)
		error_message((*champ)->counter, "Malloc error");
	else if (error_type == UNKNOWN_TOKEN)
		error_message((*champ)->counter, "Unknown token to parse");
	else if (error_type == NO_CHAMP_NAME)
		error_message((*champ)->counter, "No champ's name");
	else if (error_type == NO_CHAMP_COMMENT)
		error_message((*champ)->counter, "No champ's comment");
	else if (error_type == WRONG_LENGTH_OF_NAME)
		error_message((*champ)->counter, "Wrong length of champ's name or champs' comment");
	else if (error_type == INCORRECT_SYNTAX)
		error_message((*champ)->counter, "Incorrect syntax");
	else if (error_type == NON_EXISTING_COMMAND)
		error_message((*champ)->counter, "Non existing command");
	else if (error_type == NON_EXISTING_LABEL)
		error_message((*champ)->counter, "Labels with out command");
	else if (error_type == WRONG_NUMBER_OF_ARGS)
		error_message((*champ)->counter, "Wrong number of args");
	else if (error_type == WRONG_TYPE_OF_ARGS)
        error_message((*champ)->counter, "Wrong type of command arguments");
	else if (error_type == LABELS_WITHOUT_COMMAND)
        error_message((*champ)->counter, "Wrong label");
	else if (error_type == NO_BACKSLASH)
		error_message((*champ)->counter, "No backslash at the end of the file");
	else if (error_type == UNEXPECTED_END_OF_FILE)
		error_message((*champ)->counter, "Unexpected end of file");
	finish_him(champ);
}
