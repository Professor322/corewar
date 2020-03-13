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

char *output_file_name(char *argv) {
	char *file_name_end = ft_strchr(argv, '.');
	char *name = ft_strnew(file_name_end - argv + COR);
	*file_name_end = '\0';
	ft_strcpy(name, argv);
	name[file_name_end - argv] = '.';
	name[file_name_end - argv + 1] = 'c';
	name[file_name_end - argv + 2] = 'o';
	name[file_name_end - argv + 3] = 'r';
	return 	name;
}


int 	main(int argc, char **argv)
{
	int fd_input;
	int fd_output;
	char *name;
	t_champ *champ;

/*	champ = champ_init();
	champ->fd = open(argv[1], O_RDONLY);
	parse(&champ);
	printf("%s %s", champ->name, champ->comment);*/
	//free_memory(&champ);
	if (argc == 2)
	{
		if ((fd_input = open(argv[1], O_RDONLY)) == -1)
			error_manager(NO_FILE, &champ);
		if (!(champ = champ_init()) || !(name = output_file_name(argv[1])))
			error_manager(MALLOC_ERROR, &champ);
		ft_parse(fd_input, &champ);
		fd_output = open(name,  O_WRONLY | O_CREAT| O_TRUNC, 0644);
		write_exec_code_in_file(fd_output, champ->command_vec, name, champ);
		ft_memdel((void**)&name);
		free_memory(&champ);
		close(fd_input);
		close(fd_output);
	} else
		help();
	return (0);



}