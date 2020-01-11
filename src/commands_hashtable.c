//
// Created by Virgil Legros on 11/01/2020.
//
#include "../assembler.h"

t_node	*create_command(char *name, void (*command)(t_command*, t_foo*))
{
	t_node *n_command;

	n_command = (t_node*)ft_memalloc(sizeof(t_node));
	n_command->name = name;
	n_command->command = command;
	return (n_command);
}

t_ht	*create_commands_ht(void)
{
	t_ht	*commands;

	commands = ft_ht_init();
	ht_insert_command(commands, create_command(ft_strdup("add"), add));
	ht_insert_command(commands, create_command(ft_strdup("aff"), aff));
	ht_insert_command(commands, create_command(ft_strdup("and"), and));
	ht_insert_command(commands, create_command(ft_strdup("fork"), ft_fork));
	ht_insert_command(commands, create_command(ft_strdup("ld"), ld));
	ht_insert_command(commands, create_command(ft_strdup("ldi"), ldi));
	ht_insert_command(commands, create_command(ft_strdup("lfork"), lfork));
	ht_insert_command(commands, create_command(ft_strdup("live"), live));
	ht_insert_command(commands, create_command(ft_strdup("lld"), lld));
	ht_insert_command(commands, create_command(ft_strdup("lldi"), lldi));
	ht_insert_command(commands, create_command(ft_strdup("or"), or));
	ht_insert_command(commands, create_command(ft_strdup("st"), st));
	ht_insert_command(commands, create_command(ft_strdup("sti"), sti));
	ht_insert_command(commands, create_command(ft_strdup("sub"), sub));
	ht_insert_command(commands, create_command(ft_strdup("xor"), xor));
	ht_insert_command(commands, create_command(ft_strdup("zjmp"), zjmp));
	return (commands);
}