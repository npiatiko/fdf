#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/08 10:57:33 by npiatiko          #+#    #+#              #
#    Updated: 2019/02/08 10:57:34 by npiatiko         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

FLAGS1 = -Wall -Wextra -Werror
FLAGS2 =  -lmlx -framework OpenGL -framework Appkit
SRCS =	./src/aux_fns.c \
        ./src/deal.c \
        ./src/main.c \
        ./src/painter.c \
        ./src/parser.c \
        ./src/projections.c \
        ./src/rotate.c

all: libft $(NAME)

OBJ = $(SRCS:.c=.o)

.PHONY : libft
libft:
	@make -C./libft

$(NAME): $(OBJ) libft/libft.a
	gcc -o $(NAME) $(OBJ) $(FLAGS2) ./libft/libft.a -I ./inc

%.o: %.c $(INC) inc/fdf.h
	gcc -o $@ -c $< $(FLAGS1) -I ./inc -I ./libft/includes

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all