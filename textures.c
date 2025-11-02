/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:39:24 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/11/01 13:06:09 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_init(t_game *g)
{
g->tex_no = mlx_load_png("./textures/no.png");
g->tex_so = mlx_load_png("./textures/so.png");
g->tex_ea = mlx_load_png("./textures/ea.png");
g->tex_we = mlx_load_png("./textures/we.png");
if (!g->tex_no || !g->tex_so || !g->tex_ea || !g->tex_we)
{
    printf("Failed to load texture\n");
    exit(1);
}
}

uint32_t get_tex_color(mlx_texture_t *tex, int x, int y)
{
    int i = (y * tex->width + x) * 4;
    return (tex->pixels[i + 0] << 24 |
            tex->pixels[i + 1] << 16 |
            tex->pixels[i + 2] << 8  |
            tex->pixels[i + 3]);
}
