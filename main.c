/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:30:25 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/09/20 10:39:19 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_texture(mlx_t *mlx, mlx_texture_t *tex, int x, int y)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(mlx, tex);
	if (!img)
		return;
	mlx_image_to_window(mlx, img, x * TILE_SIZE, y * TILE_SIZE);
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
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			y;
	int			x;

	mlx = mlx_init(800, 600, "cub3D", true);
	if (!mlx)
		return ;
	img = mlx_new_image(mlx, 800, 600);
	if (!img)
		return ;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_texture(mlx, mlx_load_png(path->no_path), x, y);
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
	mlx_terminate(mlx);
}

int	main_helper(char *map_name)
{
	char		**map;
	t_player		*player_pos;
	t_textures	*paths;
	int			fd;
	int			map_lines;

	fd = open(map_name, O_RDONLY);
	player_pos = malloc(sizeof(t_player));
	if (!player_pos)
		exit(0);
	paths = malloc(sizeof(t_textures));
	if (!paths)
		return (free(player_pos), 0);
	get_paths(paths, fd);
	map = convert_map(map_name);
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
