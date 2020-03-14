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

void    free_t_b_command(void **to_del)
{
    t_b_command *b_command;
    int         i;
    t_arg       *args;

    b_command = (t_b_command *)*to_del;
    i = -1;
    args = (t_arg *)b_command->args;
    while (++i < 4)
    {
        if (args[i].label)
        {
            printf("%s\n", args[i].label->name);
            ft_strdel(&(args[i].label->name));
            ft_memdel((void**)args[i].label);
        }
    }
    ft_memdel((void**)&(b_command));
}

void    free_label_vec(void **to_del)
{
    t_arg *arg;

    arg = (t_arg *)*to_del;
    ft_strdel(&(arg->label->name));
    ft_memdel((void **)&arg->label);
}

void	free_memory(t_champ **champ)
{
	t_champ *to_del;

	to_del = *champ;
	ft_memdel((void **) &to_del->name);
	ft_memdel((void **) &to_del->comment);
	ft_ptr_vec_del(&to_del->temp_labels, ft_memdel);
    //`Vera delete
    ft_ptr_vec_del(&to_del->labels_vec, free_label_vec);
    ft_ptr_vec_del(&to_del->command_vec, free_t_b_command);
    //all delete
	ht_delete(&to_del->labels);
	ft_memdel((void**)&to_del->line);
	while (read_line(champ)) {
		ft_memdel((void**)&to_del->line);
	}
	ft_memdel((void **) champ);
}

void	finish_him(t_champ **champ)
{
	if (*champ)
		free_memory(champ);
	exit(1);
}
