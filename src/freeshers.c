//
// Created by Virgil Legros on 17/02/2020.
//

#include "../assembler.h"

static void		del_ht_elem(t_list **head)
{
	t_list *temp;

	temp = *head;
	while (temp)
	{
		*head = temp;
		ft_memdel(&temp->content);
		temp = temp->next;
		ft_memdel((void**)head);
	}
}

static void		ht_delete(t_ht **hashtable)
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


void	finish_him(t_champ **champ)
{
	t_champ *to_del;

	if (*champ)
	{
		to_del = *champ;
		ft_memdel((void **) &to_del->name);
		ft_memdel((void **) &to_del->comment);
		ft_ptr_vec_del(&to_del->temp_labels, ft_memdel);
		ht_delete(&to_del->labels);
		ft_memdel((void **) champ);
	}
	exit(1);
}
