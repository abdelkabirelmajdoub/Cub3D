/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:39:24 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/11/03 13:43:00 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_init(t_game *g)
{
    g->no = mlx_load_png("./textures/no.png");
    g->so = mlx_load_png("./textures/so.png");
    g->ea = mlx_load_png("./textures/ea.png");
    g->we = mlx_load_png("./textures/we.png");
    if (!g->no || !g->so || !g->ea || !g->we)
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
