/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:23:51 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/10/18 19:43:18 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
#include <math.h>
// # include "libft/libft.h"
# include <MLX42/MLX42.h>
#include <string.h>
/* ****************get_next_line*****************/
# ifndef GET_NEXT_LINE_H
#  define GET_NEXT_LINE_H

#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 45
#  endif
#  ifndef TILE
#   define TILE 64
#  endif
#define SIZE_P 15
#define SPEED 3
#define MARGIN 3
#define DEBUG 1

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);
int		ft_strchr(char *str);
int		ft_strlen(char *str);
char	*after_newline(char *str);
char	*before_newline(char *str);
# endif
/* ****************get_next_line*****************/
// ---- raycasting __///
#define WIDTH 1080
#define HEIGHT 720
#define PI  3.14159f
#define ROT_SPEED 0.05
#define FOV (PI / 3)
#define NUM_RAYS 60
#define RAY_STEP 5


typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	speed;

}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	char		**map;
} t_game;

/* ****************parsing*****************/


typedef struct s_textures
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
}	t_textures;

char	**convert_map(char *map_name, int start);
int		map_start(char *map_name);
int		count_chars(char *map_name);
int		count_line(char *map_name);
int		surrounded_bywalls(char **map, int line);
int		player_check(char **map, int line);
int		map_content(char **map, int line);
int		space_check(char **map, int line);
void	get_playerpos(char **map, int line, t_player	*player_pos);
int		map_pars(char **map, int map_lines, t_player *player_pos);
void	get_paths(t_textures *paths, int fd, int line);
char	**main_helper(char *map_name, t_player *player_pos);
char	**ft_split(char const *s, char c);
int		validate_color(char *str);
int		path_check(t_textures	*paths);
/* ****************parsing*****************/



#endif