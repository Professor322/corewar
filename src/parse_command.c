//
// Created by Virgil Legros on 16/01/2020.
//
#include "../assembler.h"

t_node	*create_node(t_champ **champ_ptr, const char *label, const t_b_command *command)
{
	t_node *new_label;

	if (!(new_label = (t_node*)ft_memalloc(sizeof(t_node))))
		error_manager(MALLOC_ERROR, champ_ptr);
	new_label->name = (char*)label;
	new_label->command = (t_b_command*)command;
	return (new_label);
}

void	compile_command(t_champ **champ_ptr, const int cmd, char **args)
{
	const t_b_command *compiled_command =
			g_commands[cmd].func(args, *champ_ptr);
	while ((*champ_ptr)->temp_labels->length)
	{
		ht_insert_node((*champ_ptr)->labels,
				create_node(champ_ptr,
						ft_ptr_vec_popback((*champ_ptr)->temp_labels),
							compiled_command));
	}
}