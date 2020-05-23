# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbartole <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 18:20:55 by djon-con          #+#    #+#              #
#    Updated: 2020/05/17 20:53:19 by mbartole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
VM_SRC = vm/
COMMANDS_SRC = commands/
COMMON_SRC = common/
VIS_SRC = vis/
SRC = $(addprefix $(VM_SRC),  cars.c \
                              champions.c \
                              champions_parse.c \
                              fight.c \
                              main.c \
                              operations.c \
                              parse_input.c \
                              priority_queue.c \
                              utils.c) \
      $(addprefix $(VM_SRC)$(COMMANDS_SRC), add.c \
                                            aff.c \
                                            and.c \
                                            fork.c \
                                            ld.c \
                                            ldi.c \
                                            lfork.c \
                                            live.c \
                                            lld.c \
                                            lldi.c \
                                            or.c \
                                            st.c \
                                            sti.c \
                                            sub.c \
                                            xor.c \
                                            zjmp.c)\
      $(addprefix $(VM_SRC)$(COMMANDS_SRC)$(COMMON_SRC), arg_preparation.c\
                                                         arg_utils.c\
                                                         clone_utils.c\
                                                         command_utils.c\
                                                         validation.c)\
      $(addprefix $(VM_SRC)$(VIS_SRC), catch_keyboard.c \
                                       champ_interface.c \
                                       checks_interface.c \
                                       color_utils.c \
                                       draw_utils.c \
                                       finish_interface.c \
                                       info_interface.c \
                                       start_interface.c \
                                       update_info.c) \
LIB_PATH = libft/
LIB_HEADER_PATH = $(LIB_PATH)includes/
HEADER_PATH = vm/
CW_ORIGINAL_HEADER_PATH = ./
HEADER = $(addprefix $(LIB_HEADER_PATH), libft.h get_next_line.h ft_printf.h float.h) vm/corewar.h vm/pque.h vm/vis/vis.h op.h
INCLUDE_FLAGS = -I $(HEADER_PATH) -I $(LIB_HEADER_PATH) -I $(CW_ORIGINAL_HEADER_PATH)
WARNING_FLAGS = -W -Werror -Wextra -Wall
LIB = $(LIB_PATH)libft.a
OBJ = $(SRC:.c=.o)

.PHONY: clean fclean re

all: $(NAME)
	echo $(SRC)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)
	gcc $(LIB) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(INCLUDE_FLAGS) $(WARNING_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIB_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_PATH)

re: fclean all
