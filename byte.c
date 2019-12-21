/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:05:50 by jziemann          #+#    #+#             */
/*   Updated: 2019/11/13 21:05:50 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/includes/libft.h"

int amount_real_bytes(unsigned int num) {
    int amount;

    amount = 0;
    if (!num)
        return (0);
    while (num > 0)
    {
        amount++;
        num >>= 8;
    }
    if (amount % 2 == 0)
        return (3 - amount);
    else
        return (4 - amount);
}

int main(int argc, char **argv)
{
	int num;
	int i;
	int size;
	int *byte; // not array, struct which contains numeric and amount real byte, array[struct]
	int b = num;

	size = ft_atoi(argv[2]);
	num = ft_atoi(argv[1]);
    byte = ft_memalloc(size);
    byte = ft_memset(byte, (char)num, 1);

//    write(1, "\n", 1);
//    write(1, byte, size);
//    write(1, "\n", 1);
    printf("\n%d\n", i = amount_real_bytes(num));
    num <<= 8 * i;
    write(1, &num, size);

//    write(1, &(num ), size);

	return (0);
}