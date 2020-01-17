//
// Created by Virgil Legros on 17/01/2020.
//

#include "assembler.h"

t_champ *champ_init()
{
	t_champ	*champ;

	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	champ->temp_labels = ft_ptr_vec_init();
	champ->file_labels = ft_ptr_vec_init();
	champ->labels = ft_ht_init();
	return (champ);
}

int 	main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	t_champ *champ;

	champ = champ_init();
	ft_parse(fd, champ);
	return (0);
}