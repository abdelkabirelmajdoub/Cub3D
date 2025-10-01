/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:30:25 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/09/30 10:58:44 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_texture(mlx_image_t *img, mlx_texture_t *tex, int x, int y)
{
	int	i, j;
	uint32_t	color;

	for (i = 0; i < TILE_SIZE; i++)
	{
		for (j = 0; j < TILE_SIZE; j++)
		{
			int tex_x = j * tex->width / TILE_SIZE;
			int tex_y = i * tex->height / TILE_SIZE;
			uint8_t *pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];

			color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
			mlx_put_pixel(img, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
		}
	}
}

void	draw_square(mlx_image_t *img, int x, int y, int size, uint32_t color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			mlx_put_pixel(img, x + j, y + i, color);
	}
}

void	mlx_loading(char **map, t_textures *path)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*wall_tex;
	int				y;
	int				x;

	mlx = mlx_init(800 , 600, "cub3D", true);
	if (!mlx)
		return ;
	img = mlx_new_image(mlx, 800, 600);
	if (!img)
		return ;
	wall_tex = mlx_load_png(path->no_path);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_texture(img, wall_tex, x, y);
			else if (map[y][x] == '0')
				draw_square(img, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0xFFFFFFFF);
			else if (map[y][x] == 'N' || map[y][x] == 'S' ||
					map[y][x] == 'E' || map[y][x] == 'W')
				draw_square(img, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0xFF0000FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_delete_texture(wall_tex);
	mlx_terminate(mlx);
}

int	main_helper(char *map_name)
{
	char		**map;
	t_player		*player_pos;
	t_textures	*paths;
	int			fd;
	int			map_lines;
	int			map_s;

	fd = open(map_name, O_RDONLY);
	player_pos = malloc(sizeof(t_player));
	if (!player_pos)
		exit(0);
	paths = malloc(sizeof(t_textures));
	if (!paths)
		return (free(player_pos), 0);

	map_s = map_start(map_name);
	map = convert_map(map_name, map_s);
	get_paths(paths, fd, map_s);
	map_lines = 0;
	while (map[map_lines])
		map_lines++;
	if (map_pars(map, map_lines, player_pos) == 0
		|| path_check(paths) == 0)
		return (0);
	mlx_loading(map, paths);
	return (1);
}

int	main(int ac, char **av)
{
	char		*map_name;

	if (ac != 2)
	{
		perror("Wrong Number of args!");
		return (1);
	}
	map_name = av[1];
	if (main_helper(map_name) == 0)
	{
		perror("Fix your map/paths");
		return (0);
	}
}
