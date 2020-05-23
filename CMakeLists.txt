cmake_minimum_required(VERSION 3.13)

project(asm)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")

FILE(GLOB ft_printf ./libft/ft_printf/*.c)
FILE(GLOB str_func ./libft/str_funcs/*.c)
FILE(GLOB digit_func ./libft/digit_funcs/*.c)
FILE(GLOB char_func ./libft/char_funcs/*.c)
FILE(GLOB useful_func ./libft/useful_funcs/*.c)
FILE(GLOB lst_func ./libft/lst_funcs/*.c)
FILE(GLOB int_vec_func ./libft/vec_funcs/int_vec/*.c)
FILE(GLOB ptr_vec_func ./libft/vec_funcs/ptr_vec/*.c)
FILE(GLOB memes_func ./libft/mem_funcs/*.c)
FILE(GLOB char_vec ./libft/vec_funcs/char_vec/*.c)
FILE(GLOB coms asm-proj/commands/*.c)

include_directories( ./libft/includes)

add_executable(asm
        asm-proj/src/parse_command.c
        asm-proj/src/find_node.c
        asm-proj/src/enlarge_table.c
        asm-proj/src/find_node.c
        asm-proj/src/output_to_file.c
        asm-proj/src/insert_node.c
        asm-proj/src/parse_header.c
        asm-proj/src/freeshers.c
        asm-proj/src/error_manager.c
        asm-proj/src/parse_args.c
        asm-proj/src/parse_exec.c
        asm-proj/src/parser.c
        asm-proj/src/utils.c
        ${coms}
        ${useful_func}
        asm-proj/src/main.c asm-proj/src/globals.c)
target_link_libraries(asm ~/Desktop/corewar/libft/libft.a)
