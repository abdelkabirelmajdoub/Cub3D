NAME	= ../cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRC		= 	main_bonus.c dda_bonus.c init_bonus.c collision_bonus.c draw_bonus.c game_loop_bonus.c textures_bonus.c d_utils_bonus.c \
			parsing/extra_func_bonus.c \
 			parsing/get_next_line_utils_bonus.c parsing/get_next_line_bonus.c parsing/map_parsing_bonus.c parsing/map_pars_bonus.c parsing/texture_pars_bonus.c\
			parsing/ft_split_bonus.c



OBJS	= $(SRC:.c=.o)


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
	@	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FLAGMLX) -o $(NAME)

%.o: %.c cub3d_bonus.h
	@	$(CC) $(CFLAGS) -c $< -I$(MLX42_INC) -o $@

clean:
	@	rm -f $(OBJS)


