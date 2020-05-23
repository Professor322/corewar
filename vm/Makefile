# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djon-con <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 18:20:55 by djon-con          #+#    #+#              #
#    Updated: 2020/05/23 13:53:36 by djon-con         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_MAKE = libft
VM_MAKE = vm
ASM_MAKE = asm-proj

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_MAKE)
	make -C $(VM_MAKE)
	make -C $(ASM_MAKE)

clean:
	make clean -C $(LIB_MAKE)
	make clean -C $(VM_MAKE)
	make clean -C $(ASM_MAKE)

fclean: clean
	make fclean -C $(LIB_MAKE)
	make fclean -C $(VM_MAKE)
	make fclean -C $(ASM_MAKE)

re: fclean all
