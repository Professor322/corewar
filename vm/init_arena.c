/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:31:34 by mbartole          #+#    #+#             */
/*   Updated: 2020/05/17 20:02:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		greet_champions(t_cbox *cbox)
{
	int	i;

	if (cbox->flags & VIS_FLAG_EXIST)
		return ;
	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < MAX_PLAYERS)
		if (cbox->champs[i].code_size)
			ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
					i + 1, cbox->champs[i].code_size,
					cbox->champs[i].name, cbox->champs[i].comm);
}

static int		count_champions(t_champ *champs)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (++i < MAX_PLAYERS)
		if (champs[i].code_size)
			n++;
	return (n);
}

/*
** make new empty car at the start of the game
*/

static void		make_car(t_cbox *cbox, char player, unsigned int pos)
{
	t_car	*new;

	new = fetch_free_car(cbox);
	new->id = cbox->car_counter;
	cbox->car_counter += 1;
	new->regs[0] = player;
	new->pos = pos;
	place_car(pos, -player, cbox, "put");
	change_car_count(-player, cbox, 1);
	call_it_alive(-player, cbox);
	new->last_live = -1;
	reschedule_car(cbox, new, 0);
}

/*
** for all champions: copy code to arena,
** call it last alive, give it new empty car
*/

void			init_arena(t_cbox *cbox, char **argv)
{
	int				champs_count;
	int				i;
	unsigned int	cell;

	cbox->arena.cycles_to_die = CYCLE_TO_DIE;
	cbox->arena.last_check = 0;
	start_interface(cbox);
	champs_count = count_champions(cbox->champs);
	i = -1;
	cell = 0;
	while (++i < MAX_PLAYERS)
		if (cbox->champs[i].code_size != 0)
		{
			init_champion(argv[cbox->champs[i].code_size], cbox, cell,
					&cbox->champs[i]);
			draw_champion(i, cell, cbox);
			cbox->arena.last_alive = i + 1;
			make_car(cbox, -(i + 1), cell);
			cell += MEM_SIZE / champs_count;
		}
	greet_champions(cbox);
}
