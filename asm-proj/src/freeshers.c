/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeshers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: professor <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:52:12 by vlegros           #+#    #+#             */
/*   Updated: 2020/05/22 19:05:25 by professor        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

static void	del_ht_elem(t_list **head)
{
	t_list *temp;

	temp = *head;
	while (temp)
	{
		*head = temp;
		ft_memdel((void**)&(((t_node*)temp->content)->name));
		ft_memdel(&temp->content);
		temp = temp->next;
		ft_memdel((void**)head);
	}
}

static void	ht_delete(t_ht **hashtable)
{
	t_ht			*ht;
	const int		*data = (*hashtable)->loaded->data;
	const size_t	length = (*hashtable)->loaded->length;
	int				i;

	ht = *hashtable;
	i = -1;
	while (++i < (int)length)
		del_ht_elem(&(ht->table[data[i]]));
	free(ht->table);
	ft_int_vec_del(&ht->loaded);
	ft_memdel((void**)hashtable);
}

void		free_t_b_command(void **to_del)
{
	t_b_command	*b_command;
	int			i;
	t_arg		*args;

	b_command = (t_b_command *)*to_del;
	i = -1;
	args = (t_arg *)b_command->args;
	while (++i < 4)
	{
		if (args[i].label)
		{
			ft_strdel(&(args[i].label->name));
			ft_memdel((void**)args[i].label);
		}
	}
	ft_memdel((void**)&(b_command));
}

void		free_label_vec(void **to_del)
{
	t_arg *arg;

	arg = (t_arg *)*to_del;
	ft_strdel(&(arg->label->name));
	ft_memdel((void **)&arg->label);
}

void		free_memory_and_close_fd(t_champ **champ)
{
	t_champ *to_del;

	to_del = *champ;
	ft_memdel((void**)&to_del->name);
	ft_memdel((void**)&to_del->comment);
	ft_memdel((void**)&to_del->line);
	ft_memdel((void**)&to_del->o_filename);
	while (read_line(champ) > 0)
		ft_memdel((void**)&to_del->line);
	ft_ptr_vec_del(&to_del->temp_labels, ft_memdel);
	ft_ptr_vec_del(&to_del->labels_vec, free_label_vec);
	ft_ptr_vec_del(&to_del->command_vec, free_t_b_command);
	ht_delete(&to_del->labels);
	if (to_del->fd_input != -1)
		close(to_del->fd_input);
	if (to_del->fd_output != -1)
		close(to_del->fd_output);
	ft_memdel((void**)champ);
}
