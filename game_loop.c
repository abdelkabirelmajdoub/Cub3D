/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:27:04 by ael-majd          #+#    #+#             */
/*   Updated: 2025/10/30 12:05:54 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keys_press(t_game *g, float *dx, float *dy)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_M))
		g->show_map = 1;
	if (mlx_is_key_down(g->mlx, MLX_KEY_N))
		g->show_map = 0;
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		*dx += cos(g->player.angle) * SPEED;
		*dy += sin(g->player.angle) * SPEED;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		*dx -= cos(g->player.angle) * SPEED;
		*dy -= sin(g->player.angle) * SPEED;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		*dx += cos(g->player.angle + PI / 2) * SPEED;
		*dy += sin(g->player.angle + PI / 2) * SPEED;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		*dx += cos(g->player.angle - PI / 2) * SPEED;
		*dy += sin(g->player.angle - PI / 2) * SPEED;
	}
}

void	rotation_face(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		g->player.angle += ROT_SPEED;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		g->player.angle -= ROT_SPEED;
	if (g->player.mouse_locked)
	{
		mlx_get_mouse_pos(g->mlx, &g->player.mouse_x, &g->player.mouse_y);
		mlx_set_cursor_mode(g->mlx, MLX_MOUSE_DISABLED);
		g->player.angle += (g->player.mouse_x - g->player.prev_mouse_x) 
			* 0.0015;
		mlx_set_mouse_pos(g->mlx, WIDTH / 2, HEIGHT / 2);
		g->player.prev_mouse_x = WIDTH / 2;
	}
}

void	suspand_cursor(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_CONTROL))
		g->player.mouse_locked = true;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
	{
		g->player.mouse_locked = false;
		mlx_set_cursor_mode(g->mlx, MLX_MOUSE_NORMAL);
	}
}

void	check_move_rotate(t_game *g, float dx, float dy)
{
	if (g->player.angle < 0)
		g->player.angle += 2 * PI;
	if (g->player.angle > 2 * PI)
		g->player.angle -= 2 * PI;
	if (can_move(g, dx, g->player.y))
		g->player.x = dx;
	if (can_move(g, g->player.x, dy))
		g->player.y = dy;
	if (g->player.x < 0)
		g->player.x = 0.0f;
	if (g->player.y < 0)
		g->player.y = 0.0f;
}

void	game_loop(void *param)
{
	t_game	*g;
	float	dx;
	float	dy;

	g = (t_game *)param;
	dx = g->player.x;
	dy = g->player.y;
	suspand_cursor(g);
	rotation_face(g);
	keys_press(g, &dx, &dy);
	check_move_rotate(g, dx, dy);
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	mlx_delete_image(g->mlx, g->img);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g->mlx, g->img, 0, 0);
	if (g->show_map)
	{
		draw_map(g);
		draw_player(g, g->player.x, g->player.y, 0xFFFF0000);
		draw_rays(g);
	}
	else
		tree_d_render(g);
}
