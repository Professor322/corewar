/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:07 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/23 20:48:06 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_timeline(t_cbox *cbox)
{
	int i;

	i = -1;
	while (++i < SIZE_OF_TIMELINE)
		if (!(ft_vnew(&(cbox->timeline[i]), SIZE_OF_QUE)))
			exit(clean_all(cbox, MALLOC_ERROR));
}

void	init_arena(int champs_count, t_cbox *cbox)
{
	int i;
	unsigned int	cell;

	ft_bzero(&cbox->arena, sizeof(t_arena));
	if (!(cbox->arena.arena = ft_memalloc(MEM_SIZE)))
		exit(clean_all(cbox, MALLOC_ERROR));
	cbox->arena.cycles_to_die = CYCLE_TO_DIE;
	i = -1;
	cell = 0;
	while (++i < MAX_PLAYERS)
		if (cbox->champs[i].id != 0)
		{
			ft_memmove(&(cbox->arena.arena[cell]), cbox->champs[i].code, cbox->champs[i].code_size);
			push_que(cbox->timeline[0], make_car(cbox, -i, cell), cbox->carry_counter);
			cbox->arena.last_alive = &cbox->champs[i - 1];
			cell += MEM_SIZE / champs_count;
		}
}

int		main(int argc, char **argv)
{
	size_t 		i;
	int 		n;  // number of players
	t_cbox		cbox;  // corewar-box: champions, arena, timeline

//	TODO validate args
//	TODO validate files of players
//  TODO parse flags

	ft_printf("\n{RED}welcome back to HELLLLL\n\n");

	ft_bzero(&cbox, sizeof(t_cbox));
	i = 0;
	n = 0;
	while (++i < argc)
		if (argv[i][0] != '-' && ++n)
			get_champion(argv[i], &cbox.champs[i - 1], i, &cbox);

	greet_champions(cbox.champs, MAX_PLAYERS);

	init_timeline(&cbox);

	init_arena(n, &cbox);
	dump_arena(cbox.arena.arena);

	i = 0;
	while (do_the_fight(&cbox, i))
		i++;

	return (clean_all(&cbox, SUCCESS));
}