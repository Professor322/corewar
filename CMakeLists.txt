cmake_minimum_required(VERSION 3.13)

project(CoreWar C)


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

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
include_directories(libft/includes/ ./ ./vm/vis)
#include_directories(include)

#aux_source_directory(src/asm src_asm)
aux_source_directory(vm src_vm)
#aux_source_directory(src/ src)
aux_source_directory(vm/vis src_visu)


add_executable(corewar ${src_vm} op.h vm/utils.c vm/init_arena.c vm/cars.c vm/fight.c vm/operations.c vm/commands/ld.c vm/commands/common/arg_utils.c vm/commands/live.c vm/commands/st.c vm/commands/add.c vm/commands/sub.c vm/commands/and.c vm/commands/common/validation.c vm/commands/or vm/commands/xor.c vm/commands/zjmp.c vm/commands/aff.c vm/commands/ldi.c vm/commands/sti.c vm/commands/lld.c vm/commands/lldi.c vm/commands/fork.c vm/commands/lfork.c vm/commands/common/clone_utils.c vm/commands/common/command_utils.c vm/commands/common/arg_preparation.c vm/vis/draw_utils.c vm/vis/champ_interface.c vm/vis/update_info.c vm/vis/start_interface.c vm/vis/color_utils.c vm/vis/finish_interface.c vm/vis/info_interface.c vm/vis/catch_keyboard.c vm/vis/checks_interface.c) # ${src_visu} ${src})
target_link_libraries(corewar ${PROJECT_SOURCE_DIR}/libft/libft.a -lncurses)

target_include_directories(corewar PUBLIC vm/)

#add_executable(asm ${src_asm} ${src})
#target_link_libraries(asm ${PROJECT_SOURCE_DIR}/libft/lib/libft.a)
#
#target_include_directories(asm PUBLIC include/asm)