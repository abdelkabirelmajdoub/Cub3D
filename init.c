/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:04:19 by ael-majd          #+#    #+#             */
/*   Updated: 2025/11/09 10:48:33 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_sizeof_map(t_game *g)
{
	int	i;
	int	len;

	i = 0;
	g->map_height = 0;
	g->map_height = 0;
	while (g->map[i])
	{
		len = ft_strlen(g->map[i]);
		if (len > g->map_width)
			g->map_width = len;
		i++;
	}
	g->map_height = i;
}

void	init_game(t_game *g)
{
	g->mlx = mlx_init(WIDTH, HEIGHT, "3D Game", true);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g->mlx, g->img, 0, 0);
	g->player.prev_mouse_x = WIDTH / 2;
	g->show_map = 0;
	g->player.mouse_locked = false;
	set_sizeof_map(g);
}

void	set_direction_player(t_game *g, int x, int y)
{
	if (g->map[y][x] == 'E')
		g->player.angle = 0.0f;
	if (g->map[y][x] == 'W')
		g->player.angle = M_PI;
	if (g->map[y][x] == 'S')
		g->player.angle = M_PI / 2;
	if (g->map[y][x] == 'N')
		g->player.angle = (3 * M_PI) / 2;
}

void	init_player(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'W' || g->map[y][x] == 'S'
					|| g->map[y][x] == 'N' || g->map[y][x] == 'E')
			{
				g->player.x = x * TILE + TILE / 2;
				g->player.y = y * TILE + TILE / 2;
				set_direction_player(g, x, y);
			}
			x++;
		}
		y++;
	}
}

void	free_up(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
