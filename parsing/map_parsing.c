/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:09:09 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/09/10 12:16:01 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/yasserlotfi/studies/cursus/Cub3D/cub3d.h"

int count_chars(char *map_name)
{
	int		fd;
	int		char_num;
	int 	byte_read;
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
	buffer = malloc (count_chars(map_name));
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

// char	**convert_map(char **map)
// {
	
// }

int main ()
{

	printf("%d\n",count_line("map.cub"));
}