//
// Created by professor on 28.11.19.
//

#ifndef ASM_TESTS_H
#define ASM_TESTS_H

int 	get_command_name(char **line);
char	**get_args(const char *line);
void	delete_comment(char *line);
char	*get_label(char **line);
int		is_label(const char *it_begin, const char *it_end);
int 	is_command(const char *it_begin, const char *it_end);
int	test_all(char *path1, char	*path2, char *path3);

#endif //ASM_TESTS_H
