//
// Created by Virgil Legros on 01/03/2020.
//

#include "../assembler.h"



void 	parse(t_champ **champ_ptr)
{
	t_champ *champ;

	champ = *champ_ptr;
	while (read_line(champ_ptr) && (!champ->name || !champ->comment))
	{
		parse_header(champ_ptr);
		ft_memdel((void**)&champ->line);
	}
	while (read_line(champ_ptr))
	{
		parse_exec(champ_ptr);
		ft_memdel((void**)&(champ->line));
	}
}