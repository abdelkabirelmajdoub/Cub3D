/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:54:49 by ael-majd          #+#    #+#             */
/*   Updated: 2025/11/09 10:55:03 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	texture_init(t_game *g, t_textures *paths)
{
	g->no = mlx_load_png(paths->no_path);
	g->so = mlx_load_png(paths->so_path);
	g->ea = mlx_load_png(paths->ea_path);
	g->we = mlx_load_png(paths->we_path);
	if (!g->no || !g->so || !g->ea || !g->we)
	{
		printf("Failed to load texture\n");
		exit(1);
	}
}

uint32_t	get_tex_color(mlx_texture_t *tex, int x, int y)
{
	int	i;

	i = (y * tex->width + x) * 4;
	return (tex->pixels[i + 0] << 24
		| tex->pixels[i + 1] << 16
		| tex->pixels[i + 2] << 8 
		| tex->pixels[i + 3]);
}

void	init_paths(t_textures *path, t_game *g)
{
	path->ceiling_color = NULL;
	path->floor_color = NULL;
	path->ea_path = NULL;
	path->we_path = NULL;
	path->so_path = NULL;
	path->no_path = NULL;
	g->ea = NULL;
	g->we = NULL;
	g->so = NULL;
	g->no = NULL;
}
