/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:04:19 by ael-majd          #+#    #+#             */
/*   Updated: 2025/10/30 10:17:01 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *g)
{
	g->mlx = mlx_init(WIDTH, HEIGHT, "3D Game", true);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g->mlx, g->img, 0, 0);
	g->player.prev_mouse_x = WIDTH;
    g->show_map = 0;
	g->player.mouse_locked = true;
}

void    set_direction_player(t_game *g, int x, int y)
{
    if (g->map[y][x] == 'E')
        g->player.angle = 0;
    if (g->map[y][x] == 'W')
        g->player.angle = PI;
    if (g->map[y][x] == 'S')
        g->player.angle = PI / 2;
    if (g->map[y][x] == 'N')
        g->player.angle = 3 * PI / 2;
}

void    init_player(t_game *g)
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
       			g->player.x = x * TILE + TILE / 2;
                g->player.y = y * TILE + TILE / 2;
                set_direction_player(g, x, y);
			}
			x++;
		}
		y++;	
	}
	
}

void    free_up(char **s)
{
	int i;

    i = 0;
	while(s[i])
		free(s[i++]);
	free(s);
}
