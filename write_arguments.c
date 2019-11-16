//
// Created by Dacey mormont Jon connington on 16/11/2019.
//

#include "assembler.h"

void	write_one_argument(char **bin, t_arg arg)
{
	if (arg.size != 0)
	{
		ft_memcpy(*bin, arg.bin, arg.size);
		(*bin) += arg.size;
	}
}

void	write_arguments(char *bin, t_arg arg1, t_arg arg2, t_arg arg3)
{
	write_one_argument(&bin, arg1);
	write_one_argument(&bin, arg2);
	write_one_argument(&bin, arg3);
}
