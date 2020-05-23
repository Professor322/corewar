/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: professor <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:28:37 by vlegros           #+#    #+#             */
/*   Updated: 2020/05/22 19:22:05 by professor        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

t_node	*create_node(t_champ **champ_ptr, const char *label,
		const t_b_command *command)
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
	const t_b_command *comp_cmd = g_commands[cmd].func(args, *champ_ptr);

	while ((*champ_ptr)->temp_labels->length)
	{
		ht_insert_node((*champ_ptr)->labels,
				create_node(champ_ptr,
						ft_ptr_vec_popback((*champ_ptr)->temp_labels),
							comp_cmd));
	}
}
