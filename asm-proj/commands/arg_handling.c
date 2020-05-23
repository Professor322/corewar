/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:55:20 by jziemann          #+#    #+#             */
/*   Updated: 2020/03/14 17:53:53 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void			indir_arg(t_arg *arg_parse, char *arg)
{
	unsigned int	ind_val;
	int				temp;

	temp = ft_atoi(arg);
	ind_val = temp < 0 ? ~((temp * -1)) + 1 : temp;
	arg_parse->type = T_IND;
	arg_parse->size = 2;
	arg_parse->bin = reverse_short((short)ind_val);
}

void			*label_init(t_arg *arg, int size, char *l_name, t_champ *champ)
{
	t_b_command		*byte_command;
	const size_t	index = champ->command_vec->length - 1;

	byte_command = (t_b_command*)(champ->command_vec->data[index]);
	if (!(arg->label = (t_label *)ft_memalloc(sizeof(t_label))))
		return (NULL);
	arg->label->name = ft_strdup(l_name);
	arg->label->cumulate_size = byte_command->cumulative_size;
	arg->is_label = 1;
	arg->size = size;
	ft_ptr_vec_pushback(champ->labels_vec, arg);
	return (byte_command);
}

void			*dir_arg(t_arg *arg_pars, int d_size, char *arg, t_champ *champ)
{
	unsigned int	dir_val;
	int				temp;

	if (arg[1] && arg[1] == ':')
	{
		if (!(label_init(arg_pars, d_size, arg + 2, champ)))
			return (NULL);
	}
	else
	{
		temp = ft_atoi(++arg);
		dir_val = temp < 0 ? ~(temp * -1) + 1 : temp;
		arg_pars->bin = d_size == 4 ? reverse_int((int)dir_val) :
			reverse_short((short)dir_val);
		arg_pars->size = d_size;
	}
	arg_pars->type = T_DIR;
	return (arg_pars);
}

void			reg_arg(t_arg *arg_parse, char *arg)
{
	int	r_val;

	r_val = ft_atoi(++arg);
	arg_parse->size = 1;
	arg_parse->type = T_REG;
	arg_parse->bin = r_val;
}

t_b_command		*compile(int cmd_code, t_champ *champ, int d_size, char **cmd)
{
	t_b_command		*b_cmd;
	int				i;
	unsigned int	byte_shift;
	t_arg			*arg;

	b_cmd = init_b_cmd(cmd_code, champ, cmd);
	i = -1;
	byte_shift = 6;
	while (*cmd)
	{
		if (!(arg = get_arg(*cmd, d_size, champ, &b_cmd->args[++i])))
			help_error(cmd, MALLOC_ERROR, &champ);
		b_cmd->args[i] = *arg;
		if ((*cmd++ && i != 0) || i > 0)
		{
			if (i == 1)
				b_cmd->arg_type_code += b_cmd->args[i - 1].type << byte_shift;
			byte_shift -= 2;
			b_cmd->arg_type_code += b_cmd->args[i].type << byte_shift;
		}
		champ->command_size += (b_cmd->args[i].size + (i < 2));
	}
	return (b_cmd);
}
