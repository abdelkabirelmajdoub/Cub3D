/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:07:46 by ael-majd          #+#    #+#             */
/*   Updated: 2025/11/02 13:22:02 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	darw_square(mlx_image_t *img, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			if (start_x + x < WIDTH && start_y + y < HEIGHT)
			{
				if (x < 1 || y < 1)
					mlx_put_pixel(img, start_x + x, start_y + y , 0xB22222FF);
				else
					mlx_put_pixel(img, start_x + x, start_y + y, color);	
			}
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *g, float cx, float cy, int color)
{
	int	x;
	int	y;
    int start_x;
    int start_y;

	start_x = (int)(cx - SIZE_P / 2);
	start_y = (int)(cy - SIZE_P / 2);
	y = 0;
    while (y < SIZE_P)
    {
		x = 0;
        while (x < SIZE_P)
        {
            if (start_x + x >= 0 && start_x + x < WIDTH && start_y + y >= 0 && start_y + y < HEIGHT)
                mlx_put_pixel(g->img, start_x + x, start_y + y, color);
			x++;
        }
		y++;
    }
}

void	draw_map(t_game *g)
{
	int x;
	int y;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == '1')
				darw_square(g->img,  x * TILE,  y * TILE, 0x0000FFFF);
			else
				darw_square(g->img,  x * TILE,  y * TILE, 0xCCCCCCFF);
			x++;
		}
		y++;
	}
}

void	draw_one_ray(t_game *g, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;

	ray_x = g->player.x;
	ray_y = g->player.y;
	step_x = cosf(ray_angle);
	step_y = sinf(ray_angle);
	while (!touch(g, ray_x, ray_y))
	{
		if (ray_x >= 0 && ray_x < WIDTH && ray_y >= 0 && ray_y < HEIGHT)
			mlx_put_pixel(g->img, ray_x, ray_y, 0xFF0000FF);
		ray_x += step_x;
		ray_y += step_y;
	}
}

void draw_rays(t_game *g)
{
	float ray_angle;
	int i = 0;

	while (i < WIDTH)
	{
		ray_angle = g->player.angle - (FOV / 2) + i * (FOV / WIDTH);
		draw_one_ray(g, ray_angle);
		i++;
	}
}
