/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:24:03 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/11/13 10:12:05 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	validate_help(char *str)
{
	int	i;
	int	x;

	if (!str)
		return (0);
	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == ',')
			x++;
		i++;
	}
	if (x == 2)
		return (1);
	return (0);
}

int	validate_color(char *str, int *color)
{
	int			r;
	int			g;
	int			b;
	char		**numbers;

	if (validate_help(str) == 0)
		return (0);
	numbers = ft_split(str, ',');
	if (numbers == NULL)
		return (0);
	r = ft_atoi(numbers[0]);
	g = ft_atoi(numbers[1]);
	b = ft_atoi(numbers[2]);
	*color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free (numbers[0]);
		free (numbers[1]);
		free (numbers[2]);
		free (numbers);
		return (0);
	}
	free (numbers[0]);
	return (free (numbers[1]), free (numbers[2]), free (numbers), 1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != ' ')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_path(t_textures *path, t_game *g)
{
	if (g->ea)
		mlx_delete_texture(g->ea);
	if (g->we)
		mlx_delete_texture(g->we);
	if (g->so)
		mlx_delete_texture(g->so);
	if (g->no)
		mlx_delete_texture(g->no);
	if (path->floor_color)
		free(path->floor_color);
	if (path->ceiling_color)
		free(path->ceiling_color);
	if (path->ea_path)
		free(path->ea_path);
	if (path->we_path)
		free(path->we_path);
	if (path->so_path)
		free(path->so_path);
	if (path->no_path)
		free(path->no_path);
	if (path)
		free(path);
}
