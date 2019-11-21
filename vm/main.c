/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:07 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/21 16:55:33 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_champion(char *file, s_champ *champ, int i)
{
	champ->id = i;
	// TODO read evrth from champion file, validate and set properties of champ[i]
	// TODO if smth wrong just exit() with some exit_code
	// moke up jumper.cor
	champ->code_size = 0;
	champ->name = "Jumper !";
	champ->comm = "en fait C forker !";
	champ[i].code = NULL;
}

void	greet_champions(s_champ *champs, int size)
{
	int 	i;

	ft_printf("{YELLOW}Introducing contestants...\n");
	i = -1;
	while (++i < size)
		if (champs[i].id)
			ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
					champs[i].id, champs[i].code_size,
					champs[i].name, champs[i].comm);
}

void	init_arena(s_arena *arena, s_champ *champs, int champs_count)
{
	int i;
	int	cell;

	ft_bzero(arena, sizeof(s_arena));
	if (!(arena->arena = ft_memalloc(MEM_SIZE)))
		exit(clean_all(NULL, MALLOC_ERROR));
	i = -1;
	cell = 0;
	while (++i < MAX_PLAYERS)
	{
		ft_memmove(champs[i].code, &arena->arena[cell], champs[i].code_size);
		arena->last_alive = &champs[i - 1];
		cell += MEM_SIZE / champs_count;
	}
}

int		main(int argc, char **argv)
{
	int 		i;
	int 		n;  // number of players
	s_arena		arena;
	s_champ		champs[MAX_PLAYERS];

//	validate args
//	validate files of players

	ft_printf("\n{RED}welcome back to HELLLLL\n\n");

	ft_bzero(champs, sizeof(s_champ) * MAX_PLAYERS);
	i = 0;
	n = 0;
	while (++i < argc)
		if (argv[i][0] != '-' && ++n)  // TODO parse flags
			get_champion(argv[i], &champs[i], i);

	greet_champions(champs, MAX_PLAYERS);

	init_arena(&arena, champs, n);
	dump_arena(arena.arena);

	return (clean_all(NULL, SUCCESS));
}