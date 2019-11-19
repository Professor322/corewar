/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:07 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/19 18:53:37 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int 	clean_all(s_arena *arena, char code_exit)
{
	free(arena);
	return (code_exit);
}

void	get_champion(char *file, s_champ *champ, int i)
{
	// TODO read evrth from champion file, validate and set properties of champ[i]

	champ->id = i;
	// moke up jumper.cor
	champ->code_size = 320;
	champ->name = "Jumper !";
	champ->comm = "en fait C forker !";
//	champ[i].code =
}

void	greet_champions(s_champ *champs, int size)
{
	int 	i;

	ft_printf("{YELLOW}Introducing contestants...\n");
	i = -1;
	while (++i < size)
		if (champs[i].id)
			ft_printf("* Player %i, weighing %i bytes, '%s' ('%s') !\n",
					champs[i].id, champs[i].code_size,
					champs[i].name, champs[i].comm);
}

int		main(int argc, char **argv)
{
	int 		i;
//	s_arena		*arena;
	s_champ	champs[MAX_PLAYERS];

//	validate args
//	validate files of players

	ft_printf("\n{RED}welcome back to HELLLLL\n\n");

//	if (!(arena = ft_memalloc(sizeof(arena))))
//		return(clean_all(NULL, MALLOC_ERROR))

	ft_bzero(champs, sizeof(s_champ) * MAX_PLAYERS);
	i = 0;
	while (++i < argc)
		if (argv[i][0] != '-')  // TODO parse flags
			get_champion(argv[i], &champs[i], i);
	greet_champions(champs, MAX_PLAYERS);

	return (clean_all(NULL, SUCCESS));
}