/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:56:16 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/11/11 11:26:08 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <string.h>
#include <stdlib.h>

char	*trim_newline(char *str)
{
	char	*new_str;
	int		len;

	if (!str)
		return (NULL);
	len = strlen(str);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, str);
	if (len > 0 && new_str[len - 1] == '\n')
		new_str[len - 1] = '\0';
	return (new_str);
}

void	get_paths_helper(t_textures *paths, char *value, int j)
{
	int	i;

	i = -1;
	if (value[j] == 'N' || value[j] == 'S' || value[j] == 'W'
		|| value[j] == 'E')
		i = 2;
	else if (value[j] == 'F' || value[j] == 'C')
		i = 1;
	while (value[i] == 32 || (value[i] >= 9 && value[i] <= 13))
		i++;
	if (value[j] == 'N')
		paths->no_path = trim_newline(&value[i]);
	else if (value[j] == 'S')
		paths->so_path = trim_newline(&value[i]);
	else if (value[j] == 'W')
		paths->we_path = trim_newline(&value[i]);
	else if (value[j] == 'E')
		paths->ea_path = trim_newline(&value[i]);
	else if (value[j] == 'F')
		paths->floor_color = trim_newline(&value[i]);
	else if (value[j] == 'C')
		paths->ceiling_color = trim_newline(&value[i]);
}

int	get_paths(t_textures *paths, int fd, int line)
{
	int		i;
	int		j;
	int		x;	
	char	*value;

	i = 0;
	x = 0;
	while (i < line)
	{
		j = 0;
		value = get_next_line(fd);
		while (value[j] == 32 || (value[j] >= 9 && value[j] <= 13))
			j++;
		if (value[j] == 'N' || value[j] == 'S' || value[j] == 'W'
			|| value[j] == 'E' || value[j] == 'F' || value[j] == 'C')
		{
			get_paths_helper(paths, value, j);
			x++;
		}
		free (value);
		i++;
	}
	if (x != 6)
		return (0);
	return (1);
}

int	path_check(t_textures	*paths, t_game *game)
{
	int	fd_no;
	int	fd_so;
	int	fd_we;
	int	fd_ea;

	fd_no = open(paths->no_path, O_RDONLY);
	fd_so = open(paths->so_path, O_RDONLY);
	fd_we = open(paths->we_path, O_RDONLY);
	fd_ea = open(paths->ea_path, O_RDONLY);
	if (fd_no == -1 || fd_so == -1 || fd_we == -1 || fd_ea == -1
		|| validate_color(paths->floor_color, &game->floor_color) == 0
		|| validate_color(paths->ceiling_color, &game->ceil_color) == 0)
	{
		if (fd_no != -1)
			close(fd_no);
		if (fd_so != -1)
			close(fd_so);
		if (fd_we != -1)
			close(fd_we);
		if (fd_ea != -1)
			close(fd_ea);
		return (0);
	}
	return (close(fd_no), close(fd_so), close(fd_we), close(fd_ea), 1);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned long long	r;

	i = 0;
	s = 1;
	r = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' )
	{
		if (r >= 922337203685477580 && str[i] - '0' > 7 && s == 1)
			return (-1);
		if (r >= 922337203685477580 && str[i] - '0' > 8 && s == -1)
			return (0);
		r = r * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (r * s);
}
