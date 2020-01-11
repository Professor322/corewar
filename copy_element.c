//
// Created by Virgil Legros on 11/01/2020.
//
#include "assembler.h"

int		copy_command(t_list **dst, t_node *node,
							   size_t capacity, t_ivec *loaded)
{
	const unsigned long index = ft_hash((unsigned char*)node->name, capacity);
	t_list				*temp;
	t_list				*new;

	temp = dst[index];
	if (!temp)
	{
		if (!(dst[index] = ft_lstnew(NULL, 0)))
			return (0);
		dst[index]->content = node;
		ft_int_vec_pushback(loaded, (int)index);
	}
	else
	{
		if (!(new = ft_lstnew(NULL, 0)))
			return (0);
		new->content = node;
		ft_lstadd(&dst[index], new);
	}
	return (1);
}

int		copy_label(t_list **dst, t_label *node,
							   size_t capacity, t_ivec *loaded)
{
	const unsigned long index = ft_hash((unsigned char*)node->name, capacity);
	t_list				*temp;
	t_list				*new;

	temp = dst[index];
	if (!temp)
	{
		if (!(dst[index] = ft_lstnew(NULL, 0)))
			return (0);
		dst[index]->content = node;
		ft_int_vec_pushback(loaded, (int)index);
	}
	else
	{
		if (!(new = ft_lstnew(NULL, 0)))
			return (0);
		new->content = node;
		ft_lstadd(&dst[index], new);
	}
	return (1);
}