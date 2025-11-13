/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:07:46 by ael-majd          #+#    #+#             */
/*   Updated: 2025/11/13 10:12:05 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_square(t_game *g, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	if (!g->img)
		return ;
	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			if (start_x + x >= 0 && start_x + x < (int)g->img->width
				&& start_y + y >= 0 && start_y + y < (int)g->img->height)
			{
				if (x < 1 || y < 1)
					mlx_put_pixel(g->img, start_x + x, start_y + y, 0xFFFFFFFF);
				else
					mlx_put_pixel(g->img, start_x + x, start_y + y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_ray(t_game *g, int start_x, int start_y)
{
	int	len;
	int	i;
	int	x;
	int	y;

	len = TILE * 2;
	i = 0;
	while (i < len)
	{
		x = start_x + cosf(g->player.angle) * i;
		y = start_y + sinf(g->player.angle) * i;
		if (x >= 0 && x < MINI_SIZE && y >= 0 && y < MINI_SIZE)
			mlx_put_pixel(g->img, x + TILE / 2, y + TILE / 2, 0xFF0000FF);
		i++;
	}
}

void	draw_player(t_game *g, int color)
{
	int	fixed_cord;
	int	x;
	int	y;

	draw_ray(g, MINI_SIZE / 2, MINI_SIZE / 2);
	fixed_cord = MINI_SIZE / 2 - SIZE_P / 2;
	y = 0;
	while (y < SIZE_P)
	{
		x = 0;
		while (x < SIZE_P)
		{
			mlx_put_pixel(g->img, fixed_cord + x + TILE / 2, 
				fixed_cord + y + TILE / 2, color);
			x++;
		}
		y++;
	}
}

void	init_minimap(t_minimap *m, t_game *g)
{
	m->visible = 5;
	m->p_map_x = (int)(g->player.x / TILE);
	m->p_map_y = (int)(g->player.y / TILE);
}

void	draw_map(t_game *g)
{
	t_minimap	m;
	int			x;
	int			y;

	init_minimap(&m, g);
	y = m.p_map_y - m.visible;
	while (y <= m.p_map_y + m.visible)
	{
		x = m.p_map_x - m.visible;
		while (x <= m.p_map_x + m.visible)
		{
			m.draw_x = (x - m.p_map_x + m.visible) * TILE;
			m.draw_y = (y - m.p_map_y + m.visible) * TILE;
			if (x < 0 || y < 0 || x >= ft_strlen(g->map[y])
				|| y >= g->map_height)
				draw_square(g, m.draw_x, m.draw_y, 0x0);
			else if (g->map[y][x] == '1')
				draw_square(g, m.draw_x, m.draw_y, 0x0000FFFF);
			else
				draw_square(g, m.draw_x, m.draw_y, 0xCCCCCCFF);
			x++;
		}
		y++;
	}
	draw_player(g, 0xFF0000FF);
}
