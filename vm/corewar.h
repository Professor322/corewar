/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/21 16:02:27 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR
# define COREWAR

# include "libft.h"
# include "op.h"

typedef struct	t_champ
{
	char	id;
	char 	*name;
	char 	*comm;
	int 	code_size;
	char 	*code;
}				s_champ;

typedef struct	t_arena
{
	char 	*arena;
	s_champ	*last_alive;
	size_t 	cycle;
	size_t 	live_count;
	size_t 	checks_count;
}				s_arena;

typedef enum	e_code_exit
{
	SUCCESS,
	MALLOC_ERROR
}				t_code_exit;

int				clean_all(s_arena *arena, char code_exit);
void 			dump_arena(char *arena);

#endif