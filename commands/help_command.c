/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 20:46:31 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/14 18:01:58 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assembler.h"

short	reverse_short(short s)
{
	unsigned char	c1;
	unsigned char	c2;

	c1 = s & 0xff;
	c2 = (s >> 8) & 0xff;
	return ((c1 << 8) + c2);
}

int		reverse_int(int s)
{
	unsigned short	c1;
	unsigned char	c2;

	c1 = reverse_short(s & 0xffff);
	c2 = reverse_short((s >> 16) & 0xffff);
	return ((c1 << 16) + c2);
}

int		ft_is_numeric(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

t_arg	*get_arg(char *arg, int dir_size, t_champ *champ, t_arg *arg_parse)
{
	if (*arg && *arg == 'r')
		reg_arg(arg_parse, arg, champ);
	else if (*arg && *arg == '%')
		dir_arg(arg_parse, dir_size, arg, champ);
	else if (*arg && *arg == ':')
	{
		label_init(arg_parse, 2, arg + 1, champ);
		arg_parse->type = T_IND;
	}
	else if (ft_is_numeric(arg))
		indir_arg(arg_parse, arg);
	return (arg_parse);
}
