/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:07 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/17 20:29:07 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		do_all_mallocs(t_cbox *cbox)
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

static void		print_help(t_cbox cbox)
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

static void		dump_arena(unsigned char *arena)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!i)
			ft_printf("0x%#.4x : ", i);
		else if (!(i % 64))
			ft_printf("\n%#.4x : ", i);
		ft_printf("%c%c ", HEX[arena[i] / 16], HEX[arena[i] % 16]);
	}
	ft_printf("\n");
}

static void		greet_winner(t_cbox *cbox)
{
	t_champ champ;

	champ = cbox->champs[cbox->arena.last_alive - 1];
	if (cbox->flags & VIS_FLAG_EXIST)
		return ;
	ft_printf("Contestant %d, \"%s\", has won !\n",
			cbox->arena.last_alive, champ.name);
}

int				main(int argc, char **argv)
{
	t_cbox	cbox;
	size_t	dump;

	ft_bzero(&cbox, sizeof(t_cbox));
	dump = parse_input(argv, argc, &cbox);
	print_help(cbox);
	do_all_mallocs(&cbox);
	init_arena(&cbox, argv);
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
