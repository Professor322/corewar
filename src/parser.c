//
// Created by Virgil Legros on 01/03/2020.
//

#include "../includes/assembler.h"



void 	parse(t_champ **champ_ptr)
{
	t_champ *champ;

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
}