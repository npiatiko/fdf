cmake_minimum_required(VERSION 3.12)
project(fdf)

add_subdirectory(./libft)
set(CMAKE_C_STANDARD 99)

add_executable(fdf main.c fdf.h parser.c painter.c atoi_hex.c)
target_link_libraries(fdf LIBFT)