NAME = fdf

FLAGS = -Wall -Wextra -Werror
CC = gcc $(FLAGS)

MLX_HEAD = /usr/local/include
MLX_SRCS = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

LIB_D = libft
LIB_HEAD = $(LIB_D)/includes
LIB_SRCS = -L $(LIB_D) -lft
LIBFT = $(addprefix $(LIB_D)/, libft.a)

INCLS = -I $(MLX_HEAD) -I $(LIB_HEAD)

SRCS =	main.c \
		parser.c \
		painter.c \
		aux_fns.c \
		rotate.c \
		deal.c \
		projections.c

OBJS_D = ./objs
OBJS = $(addprefix $(OBJS_D)/, $(SRCS:.c=.o))

all: $(OBJS_D) $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) all -C $(LIB_D)

$(OBJS_D):
	@mkdir -p $(OBJS_D)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(SRCS) $(MLX_SRCS) $(LIB_SRCS) $(INCLS)

$(OBJS_D)/%.o: %.c *.h libft/includes/*.h $(MLX_HEAD)/*.h
	$(CC) -o $@ -c $< $(INCLS)

clean:
	@rm -rf $(OBJS_D)

fclean: clean
	@$(MAKE) fclean -C $(LIB_D)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re