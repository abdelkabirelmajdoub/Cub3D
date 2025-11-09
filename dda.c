/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:40:59 by ael-majd          #+#    #+#             */
/*   Updated: 2025/11/09 10:44:10 by ael-majd         ###   ########.fr       */
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

void	x_tex(t_dda *p)
{
	if (p->side == 0)
		p->wall_x = p->y_tile + p->dist * p->ray_y;
	else
		p->wall_x = p->x_tile + p->dist * p->ray_x;
	p->wall_x -= (int)p->wall_x;
	if (p->wall_x < 0.0f)
		p->wall_x += 1.0f;
	p->tex_x = (int)(p->wall_x * (float)p->tex->width);
	if (p->side == 0 && p->ray_x < 0)
		p->tex_x = p->tex->width - p->tex_x - 1;
	if (p->side == 1 && p->ray_y > 0)
		p->tex_x = p->tex->width - p->tex_x - 1;
	if (p->tex_x < 0)
		p->tex_x = 0;
	if (p->tex_x >= (int)p->tex->width)
		p->tex_x = p->tex->width - 1;
}

void	start_end(t_dda *p, int *line_height, int *start_draw, int *end_draw)
{
	*line_height = (int)(HEIGHT / p->perp_wall);
	*start_draw = -*line_height / 2 + HEIGHT / 2;
	if (*start_draw < 0)
		*start_draw = 0;
	*end_draw = *line_height / 2 + HEIGHT / 2;
	if (*end_draw > HEIGHT)
		*end_draw = HEIGHT;
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
	x_tex(&p);
	start_end(&p, &line_height, &start_draw, &end_draw);
	ceill_draw(g, start_draw, i);
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
	floor_draw(g, end_draw, i);
}
