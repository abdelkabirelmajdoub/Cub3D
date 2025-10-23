/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:30:25 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/10/23 14:52:08 by ael-majd         ###   ########.fr       */
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

void darw_square(mlx_image_t *img, int start_x, int start_y, int color)
{
	for (int y = 0; y < TILE; y++)
	{
		for(int x = 0; x < TILE; x++)
		{
			if (start_x + x < WIDTH && start_y + y < HEIGHT)
			{
				if (x < 2 || y < 2)
					mlx_put_pixel(img, start_x + x, start_y + y , 0xCCCCCCFF);
				else
					mlx_put_pixel(img, start_x + x, start_y + y, color);	
			}
			
		}
	}
}


void draw_player(t_game *g, int start_x, int start_y, int color)
{
	int y;
	int x;

	y = 0;
	while(y < SIZE_P)
	{
		x = 0;
		while(x < SIZE_P)
		{
			if (start_x + x < WIDTH && start_y + y < HEIGHT)
				mlx_put_pixel(g->img,  start_x + x,  start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *g)
{
	int y, x;
	for (y = 0; g->map[y]; y++)
	{
		for(x = 0; g->map[y][x]; x++)
		{
			if (g->map[y][x] == '1')
				darw_square(g->img,  x * TILE,  y * TILE, 0x0000FFFF);
			else
				darw_square(g->img,  x * TILE,  y * TILE, 0xCCCCCCFF);
		}
	}
	
	
}

bool can_move(t_game *g, float new_x, float new_y)
{
    int grid_x = (int)(new_x / TILE);
    int grid_y = (int)(new_y / TILE);

    if (g->map[grid_y][grid_x] == '1')
        return false;
    return true;
}

bool touch(t_game *g, float px, float py)
{
	int x = (px / TILE);
	int y = (py / TILE);
	if (x <  0 || y < 0)
		return true;
	if (!g->map[y])
		return true;
	if (!g->map[y][x])
		return true;
	if (g->map[y][x] == '1')
		return true;
	return false;
}
float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}
void draw_line(t_game *g, float ray_angle, int i)
{
	float ray_x = g->player.x;
	float ray_y = g->player.y;
	float step_x = cos(ray_angle) * RES;
	float step_y = sin(ray_angle) * RES;
	
	// int max_steps = WIDTH * 4;
	// int steps = 0;
	while(!touch(g, ray_x, ray_y) )
	{
		if (DEBUG)
			if (ray_x >= 0 && ray_x < WIDTH && ray_y >= 0 && ray_y < HEIGHT)
                mlx_put_pixel(g->img, ray_x, ray_y, 0xFF0000FF);
		ray_x += step_x;
		ray_y += step_y;
	}	
	if (!DEBUG)
	{
		float dist = fixed_dist(g->player.x, g->player.y, ray_x, ray_y, g);
		if (dist < 0.1)
			dist = 0.1;
		float height = (TILE / dist) * (WIDTH / 2);
		if (height > HEIGHT * 2)
			height = HEIGHT * 2;
		int start_y = (HEIGHT - height) / 2;
		if (start_y < 0)
			start_y = 0;
		int end = start_y + height;
		if (end > HEIGHT)
			end = HEIGHT;
		while(start_y < end)
		{
			if (i >= 0 && i < WIDTH)
				mlx_put_pixel(g->img, i, start_y, 0x556B2FFF);
			start_y++;
		}
	}
}

void game_loop(void *param)
{
	t_game *g;

	g = (t_game *)param;
	float dx = g->player.x;
	float dy = g->player.y;
	
	
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		g->player.angle += ROT_SPEED;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		g->player.angle -= ROT_SPEED;

	
	mlx_set_cursor_mode(g->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(g->mlx, &g->player.mouse_x, &g->player.mouse_y);	
	g->player.angle += (g->player.mouse_x - g->player.prev_mouse_x) * 0.0025;
	mlx_set_mouse_pos(g->mlx, WIDTH / 2, HEIGHT / 2);
	g->player.prev_mouse_x = WIDTH / 2;

	if (g->player.angle < 0)
		g->player.angle += 2 * PI;
	if (g->player.angle > 2 * PI)
		g->player.angle -= 2 * PI;


	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		dx += cos(g->player.angle) * SPEED;
		dy += sin(g->player.angle) * SPEED;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		dx -= cos(g->player.angle) * SPEED;
		dy -= sin(g->player.angle) * SPEED;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		dx += cos(g->player.angle + PI/2) * SPEED;
		dy += sin(g->player.angle + PI/2) * SPEED;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		dx += cos(g->player.angle - PI/2) * SPEED;
		dy += sin(g->player.angle - PI/2) * SPEED;
	}

	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
		
	if (can_move(g, dx, g->player.y))
		g->player.x = dx;
	if (can_move(g, g->player.x, dy))
		g->player.y = dy;
		
	if (g->player.x < 0)
		g->player.x = 0;
	if (g->player.y < 0)
		g->player.y = 0;
	mlx_delete_image(g->mlx, g->img);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g->mlx, g->img, 0, 0);


	if (DEBUG)
	{
		draw_map(g);
		draw_player(g, g->player.x, g->player.y, 0xFFFF0000);
	}
	
	float start_angle = g->player.angle - FOV / 2;
	int i = 0;
	while (i < WIDTH)
	{
		start_angle += FOV / WIDTH;
		draw_line(g, start_angle, i);
		i++;
	}
	
}
void	init_game(t_game *g)
{
	g->mlx = mlx_init(WIDTH, HEIGHT, "3D Game", true);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g->mlx, g->img, 0, 0);
	g->player.prev_mouse_x = WIDTH;
}
void init_player(t_game *g)
{
	int x;
	int y;

	y = 0;
	while(g->map[y])
	{
		x = 0;
		while(g->map[y][x])
		{
			if (g->map[y][x] == 'W' || g->map[y][x] == 'S'
					|| g->map[y][x] == 'N' || g->map[y][x] == 'E')
			{
       			g->player.x = x * TILE + TILE / 2 - SIZE_P / 2;
                g->player.y = y * TILE + TILE / 2 - SIZE_P / 2;
				if (g->map[y][x] == 'E')
					g->player.angle = 0;
				if (g->map[y][x] == 'W')
					g->player.angle = PI;
				if (g->map[y][x] == 'S')
					g->player.angle =  3 * PI / 2;
				if (g->map[y][x] == 'N')
					g->player.angle = PI / 2;
			}
			x++;
		}
		y++;	
	}
	
}
void ll()
{
	system("leaks -q cub3D");
}

void free_up(char **s)
{
	int i = 0;
	while(s[i])
		free(s[i++]);
	free(s);
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
	free_up(game.map);
	mlx_terminate(game.mlx);
	// atexit(ll);
}
