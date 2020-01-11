//
// Created by professor on 28.11.19.
//
#include "../assembler.h"
#include "tests.h"
#include "string.h"

#define LABEL_NUM 7
#define COMMANDS_NUM 18

int 	got_all_values(const char **p_value, const char **r_value, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		if (strcmp(p_value[i], r_value[i]))
			return (0);
	}
	return (1);
}

int get_all_commands(const int *p_commands, const int *r_commands)
{
	for (int i = 0; i < COMMANDS_NUM; ++i) {
		/*int p = p_commands[i], r = r_commands[i];
		printf("%d == %d\n", p, r);*/

		if (p_commands[i] != r_commands[i])
			return (0);
	}
	return (1);
}


int		test_get_label(char *path)
{
	char *p_labels[LABEL_NUM] = {"label", "code", "avantdebut", "init",
							"debut", "level0", "level11"};
	int fd = open(path, O_RDONLY);
	char *line = NULL;
	t_pvec *r_lables = ft_ptr_vec_init();


	while (get_next_line(fd, &line))
	{
		char *label = get_label(&line);
		if (label)
			ft_ptr_vec_pushback(r_lables, label);
		//ft_memdel((void**)&line);
	}
	close(fd);
	return got_all_values((const char**)p_labels, (const char**)(r_lables->data), LABEL_NUM);
}

int	test_get_command_name(char *path)
{
	char *p_commands_chr[COMMANDS_NUM] = {"live", "sti", "zjmp", "live",
			"sti", "zjmp", "live", "sti", "zjmp", "sti", "add", "sub",
			"zjmp", "fork", "live", "fork", "live","fork"};
	int fd = open(path, O_RDONLY);
	char *line = NULL;
	t_ivec *r_commands = ft_int_vec_init();
	t_ivec *p_commands = ft_int_vec_init();


	for (int i = 0; i < COMMANDS_NUM; ++i)
		ft_int_vec_pushback(p_commands,
				is_command(p_commands_chr[i],
						   (char*)((p_commands_chr + i) + strlen(p_commands_chr[i]))));
	while (get_next_line(fd, &line))
	{
		if (!*line)
			continue ;
		int command = get_command_name(&line);
		if (command != -1)
			ft_int_vec_pushback(r_commands, command);
		//ft_memdel((void**)&line);
	}
	close(fd);
	return get_all_commands(p_commands->data, r_commands->data);

}

int		test_get_args(char *path)
{
	/**
	 * нужно будет написать, когда будут обрабатываться метки
	 */
	return (1);
}

int	test_all(char *path1, char	*path2, char *path3)
{
	return (test_get_label(path1) &&
			test_get_command_name(path2) &&
			test_get_args(path3));
}


