
NAME	= cub3D

CC		= cc 
CFLAGS	= -Wall -Wextra -Werror

SRC		= main.c

LIBFT	= libft/libft.a
MLX		= mlx/libmlx.a
FLAGMLX = -framework OpenGL -framework AppKit
OBJS	= $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJS)
	@	echo "\033[1;32m  🛤  Building cub3D... 🔮     \033[0m"
	@	make -C libft
	@	make -C mlx
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(FLAGMLX) -o $(NAME)

%.o:%.c 
	@	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@	make clean -C libft
	@	make clean -C mlx
	@	rm -f $(OBJS)

fclean: clean
	@	make fclean -C libft
	@	rm -f $(NAME)

re: fclean all