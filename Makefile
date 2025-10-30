NAME	= cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRC		= main.c dda.c init.c collision.c draw.c game_loop.c \
 			parsing/get_next_line_utils.c parsing/get_next_line.c parsing/map_parsing.c parsing/map_pars.c parsing/texture_pars.c\
			parsing/ft_split.c 



OBJS	= $(SRC:.c=.o)

LIBFT	= libft/libft.a

BREW_PREFIX = $(shell brew --prefix glfw)

MLX42_INC = $(HOME)/.local/include
MLX42_LIB = $(HOME)/.local/lib
GLFW_INC  = $(BREW_PREFIX)/include
GLFW_LIB  = $(BREW_PREFIX)/lib

FLAGMLX = -I$(MLX42_INC) -I$(GLFW_INC) \
          -L$(MLX42_LIB) -L$(GLFW_LIB) \
          -lmlx42 -lglfw \
          -framework OpenGL -framework Cocoa -framework IOKit 
all: $(NAME)

$(NAME): $(OBJS)
	@	echo "\033[1;32m  🛤  Building cub3D ... 🔮     \033[0m"
	@	make -C libft
	@	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FLAGMLX) -o $(NAME)

%.o: %.c cub3d.h
	@	$(CC) $(CFLAGS) -c $< -I$(MLX42_INC) -o $@

clean:
	@	make clean -C libft
	@	rm -f $(OBJS)

fclean: clean
	@	make fclean -C libft
	@	rm -f $(NAME)

re: fclean all


