cmake_minimum_required(VERSION 3.12)
project(LIBFT LANGUAGES C)

set(CMAKE_C_STANDARD 99)
AUX_SOURCE_DIRECTORY(./ LIB_SRCS)
add_library(LIBFT STATIC ${LIB_SRCS})
target_include_directories(LIBFT PUBLIC ./includes)
target_compile_options(LIBFT PUBLIC -Wall -Wextra)