# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djon-con <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 18:20:55 by djon-con          #+#    #+#              #
#    Updated: 2020/05/23 14:39:07 by djon-con         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
OUT_DIR = ../
OUT_FILE = $(OUT_DIR)$(NAME)
VM_SRC = src/
COMMANDS_SRC = $(VM_SRC)commands/
COMMON_SRC = $(COMMANDS_SRC)common/
VIS_SRC = $(VM_SRC)vis/
SRC = $(addprefix $(VM_SRC), \
		cars.c \
		champions_parse.c \
		fight.c \
		init_arena.c \
		main.c \
		operations.c \
		parse_input.c \
		priority_queue.c \
		utils.c) \
	$(addprefix $(COMMANDS_SRC), \
		add.c \
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
	$(addprefix $(COMMON_SRC), \
		arg_preparation.c\
		arg_utils.c\
		clone_utils.c\
		command_utils.c\
		validation.c) \
	$(addprefix $(VIS_SRC), \
		catch_keyboard.c \
		champ_interface.c \
		checks_interface.c \
		color_utils.c \
		draw_utils.c \
		finish_interface.c \
		info_interface.c \
		start_interface.c \
		update_info.c)
LIB_PATH = ../libft/
LIB_HEADER_PATH = $(LIB_PATH)includes/
HEADER_PATH = includes/
CW_ORIGINAL_HEADER_PATH = ../
VIS_HEADER_PATH = $(HEADER_PATH)vis/
HEADER = $(addprefix $(LIB_HEADER_PATH), libft.h get_next_line.h ft_printf.h float.h) \
	$(addprefix $(HEADER_PATH), corewar.h pque.h vis.h) \
	$(addprefix $(CW_ORIGINAL_HEADER_PATH), op.h)
VIS_FLAG = -lncurses
INCLUDE_FLAGS = -I $(HEADER_PATH) \
	-I $(LIB_HEADER_PATH) \
	-I $(CW_ORIGINAL_HEADER_PATH) \
	-I $(VIS_HEADER_PATH)
WARNING_FLAGS = -W -Werror -Wextra -Wall
LIB = $(LIB_PATH)libft.a
OBJ = $(SRC:.c=.o)

.PHONY: clean fclean re

all: $(OUT_FILE)
	echo $(SRC)

$(OUT_FILE): $(OBJ)
	gcc $(OBJ) -o $(OUT_FILE) $(VIS_FLAG) $(LIB)

%.o: %.c $(HEADER)
	gcc $(INCLUDE_FLAGS) $(WARNING_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(OUT_FILE)

re: fclean all
