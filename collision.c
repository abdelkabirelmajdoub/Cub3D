/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:29:10 by ael-majd          #+#    #+#             */
/*   Updated: 2025/10/30 11:53:53 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	can_move(t_game *g, float new_x, float new_y)
{
	float	half;
	int		left;
	int		right;
	int		top;
	int		bottom;

	half = SIZE_P / 2.0f;
	left = (new_x - half) / TILE;
	right = (new_x + half) / TILE;
	top = (new_y - half) / TILE;
	bottom = (new_y + half) / TILE;
	if (g->map[top][left] == '1')
		return (false);
	if (g->map[top][right] == '1')
		return (false);
	if (g->map[bottom][left] == '1')
		return (false);
	if (g->map[bottom][right] == '1')
		return (false);
	return (true);
}

bool	touch(t_game *g, float px, float py)
{
	int	x;
	int	y;

	x = (int)(px / TILE);
	y = (int)(py / TILE);
	if (x < 0 || y < 0)
		return (true);
	if (!g->map[y])
		return (true);
	if (!g->map[y][x])
		return (true);
	if (g->map[y][x] == '1')
		return (true);
	return (false);
}
