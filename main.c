//
// Created by Virgil Legros on 17/01/2020.
//

#include "assembler.h"

t_champ *champ_init()
{
	t_champ	*champ;

	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	champ->temp_labels = ft_ptr_vec_init();
	champ->file_labels = ft_ptr_vec_init();
	champ->labels = ft_ht_init();
	champ->command_vec = ft_ptr_vec_init();
	//champ->cumulative_size = ft_int_vec_init();
	champ->labels_vec = ft_ptr_vec_init();
	champ->name = NULL;
	champ->comment = NULL;
	return (champ);
}

int 	main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	t_champ *champ;

	champ = champ_init();

	ft_parse(fd, champ);
	write_exec_code_in_file(open("test.cor", O_CREAT | O_WRONLY , 0644),
			champ->command_vec, "test.cor", champ);

	printf("\n");
//	for (int i = 0; i < (int)champ->command_vec->length; i++)
//    {
//        printf("\n%c\t", ((t_b_command*)(champ->command_vec->data[i]))->is_after);
//
//        printf("%d\n", ((t_b_command*)(champ->command_vec->data[i]))->cumulative_size);
//
//    }
//
//	printf("__________________\n");
//	t_node *hash_label;
//
//	for (int i = 0; i < (int)champ->labels_vec->length; i++ )
//    {
//        char *name = ((t_arg*)((t_label *)(champ->labels_vec->data[i])))->label->name;
//        printf("%s\t%c\t", name,((t_arg*)((t_label *)(champ->labels_vec->data[i])))->label->is_after);
//	    printf("%d\t", ((t_arg*)((t_label *)(champ->labels_vec->data[i])))->label->cumulate_size);
//	    if ((hash_label =  ht_find_node(champ->labels, name)))
//	        printf("%s\t%d\n", hash_label->name, hash_label->command->cumulative_size);
//    }
	return (0);



}