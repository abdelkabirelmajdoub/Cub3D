/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:23:51 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/11/02 13:59:04 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <float.h>
// # include "libft/libft.h"
# include <MLX42/MLX42.h>

// #include <string.h>
/* ****************get_next_line*****************/


char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);
int		ft_strchr(char *str);
int		ft_strlen(char *str);
char	*after_newline(char *str);
char	*before_newline(char *str);

/* ****************get_next_line*****************/
/* **************** SETTINGS *****************/

# ifndef GET_NEXT_LINE_H
#  define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 45
#endif
#endif

#define TILE 64
#define SIZE_P 25
#define SPEED 3
#define MARGIN 1
#define WIDTH 1920
#define HEIGHT 1080
#define ROT_SPEED 0.01
#define FOV  M_PI/3
#define RES 0.3




// ---- raycasting __///


typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	speed;
	float	prev_mouse_x;
	int32_t	mouse_x;
	int32_t	mouse_y;
	bool mouse_locked;
}	t_player;


typedef struct s_textures
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
}	t_textures;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	char			**map;
	int				show_map;
	int				map_width;
	int				map_height;
	t_textures		*text_paths;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
} t_game;


typedef struct s_dda
{
	int		map_x;
	int 	map_y;
	int 	step_x;
	int 	step_y;
	int 	hit;
	int 	side;
	float	x_tile;
	float	y_tile;
	float	ray_x;
	float	ray_y;
	float	side_x;
	float	side_y;
	float	delta_x;
	float	delta_y;
	float	perp_wall;
	mlx_texture_t *tex;
}			t_dda;

/* ****************parsing*****************/



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

// ----- raycating ----//
void	init_game(t_game *g);
void    init_player(t_game *g);
void    free_up(char **s);
// --- drawing --//
void    darw_square(mlx_image_t *img, int start_x, int start_y, int color);
void	draw_player(t_game *g, float cx, float cy, int color);
void	draw_map(t_game *g);
bool	touch(t_game *g, float px, float py);
bool    can_move(t_game *g, float new_x, float new_y);
void	game_loop(void *param);
void	draw_line(t_game *g, float ray_angle, int i);
void	draw_rays(t_game *g);
void	tree_d_render(t_game *g);
void	texture_init(t_game *g);
uint32_t get_tex_color(mlx_texture_t *tex, int x, int y);
#endif