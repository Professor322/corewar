/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:07 by mbartole          #+#    #+#             */
/*   Updated: 2020/03/15 21:25:17 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_all_mallocs(t_cbox *cbox)
{
	int i;

	i = -1;
	while (++i < SIZE_OF_EVENTLOOP)
		if (!(ft_vnew(&(cbox->eventloop[i]), SIZE_OF_QUE)))
			exit(clean_all(cbox, MALLOC_ERROR));
	if (!(ft_vnew(&(cbox->cars), SIZE_OF_CARS)))
		exit(clean_all(cbox, MALLOC_ERROR));
	if (!(ft_vnew(&(cbox->dead_cars), SIZE_OF_CARS)))
		exit(clean_all(cbox, MALLOC_ERROR));
	if (!(ft_vnew(&(cbox->rip), SIZE_OF_QUE)))
		exit(clean_all(cbox, MALLOC_ERROR));
}

/*
** for all champions: copy code to arena,
** call it last alive, give it new empty car
*/

void	init_arena(t_cbox *cbox, char **argv)
{
	int				champs_count;
	int				i;
	unsigned int	cell;

	cbox->arena.cycles_to_die = CYCLE_TO_DIE;
	cbox->arena.last_check = 0;
	champs_count = count_champions(cbox->champs);
	i = -1;
	cell = 0;
	while (++i < MAX_PLAYERS)
		if (cbox->champs[i].code_size != 0)
		{
			init_champion(argv[cbox->champs[i].code_size], cbox, cell,
					&cbox->champs[i]);
			cbox->arena.last_alive = i + 1;
			make_car(cbox, -(i + 1), cell);
			cell += MEM_SIZE / champs_count;
		}
}

void	print_help(t_cbox cbox)
{
	int i;
	int	any_champion;

	any_champion = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
		any_champion += cbox.champs[i].code_size;
	if (any_champion)
		return ;
	ft_printf("Usage: ./corewar [-dump N -v N -a] "
	"[[-n N] <champion1.cor>] ...\n");
	ft_printf("-a\t\t: Prints output from \"aff\" (Default is to hide it)\n");
	ft_printf("-dump N\t: Dumps memory after N cycles then exits\n");
	ft_printf("-v N\t: Verbosity levels, "
	"can be added together to enable several\n");
	ft_printf("\t\t- 0 : Show only essentials\n");
	ft_printf("\t\t- 1 : Show lives\n");
	ft_printf("\t\t- 2 : Show cycles\n");
	ft_printf("\t\t- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("\t\t- 8 : Show deaths\n");
	exit(SUCCESS);
}

int		main(int argc, char **argv)
{
	t_cbox	cbox;
	size_t	dump;

	ft_bzero(&cbox, sizeof(t_cbox));
	dump = parse_input(argv, argc, &cbox);
	print_help(cbox);
	do_all_mallocs(&cbox);
	init_arena(&cbox, argv);
	greet_champions(cbox.champs);
	if (!dump)
	{
		dump_arena(cbox.arena.arena);
		return (clean_all(&cbox, SUCCESS));
	}
	while (do_the_fight(&cbox))
	{
		cbox.cycle_counter++;
		if (dump == cbox.cycle_counter)
		{
			dump_arena(cbox.arena.arena);
			return (clean_all(&cbox, SUCCESS));
		}
	}
	greet_winner(&cbox);
	return (clean_all(&cbox, SUCCESS));
}
