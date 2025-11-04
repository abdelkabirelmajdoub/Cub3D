/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:40:59 by ael-majd          #+#    #+#             */
/*   Updated: 2025/11/04 14:33:46 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_calcul(t_dda *p, t_game *g, float ray_angle)
{
	p->x_tile = g->player.x / TILE;
	p->y_tile = g->player.y / TILE;
	p->map_x = (int)p->x_tile;
	p->map_y = (int)p->y_tile;
	p->ray_x = cos(ray_angle);
	p->ray_y = sin(ray_angle);
	p->hit = 0;
	if (!p->ray_x)
		p->delta_x = 1e30f;
	else
		p->delta_x = fabs(1.0f / p->ray_x);
	if (!p->ray_y)
		p->delta_y = 1e30f;
	else
		p->delta_y = fabs(1.0f / p->ray_y);
}

void	sides_init(t_dda *p)
{
	if (p->ray_x < 0)
	{
		p->step_x = -1;
		p->side_x = (p->x_tile - p-> map_x) * p->delta_x;
	}
	else
	{
		p->step_x = 1;
		p->side_x = (p->map_x + 1.0f - p->x_tile) * p->delta_x;
	}
	if (p->ray_y < 0)
	{
		p->step_y = -1;
		p->side_y = (p->y_tile - p->map_y) * p->delta_y;
	}
	else
	{
		p->step_y = 1;
		p->side_y = (p->map_y + 1.0f - p->y_tile) * p->delta_y;
	}
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
			break;
		}
		if (g->map[p->map_y][p->map_x] == '1')
			p->hit = 1;
	}
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
		p->perp_wall = p->side_x - p->delta_x;
	else
		p->perp_wall = p->side_y - p->delta_y;
	p->perp_wall = p->perp_wall * cosf(ray_angle - g->player.angle);
	if (p->perp_wall <= 0.0001f)
		p->perp_wall = 0.0001f;
}


void	draw_line(t_game *g, float ray_angle, int i)
{
	t_dda	p;
	int		line_height;
	int		start_draw;
	int		end_draw;

	
	set_calcul(&p, g, ray_angle);
	sides_init(&p);
	dda_loop(&p, g, ray_angle);
	if (p.side == 0)
		p.wall_x = g->player.y / TILE + p.perp_wall * p.ray_y;
	else
		p.wall_x = g->player.x / TILE + p.perp_wall * p.ray_x;
	p.wall_x -= (int)p.wall_x;
	if (p.wall_x < 0.0f)
		p.wall_x += 1.0f;
	
	p.tex_x = (int)(p.wall_x * (float)p.tex->width);
	if (p.side == 0 && p.ray_x < 0)
		p.tex_x = p.tex->width - p.tex_x - 1;
	if (p.side == 1 && p.ray_y > 0)
		p.tex_x = p.tex->width - p.tex_x - 1;
	
	if (p.tex_x < 0)
		p.tex_x = 0;
	if (p.tex_x >= (int)p.tex->width)
		p.tex_x = p.tex->width - 1;
	
	line_height = (int)(HEIGHT / p.perp_wall);
	start_draw = -line_height / 2 + HEIGHT / 2;
	if (start_draw < 0)
		start_draw = 0;
	end_draw = line_height / 2 + HEIGHT / 2;
	if (end_draw > HEIGHT)
		end_draw = HEIGHT;
	int j = 0;
	while(j < start_draw)
	{
		mlx_put_pixel(g->img, i, j, g->ceil_color);
		j++;
	}
	p.step = (float)p.tex->height / (float)line_height;
	p.tex_pos_y = (start_draw - HEIGHT / 2 + line_height / 2) * p.step;
	while (start_draw < end_draw)
	{
		if (p.tex_pos_y < 0)
			p.tex_pos_y = 0;
		if (p.tex_pos_y >= (int)p.tex->height)
			p.tex_pos_y = p.tex->height - 1;
		p.color = get_tex_color(p.tex, p.tex_x, p.tex_pos_y);
		mlx_put_pixel(g->img, i, start_draw, p.color);
		p.tex_pos_y += p.step;
		start_draw++;
	}
	while(end_draw < HEIGHT)
	{
		mlx_put_pixel(g->img, i, end_draw, g->floor_color);
		end_draw++;
	}
}
