/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: professor <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:28:37 by vlegros           #+#    #+#             */
/*   Updated: 2020/05/22 19:09:47 by professor        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

char		*output_file_name(char *argv)
{
	char	*name;
	int		is_changed;
	int		i;

	i = ft_strlen(argv) - 1;
	while (i >= 0 && argv[i] != '.')
		--i;
	is_changed = 0;
	if (i >= 0 && !ft_strncmp(argv + i, ".s", 2))
	{
		is_changed = 1;
		argv[i] = '\0';
	}
	name = ft_strjoin(argv, ".cor");
	if (is_changed)
		argv[i] = '.';
	return (name);
}

t_champ		*champ_init(char *argv)
{
	t_champ	*champ;

	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	champ->temp_labels = ft_ptr_vec_init();
	champ->labels = ft_ht_init();
	champ->command_vec = ft_ptr_vec_init();
	champ->labels_vec = ft_ptr_vec_init();
	champ->o_filename = output_file_name(argv);
	champ->fd_input = -1;
	champ->fd_output = -1;
	return (champ);
}

void		check_for_file_existence_and_backslash(char *filename,
		t_champ **champ_ptr)
{
	const int	fd = open(filename, O_RDONLY);
	char		buff[1];

	if (fd == -1)
		error_manager(NO_FILE, champ_ptr);
	while (read(fd, buff, 1))
		;
	close(fd);
	if (buff[0] != '\n')
		error_manager(NO_BACKSLASH, champ_ptr);
}

int			main(int argc, char **argv)
{
	t_champ *champ;

	if (argc == 2)
	{
		champ = champ_init(argv[1]);
		if (!champ)
			error_manager(MALLOC_ERROR, &champ);
		check_for_file_existence_and_backslash(argv[1], &champ);
		champ->fd_input = open(argv[1], O_RDONLY);
		parse(&champ);
		champ->fd_output = open(champ->o_filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write_exec_code_in_file(champ->fd_output, champ->command_vec, champ);
		ft_printf("Writing output to %s\n", champ->o_filename);
		free_memory_and_close_fd(&champ);
	}
	else
		help();
	return (0);
}
