//
// Created by Virgil Legros on 01/03/2020.
//

#include "../assembler.h"


/**
 * с точки начинаются токены, если встречается неизвестный токен, то компилятор должен выдавать ошибку
 * "unknown token string number"
 *
 * @param champ
 */


void	parse_exec(t_champ **champ_ptr)
{
	t_champ *champ;

	champ = *champ_ptr;
}

void 	parse(t_champ **champ_ptr)
{

	while (read_line(champ_ptr)) {
		parse_header(champ_ptr);
	}
	//parse_exec
}