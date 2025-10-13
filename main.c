/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:30:25 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/10/13 15:09:15 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**main_helper(char *map_name, t_player *player_pos)
{
	char		**map;
	t_textures	*paths;
	int			fd;
	int			map_lines;
	int			map_s;

	fd = open(map_name, O_RDONLY);
	paths = malloc(sizeof(t_textures));
	if (!paths)
		return (free(player_pos), NULL);
	map_s = map_start(map_name);
	map = convert_map(map_name, map_s);
	get_paths(paths, fd, map_s);
	map_lines = 0;
	while (map[map_lines])
		map_lines++;
	if (map_pars(map, map_lines, player_pos) == 0
		|| path_check(paths) == 0)
		return (NULL);
	return (map);
}

void init_game(t_game *g)
{
	g->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!g->mlx)
	{
		perror("mlx_init error");
		exit(1);
	}
	g->img  = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img)
	{
		perror("new image error");
		exit(1);
	}

}
void	init_player(t_game *g){
	for(int y = 0; g->map[y]; y++)
	{
		for(int x = 0; g->map[y][x]; x++)
		{
			char c = g->map[y][x];
			if (c == 'N' || c == 'S'|| c == 'E' || c == 'W' )
			{
				g->player.x = x * TILE_SIZE + TILE_SIZE / 2;
				g->player.y = y * TILE_SIZE + TILE_SIZE / 2;
				g->player.speed = 3.0f;
				if (c == 'N') g->player.angle = PI / 2 * 3;
				if (c == 'S') g->player.angle = PI / 2;
				if (c == 'E') g->player.angle = 0;
				if (c == 'W') g->player.angle = PI;
				g->map[y][x] = '0';
				return ;
			}
		}
	}
}
void draw_map(t_game *g)
{
	int color;

	for (int y = 0; g->map[y]; y++)
	{
		for (int x = 0; g->map[y][x]; x++)
		{
			if (g->map[y][x] == '1')
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;

			for (int py = 0; py < TILE_SIZE; py++)
			{
				for (int px = 0; px < TILE_SIZE; px++)
				{
					int screen_x = x * TILE_SIZE + px;
					int screen_y = y * TILE_SIZE + py;
					if (screen_x >= 0 && screen_x < WIDTH &&
						screen_y >= 0 && screen_y < HEIGHT)
					{
						mlx_put_pixel(g->img, screen_x, screen_y, color);
					}
				}
			}
		}
	}
}

int is_wall(t_game *g, float x, float y)
{
	int mapX = (int)(x / TILE_SIZE);
	int mapY = (int)(y / TILE_SIZE);
	if (mapY < 0 || mapX < 0 || !g->map[mapY] || mapX >= (int)ft_strlen(g->map[mapY]))
		return (1);
	return (g->map[mapY][mapX] == '1');
}
void	draw_player(t_game *g)
{
	int size = 4;
	int x;
	int y;

	for(int px = -size; px <= size; px++)
	{
		for (int py = -size; py <= size; py++)
		{
			x = g->player.x + px;
			y = g->player.y + py;
			if (x >= 0 && y >= 0)
				mlx_put_pixel(g->img, x, y, 0xFF0000FF);
		}
		
	}
	
}

void	draw_ray(t_game *g, float ray_angle)
{
	float	ray_x = g->player.x;
	float	ray_y = g->player.y;
	float	step = RAY_STEP;

	float	dx = cosf(ray_angle) * step;
	float	dy = sinf(ray_angle) * step;

	for (int i = 0; i < 1000; i++)
	{
		if (is_wall(g, ray_x, ray_y))
			break;
		if (ray_x >= 0 && ray_y >= 0
			&& ray_x < WIDTH && ray_y < HEIGHT)
			mlx_put_pixel(g->img, (int)ray_x, (int)ray_y, 0x00FF00FF);
		ray_x += dx;
		ray_y += dy;
	}
}
void	draw_rays(t_game *g)
{
	float	start_angle = g->player.angle - (FOV / 2);
	float	angle_step = FOV / NUM_RAYS;

	for (int i = 0; i < NUM_RAYS; i++)
	{
		float ray_angle = start_angle + i * angle_step;
		draw_ray(g, ray_angle);
	}
}



void move_player(t_game *game)
{
	float moveStep = 0.0f;
	float moveX, moveY;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		moveStep = game->player.speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		moveStep = -game->player.speed;

	moveX = cosf(game->player.angle) * moveStep;
	moveY = sinf(game->player.angle) * moveStep;

	float newX = game->player.x + moveX;
	float newY = game->player.y + moveY;

	if (!is_wall(game, newX, game->player.y))
		game->player.x = newX;
	if (!is_wall(game, game->player.x, newY))
		game->player.y = newY;

	// rotation
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.angle -= 0.05f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.angle += 0.05f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void game_loop(void *param)
{
	t_game *g = (t_game *)param;

	mlx_delete_image(g->mlx, g->img);
	g->img  = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	move_player(g);
	draw_map(g);
	draw_rays(g);
	draw_player(g);

	mlx_image_to_window(g->mlx, g->img, 0, 0);
}
int	main(int ac, char **av)
{
	t_game		game;

	if (ac != 2)
	{
		perror("Wrong Number of args!");
		return (1);
	}
	game.map = main_helper(av[1], &game.player);
	if (!game.map)
	{
		perror("Fix your map/paths");
		return (1);
	}
	
	init_game(&game);
	init_player(&game);

	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}
