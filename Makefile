NAME = cub3D
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I get_next_line -I $(MLX_DIR) -I$(LIBFT_DIR) -I /usr/include/X11
SRCS = main.c \
	parse_file.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@printf "\033[38;2;176;137;104m MiniLibX compilée.\033[0m\n"

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re