/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:36:45 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 19:35:49 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void parse_n(char *s, int next_arg, int argc, t_cbox *cbox)
{
	int next_nbr;

	if (next_arg >= argc) // no champion file in next argument
		exit(INPUT_ERROR);
	next_nbr = ft_atoi(s);
	if (next_nbr > MAX_PLAYERS || next_nbr < 1) // invalid index of champion
		exit(INPUT_ERROR);
	if (cbox->champs[next_nbr].code_size) // index already in use
		exit(INPUT_ERROR);
	cbox->champs[next_nbr].code_size = next_arg; // in code_size we put index of argc where to get champion file
}

int parse_dump(char *s)
{
	int dump;

	dump = ft_atoi(s);
	if (dump < 0)
		exit(INPUT_ERROR);
	return dump;
}

unsigned char is_champ_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (len > 4 && file_name[len - 4] == '.' && file_name[len - 3] == 'c' &&
		file_name[len - 2] == 'o' && file_name[len - 1] == 'r')
		return 1;
	return 0;
}

void remember_champion(t_cbox *cbox, int ind_arg)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (!cbox->champs[i].code_size)
		{
			cbox->champs[i].code_size = ind_arg;
			return;
		}
	exit(INPUT_ERROR);
}

int	parse_input(char **argv, int argc, t_cbox *cbox)
{
	int i;
	int dump;

	dump = 0;
	i = 0;
    cbox->flags = 0;
    cbox->a_flag = FALSE;
	while (++i < argc)
	{
		if (!(ft_strcmp(argv[i], DUMP_FLAG)))
			dump = parse_dump(argv[++i]);
		else if (!(ft_strcmp(argv[i], N_FLAG)) && (i += 2))
			parse_n(argv[i - 1], i, argc, cbox);
        else if (!(ft_strcmp(argv[i], V_FLAG)))
            cbox->flags = parse_dump(argv[++i]); // TODO parse_flag_v
        else if (!(ft_strcmp(argv[i], A_FLAG)))
            cbox->a_flag = TRUE;
		else if (is_champ_file(argv[i]))
			remember_champion(cbox, i);
		else
			exit(INPUT_ERROR);
	}
	return dump;
}