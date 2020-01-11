//
// Created by Virgil Legros on 11/01/2020.
//
#include "../assembler.h"

int		ht_insert_label(t_ht *hashtable, t_label *node)
{
	unsigned long		index;
	t_list				*temp;
	t_list				*new;

	if (ht_enlarge(hashtable))
	{
		index = ft_hash((unsigned char*)node->name, hashtable->capacity);
		temp = hashtable->table[index];
		if (!temp)
		{
			if (!ht_help_insert(hashtable, node, index))
				return (0);
		}
		else
		{
			if (!(new = ft_lstnew(NULL, 0)))
				return (0);
			new->content = node;
			ft_lstadd(&hashtable->table[index], new);
		}
		hashtable->size++;
		return (1);
	}
	return (0);
}