/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:57:38 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/14 17:59:17 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

void			help_error(char **to_del, int type, t_champ **champ)
{
	ft_del_twodem_arr((void***)&to_del);
	error_manager(type, champ);
}

t_b_command		*zjmp(char **command, t_champ *champ)
{
	t_b_command	*b_command;
	t_arg		*args;

	b_command = compile(ZJMP_COMMAND_CODE, champ, ZJMP_T_DIR_SIZE, command);
	args = b_command->args;
	if (args[0].type != T_DIR)
		help_error(command, WRONG_TYPE_OF_ARGS, &champ);
	ft_del_twodem_arr((void***)&command);
	return (b_command);
}
