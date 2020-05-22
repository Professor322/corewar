COMPILER = gcc
CHECK_FLAGS = -Wall -Wextra -Werror
NAME = asm
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
ADD_LIB_H = ./libft/
ADD_LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME):  $(OBJ_CMD) $(OBJ_SRC)
	@make  -C ./libft all
	@$(COMPILER) -o $(NAME) $(CHECK_FLAGS) $(COMPILE_FLAGS) $(OBJ_SRC) $(OBJ_CMD) $(ADD_LIBFT)
	@echo ======[Done]======
%.o : %.c
	@echo "$(NAME) >>> Add/Update $<"
	@$(COMPILER) -c -o $@ -I $(ADD_INC) -I ./libft/includes $(CHECK_FLAGS) $<
clean:
	@rm -f $(ADD_SRC)*.o
	@rm -f $(ADD_CMD)*.o
	@make  -C ./libft clean
fclean: clean
	@rm -f ./$(NAME)
	@make -C ./libft fclean
re: fclean all