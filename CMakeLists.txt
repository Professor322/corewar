cmake_minimum_required(VERSION 3.10.2)
project(CoreWar C)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-lncurses")
include_directories(libft/includes/ ./)
#include_directories(include)

#aux_source_directory(src/asm src_asm)
aux_source_directory(vm src_vm)
#aux_source_directory(src/ src)
#aux_source_directory(src/visu src_visu)


add_executable(corewar ${src_vm} op.h vm/utils.c vm/champions.c vm/cars.c vm/fight.c vm/operations.c vm/commands/ld.c vm/arg_utils.c vm/foreach_functions.c vm/testutils.c vm/commands/live.c vm/commands/st.c vm/commands/add.c vm/commands/sub.c vm/commands/and.c vm/commands/adjacent/and_or_xor.c vm/commands/or vm/commands/xor.c) # ${src_visu} ${src})
target_link_libraries(corewar ${PROJECT_SOURCE_DIR}/libft/libft.a)

target_include_directories(corewar PUBLIC vm/)

#add_executable(asm ${src_asm} ${src})
#target_link_libraries(asm ${PROJECT_SOURCE_DIR}/libft/lib/libft.a)
#
#target_include_directories(asm PUBLIC include/asm)