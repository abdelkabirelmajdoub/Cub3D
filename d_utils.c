/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:30:02 by ael-majd          #+#    #+#             */
/*   Updated: 2025/11/12 11:21:33 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_perp_sides(t_dda *p, t_game *g, float ray_angle)
{
	if (p->side == 0)
	{
		if (p->ray_x > 0)
			p->tex = g->ea;
		else
			p->tex = g->we;
	}
	else
	{
		if (p->ray_y > 0)
			p->tex = g->so;
		else
			p->tex = g->no;
	}
	if (!p->side)
		p->dist = p->side_x - p->delta_x;
	else
		p->dist = p->side_y - p->delta_y;
	p->perp_wall = p->dist * cosf(ray_angle - g->player.angle);
	if (p->perp_wall <= 0.0001f)
		p->perp_wall = 0.0001f;
}

void	dda_loop(t_dda *p, t_game *g, float ray_angle)
{
	while (!p->hit)
	{
		if (p->side_x < p->side_y)
		{
			p->side_x += p->delta_x;
			p->map_x += p->step_x;
			p->side = 0;
		}
		else
		{
			p->side_y += p->delta_y;
			p->map_y += p->step_y;
			p->side = 1;
		}
		if (p->map_x < 0 || p->map_y < 0)
		{
			p->hit = 1;
			break ;
		}
		if (g->map[p->map_y][p->map_x] == '1')
			p->hit = 1;
	}
	set_perp_sides(p, g, ray_angle);
}

void	ceill_draw(t_game *g, int start_draw, int i)
{
	int	j;

	j = 0;
	while (j < start_draw)
	{
		mlx_put_pixel(g->img, i, j, g->ceil_color);
		j++;
	}
}

void	floor_draw(t_game *g, int end_draw, int i)
{
	while (end_draw < g->height)
	{
		mlx_put_pixel(g->img, i, end_draw, g->floor_color);
		end_draw++;
	}
}
