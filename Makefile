NAME	= cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRC		= main.c


OBJS	= $(SRC:.c=.o)

LIBFT	= libft/libft.a


MLX42_INC = $(HOME)/.local/include
MLX42_LIB = $(HOME)/.local/lib

FLAGMLX = -I$(MLX42_INC) -L$(MLX42_LIB) -lmlx42 -lglfw \
          -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation

all: $(NAME)

$(NAME): $(OBJS)
	@	echo "\033[1;32m  🛤  Building cub3D with MLX42... 🔮     \033[0m"
	@	make -C libft
	@	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FLAGMLX) -o $(NAME)

%.o: %.c
	@	$(CC) $(CFLAGS) -c $< -I$(MLX42_INC) -o $@

clean:
	@	make clean -C libft
	@	rm -f $(OBJS)

fclean: clean
	@	make fclean -C libft
	@	rm -f $(NAME)

re: fclean all
