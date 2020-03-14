//
// Created by Virgil Legros on 17/01/2020.
//

#include "assembler.h"

t_champ *champ_init()
{
	t_champ	*champ;

	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	champ->temp_labels = ft_ptr_vec_init();
	champ->labels = ft_ht_init();
	champ->command_vec = ft_ptr_vec_init();
	champ->labels_vec = ft_ptr_vec_init();
	return (champ);
}

char *output_file_name(char *argv) {
	char *file_name_end = ft_strchr(argv, '.');
	char *name = ft_strnew(file_name_end - argv + COR);
	*file_name_end = '\0';
	ft_strcpy(name, argv);
	*file_name_end = '.';
	name[file_name_end - argv] = '.';
	name[file_name_end - argv + 1] = 'c';
	name[file_name_end - argv + 2] = 'o';
	name[file_name_end - argv + 3] = 'r';
	return 	name;
}


int 	main(int argc, char **argv)
{
	char *name;
	t_champ *champ;

	if (argc == 2)
	{
		if (!(champ = champ_init()) || !(name = output_file_name(argv[1])))
			error_manager(MALLOC_ERROR, &champ);
		if ((champ->fd_input = open(argv[1], O_RDONLY)) == -1)
			error_manager(NO_FILE, &champ);
		parse(&champ);
		champ->fd_output = open(name,  O_WRONLY | O_CREAT| O_TRUNC, 0644);
		write_exec_code_in_file(champ->fd_output, champ->command_vec, champ);
		close(champ->fd_input);
		close(champ->fd_output);
		ft_memdel((void**)&name);
		free_memory(&champ);
	} else
		help();
	return (0);



}