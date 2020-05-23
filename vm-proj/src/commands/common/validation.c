/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djon-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:01 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/09 14:44:01 by djon-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm-proj/includes/corewar.h"

int	logical_validate_permitted_types(t_arg *args)
{
	if ((args[0].type == REG || args[0].type == DIR || args[0].type == IND)
		&&
		(args[1].type == REG || args[1].type == DIR || args[1].type == IND)
		&&
		args[2].type == REG
		&&
		args[3].type == NONE)
		return (1);
	return (0);
}

int	sub_add_validate_permitted_types(t_arg *args)
{
	if (args[0].type == REG
		&&
		args[1].type == REG
		&&
		args[2].type == REG
		&&
		args[3].type == NONE)
		return (1);
	return (0);
}
