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
	champ->command_vec = ft_ptr_vec_init();
	champ->labels_vec = ft_ptr_vec_init();
	champ->name = NULL;
	champ->comment = NULL;
	return (champ);
}

int 	main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	t_champ *champ;

	champ = champ_init();
	parse_header(champ, fd);
	printf("name: %s\ncomment: %s\n", champ->name, champ->comment);
	/*ft_parse(fd, champ);
	write_exec_code_in_file(open("test.cor", O_CREAT | O_WRONLY, 0644),
			champ->command_vec, "test.cor");*/
	return (0);
}