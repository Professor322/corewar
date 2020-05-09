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

/*
** get number from string
** check it can be champion number, not already in use
** check there is exist next argument (with champion file name)
** remember next argument index in champ[number]->code_size
*/

void			parse_n(char *s, int next_arg, int argc, t_cbox *cbox)
{
	int	next_nbr;

	if (next_arg >= argc)
		exit(INPUT_ERROR);
	next_nbr = ft_atoi(s);
	if (next_nbr > MAX_PLAYERS || next_nbr < 1)
		exit(INPUT_ERROR);
	if (cbox->champs[next_nbr].code_size)
		exit(INPUT_ERROR);
	cbox->champs[next_nbr].code_size = next_arg;
}

int				parse_int_flag_value(char *s)
{
	int val;

	val = ft_atoi(s);
	if (val < 0)
		exit(INPUT_ERROR);
	return (val);
}

/*
** remember next argument index in first unoccupied champ->code_size
*/

void			remember_champion(t_cbox *cbox, int ind_arg)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (!cbox->champs[i].code_size)
		{
			cbox->champs[i].code_size = ind_arg;
			return ;
		}
	exit(INPUT_ERROR);
}

int				parse_input(char **argv, int argc, t_cbox *cbox)
{
	int	i;
	int	dump;

	dump = -1;
	i = 0;
	while (++i < argc)
	{
		if (!(ft_strcmp(argv[i], DUMP_FLAG)))
			dump = parse_int_flag_value(argv[++i]);
		else if (!(ft_strcmp(argv[i], N_FLAG)) && (i += 2))
			parse_n(argv[i - 1], i, argc, cbox);
		else if (!(ft_strcmp(argv[i], V_FLAG)))
			cbox->flags += parse_int_flag_value(argv[++i]);
		else if (!(ft_strcmp(argv[i], A_FLAG)))
			cbox->flags += A_FLAG_EXIST;
		else
			remember_champion(cbox, i);
	}
	return (dump);
}