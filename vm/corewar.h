/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:55:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/19 18:24:49 by mbartole         ###   ########.fr       */
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

}				s_arena;

typedef enum	e_code_exit
{
	SUCCESS,
	MALLOC_ERROR
}				t_code_exit;

#endif