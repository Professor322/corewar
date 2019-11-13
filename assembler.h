/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:19:20 by vlegros           #+#    #+#             */
/*   Updated: 2019/11/11 22:19:20 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASSEMBLER_H
#define __ASSEMBLER_H

#include "./libft/includes/libft.h"

typedef struct	s_pair
{
	char	*key;
	char 	*value;
}				t_pair;

extern t_pair *g_commands[16];

void	parse(int fd);

#endif