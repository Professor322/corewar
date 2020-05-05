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

void	init_arena(t_cbox *cbox, char **argv)
{
    int champs_count;
	int i;
	unsigned int	cell;

	cbox->arena.cycles_to_die = CYCLE_TO_DIE;
	cbox->arena.last_check = 0;
	champs_count = count_champions(cbox->champs);
	i = -1;
	cell = 0;
	while (++i < MAX_PLAYERS)
		if (cbox->champs[i].code_size != 0)
		{
			// copy code of champion to arena
			init_champion(argv[cbox->champs[i].code_size], cbox, cell, &cbox->champs[i]);
			// call it last alive
			cbox->arena.last_alive = i + 1;
			// make new car for this champion
			make_car(cbox, -(i + 1), cell);
			cell += MEM_SIZE / champs_count;
		}
}



int		main(int argc, char **argv)
{
	t_cbox		cbox;  // corewar-box: champions, arena, eventloop
	size_t 		dump;  // cycle to stop and dump arena

	ft_bzero(&cbox, sizeof(t_cbox));
	dump = parse_input(argv, argc, &cbox);

    //TODO HELP TEXT

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
			//print_full_eventloop(&cbox);
			//print_cur_eventloop(&cbox);
            return (clean_all(&cbox, SUCCESS));
        }
    }
//    print_cur_eventloop(&cbox);
    greet_winner(&cbox);
	return (clean_all(&cbox, SUCCESS));
}
