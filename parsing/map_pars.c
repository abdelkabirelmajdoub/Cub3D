/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:39:30 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/09/18 09:28:40 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/yasserlotfi/studies/cursus/Cub3D/cub3d.h"

int	player_check(char **map, int line)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (i < line)
	{
		j = 0;
		while (map[i][j] != '\0' && map[i][j] != '\n')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				p += 1;
			j++;
		}
		i++;
	}
	if (p != 1)
	{
		perror("The problem is with Player");
		return (0);
	}
	return (1);
}

int	map_content(char **map, int line)
{
	int	i;
	int	j;

	i = 0;
	while (i < line)
	{
		j = 0;
		while (map[i][j] != '\0' && map[i][j] != '\n')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
			{
				perror("The problem is with map content");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	space_check(char **map, int line)
{
	int	i;
	int	j;

	i = 0;
	while (i < line)
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == ' ')
			{
				if (i > 0 && map[i - 1][j] != '1' && map[i - 1][j] != ' ' && map[i - 1][j] != '\0')
					return (0);
				if (i < line - 1 && map[i + 1][j] != '1' && map[i + 1][j] != ' ' && map[i + 1][j] != '\0')
					return (0);
				if (j > 0 && map[i][j - 1] != '1' && map[i][j - 1] != ' ')
					return (0);
				if (map[i][j + 1] != '\0' && map[i][j + 1] != '1' && map[i][j + 1] != ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	surrounded_bywalls(char **map, int line)
{
	static int	i;

	while (map[0][i] != '\n')
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (map[line - 1][i] != '\0')
	{
		if (map[line - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < line)
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 2] != '1')
			return (0);
		if (ft_strlen(map[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	get_playerpos(char **map, int line, t_player	*player_pos)
{
	int		i;
	int		j;

	i = 0;
	while (i < line)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				player_pos->player_row = i;
				player_pos->player_col = j;
			}
			j++;
		}
		i++;
	}
}
