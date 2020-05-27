/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:02:33 by vlegros           #+#    #+#             */
/*   Updated: 2020/05/22 23:11:04 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

t_command	g_commands[COMMANDS_NUM] =
{
	{"live", 4, 1, live},
	{"lldi", 4, 3, lldi},
	{"lld", 3, 2, lld},
	{"ldi", 3, 3, ldi},
	{"ld", 2, 2, ld},
	{"sti", 3, 3, sti},
	{"st", 2, 2, st},
	{"add", 3, 3, add},
	{"sub", 3, 3, sub},
	{"and", 3, 3, ft_and},
	{"or", 2, 3, ft_or},
	{"xor", 3, 3, ft_xor},
	{"zjmp", 4, 1, zjmp},
	{"fork", 4, 1, ft_fork},
	{"lfork", 5, 1, lfork},
	{"aff", 3, 1, aff}
};

t_header	g_header[2] =
{
	{NAME_CMD_STRING, NAME_CMD_LEN, PROG_NAME_LENGTH},
	{COMMENT_CMD_STRING, COMMENT_CMD_LEN, COMMENT_LENGTH}
};
