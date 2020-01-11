/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:10:02 by vlegros           #+#    #+#             */
/*   Updated: 2019/11/11 22:10:02 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "src/tests.h"

int 	main(int argc, char **argv)
{
	if (argc == 4)
		printf("test_all_separetly: %d", test_all(argv[1], argv[2], argv[3]));

	return (0);
}