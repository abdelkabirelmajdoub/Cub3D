/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:39:30 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/11/06 11:40:20 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		if (map[i][0] == '\n' || map[i][0] == '\0')
    		return (0);
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
		while (map[i][j] && map[i][j] != '\0')
		{
			if (map[i][j] == ' ')
			{
				if (i > 0 && map[i - 1][j] != '1' && map[i - 1][j] != ' ' && map[i - 1][j] != '\0')
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
	int	i;
	int	j;

	i = 0;
	while (i < line)
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if ((i > 0 &&  map[i - 1][j] == ' '))
					return (0);
				if (i == line - 1 || map[i + 1][j] == ' ' || map[i + 1][j] == '\0')
					return (0);
				if (j == 0 || map[i][j - 1] == ' ')
					return (0);
				if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
					return (0);
			}
			j++;
		}
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
				player_pos->x = i;
				player_pos->y = j;
			}
			j++;
		}
		i++;
	}
}
