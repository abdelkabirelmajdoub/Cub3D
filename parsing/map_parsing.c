/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:09:09 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/10/16 14:00:19 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_chars(char *map_name)
{
	int		fd;
	int		char_num;
	int		byte_read;
	char	buffer[1024];

	fd = open (map_name, O_RDONLY);
	if (fd < 0)
		return (0);
	byte_read = 1;
	char_num = 0;
	while (byte_read >= 1)
	{
		byte_read = read (fd, buffer, 1);
		char_num += byte_read;
	}
	close (fd);
	return (char_num);
}

int	count_line(char *map_name)
{
	int		fd;
	int		i;
	int		x;
	char	*buffer;
	int		byte_read;	

	i = 0;
	x = 1;
	fd = open (map_name, O_RDONLY);
	buffer = malloc (count_chars(map_name) + 1);
	if (!buffer)
		return (0);
	byte_read = read(fd, buffer, count_chars(map_name));
	if (byte_read <= 0)
		return (free(buffer), buffer = NULL, 0);
	buffer[byte_read] = '\0';
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n' && buffer[i + 1] != '\0')
			x += 1;
		i++;
	}
	free (buffer);
	buffer = NULL;
	return (close (fd), x);
}

int map_start(char *map_name)
{
	int fd;
	int line_num;
	char *line;
	int j;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return -1;
	line_num = 0;
	while ((line = get_next_line(fd)))
	{
		j = 0;
		while (line[j] == ' ' || (line[j] >= 9 && line[j] <= 13))
			j++;
		if (line[j] == '1' || line[j] == '0')
		{
			free(line);
			close(fd);
			return line_num;
		}
		free(line);
		line_num++;
	}
	close(fd);
	return -1;
}

char	**convert_map(char *map_name, int start)
{
	int		i;
	int		j;
	char	*line;
	int		fd;
	char	**array;

	array = malloc (count_line(map_name) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	fd = open (map_name, O_RDONLY);
	while (j <= start + 1)
	{
		line = get_next_line(fd);
		if (line != NULL)
			free(line);
		j++;
	}
	while (i < count_line(map_name))
	{
		array[i] = get_next_line(fd);
		i++;
	}
	return (array);
}

int	map_pars(char **map, int map_lines, t_player *player_pos)
{
	if (surrounded_bywalls(map, map_lines) != 1
		|| player_check(map, map_lines) != 1
		|| map_content(map, map_lines) != 1
		|| space_check(map, map_lines) != 1)
		return (0);
	get_playerpos(map, map_lines, player_pos);
	return (1);
}
