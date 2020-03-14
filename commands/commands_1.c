/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:44:43 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/14 17:56:21 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

t_b_command		*add(char **command, t_champ *champ)
{
	t_b_command	*b_command;
	t_arg		*args;

	b_command = compile(ADD_COMMAND_CODE, champ, ADD_T_DIR_SIZE, command);
	args = b_command->args;
	if (args[0].type != T_REG || args[1].type != T_REG || args[2].type != T_REG)
	{
		ft_del_twodem_arr((void***)&command);
		error_manager(WRONG_TYPE_OF_ARGS, &champ);
	}
	ft_del_twodem_arr((void***)&command);
	return (b_command);
}

t_b_command		*aff(char **command, t_champ *champ)
{
	t_b_command	*b_command;
	t_arg		*args;

	b_command = compile(AFF_COMMAND_CODE, champ, AFF_T_DIR_SIZE, command);
	b_command->arg_type_code = (b_command->args[0].type << (unsigned int)6);
	args = b_command->args;
	champ->command_size += 1;
	if (args[0].type != T_REG)
	{
		ft_del_twodem_arr((void***)&command);
		error_manager(WRONG_TYPE_OF_ARGS, &champ);
	}
	ft_del_twodem_arr((void***)&command);
	return (b_command);
}

t_b_command		*and(char **command, t_champ *champ)
{
	t_b_command	*b_command;
	t_arg		*args;

	b_command = compile(AND_COMMAND_CODE, champ, AND_T_DIR_SIZE, command);
	args = b_command->args;
	if (args[2].type != T_REG)
	{
		ft_del_twodem_arr((void***)&command);
		error_manager(WRONG_TYPE_OF_ARGS, &champ);
	}
	ft_del_twodem_arr((void***)&command);
	return (b_command);
}

t_b_command		*ft_fork(char **command, t_champ *champ)
{
	t_b_command	*b_command;
	t_arg		*args;

	b_command = compile(FORK_COMMAND_CODE, champ, FORK_T_DIR_SIZE, command);
	args = b_command->args;
	if (args[0].type != T_DIR)
	{
		ft_del_twodem_arr((void***)&command);
		error_manager(WRONG_TYPE_OF_ARGS, &champ);
	}
	ft_del_twodem_arr((void***)&command);
	return (b_command);
}

t_b_command		*ld(char **command, t_champ *champ)
{
	t_b_command	*b_command;
	t_arg		*args;

	b_command = compile(LD_COMMAND_CODE, champ, LD_T_DIR_SIZE, command);
	args = b_command->args;
	if (args[1].type != T_REG)
	{
		ft_del_twodem_arr((void***)&command);
		error_manager(WRONG_TYPE_OF_ARGS, &champ);
	}
	ft_del_twodem_arr((void***)&command);
	return (b_command);
}
