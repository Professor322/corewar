//
// Created by Virgil Legros on 17/01/2020.
//

#include "../includes/assembler.h"

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
	int i;

	i = ft_strlen(argv) - 1;
	while (i >= 0 && argv[i] != '.')
		--i;
	if (i >= 0 && !ft_strncmp(argv + i, ".s", 2))
		argv[i] = '\0';
	return ft_strjoin(argv, ".cor");
}


int 	main(int argc, char **argv)
{
	char *name;
	t_champ *champ;
	if (argc == 2)
	{
		champ = champ_init();
		name = output_file_name(argv[1]);
		if (!champ || !name)
			error_manager(MALLOC_ERROR, &champ);
		if ((champ->fd_input = open(argv[1], O_RDONLY)) == -1)
			error_manager(NO_FILE, &champ);
		parse(&champ);
		champ->fd_output = open(name,  O_WRONLY | O_CREAT| O_TRUNC, 0644);
		write_exec_code_in_file(champ->fd_output, champ->command_vec, champ);
		ft_printf("Writing output to %s\n", name);
		ft_memdel((void**)&name);
		free_memory_and_close_fd(&champ);
	} else
		help();
	return (0);
}