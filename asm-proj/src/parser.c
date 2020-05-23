/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 19:37:16 by vlegros           #+#    #+#             */
/*   Updated: 2020/05/22 19:38:10 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	parse(t_champ **champ_ptr)
{
	t_champ	*champ;

	champ = *champ_ptr;
	while (read_line(champ_ptr))
	{
		if (!champ->name || !champ->comment)
			parse_header(champ_ptr);
		else
			parse_exec(champ_ptr);
		ft_memdel((void**)&champ->line);
	}
	if (!champ->name || !champ->comment)
		error_manager(UNEXPECTED_END_OF_FILE, champ_ptr);
	while (champ->temp_labels->length)
		ht_insert_node(champ->labels,
				create_node(champ_ptr,
						ft_ptr_vec_popback(champ->temp_labels),
						init_b_cmd(LAST_LABELS, champ, NULL)));
}
