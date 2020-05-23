# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djon-con <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 13:58:28 by djon-con          #+#    #+#              #
#    Updated: 2020/05/23 15:29:28 by djon-con         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = gcc
CHECK_FLAGS = -Wall -Wextra -Werror
NAME = asm
OUT_DIR = ../
OUT_FILE = $(OUT_DIR)$(NAME)
ADD_CMD = ./commands/
RES_CMD = arg_handling.c\
	commands_1.c\
	commands_2.c\
	commands_3.c\
	commands_4.c\
	help_command.c
CMD_S = $(addprefix $(ADD_CMD), $(RES_CMD))
OBJ_CMD = $(CMD_S:.c=.o)
ADD_SRC = ./src/
RES_SRC = enlarge_table.c\
	error_manager.c\
	find_node.c\
	freeshers.c\
	insert_node.c\
	output_to_file.c\
	parse_args.c\
	parse_command.c\
	parse_exec.c\
	parse_header.c\
	parser.c\
	globals.c\
	utils.c\
	main.c
SRC_S = $(addprefix $(ADD_SRC), $(RES_SRC))
OBJ_SRC = $(SRC_S:.c=.o)
ADD_INC = ./includes/
ADD_LIB_H = ../libft/
ADD_LIBFT = ../libft/libft.a
CW_HEADER_PATH = ../
HEADERS = $(CW_HEADER_PATH)op.h $(ADD_INC)assembler.h

all: $(OUT_FILE)

$(OUT_FILE):  $(OBJ_CMD) $(OBJ_SRC)
	@$(COMPILER) -o $(OUT_FILE) $(CHECK_FLAGS) $(COMPILE_FLAGS) $(OBJ_SRC) $(OBJ_CMD) $(ADD_LIBFT)
	@echo ======[Done]======
%.o : %.c $(HEADERS)
	@echo "$(NAME) >>> Add/Update $<"
	@$(COMPILER) -c -o $@ -I $(ADD_INC) -I ../libft/includes -I $(CW_HEADER_PATH) $(CHECK_FLAGS) $<
clean:
	@rm -f $(ADD_SRC)*.o
	@rm -f $(ADD_CMD)*.o
fclean: clean
	@rm -f $(OUT_FILE)
re: fclean all