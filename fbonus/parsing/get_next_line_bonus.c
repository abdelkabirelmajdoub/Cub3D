/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:23:11 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/11/13 10:12:05 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*before_newline(char *str)
{
	int		i;
	char	*n_str;

	i = 0;
	if (str[i] == '\0' || !str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	n_str = malloc(i + 1);
	if (n_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		n_str[i] = str[i];
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}

char	*after_newline(char *str)
{
	int		i;
	char	*n_str;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), str = NULL);
	if (str[i] == '\n')
		i++;
	n_str = ft_strdup(&str[i]);
	free (str);
	return (n_str);
}

char	*get_next_line(int fd)
{
	static char	*hold;
	char		*buffer;
	int			b_readed;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(hold), hold = NULL);
	buffer = malloc (BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free(hold), hold = NULL);
	b_readed = 1;
	while (b_readed > 0 && ft_strchr(hold) != 1)
	{
		b_readed = read(fd, buffer, BUFFER_SIZE);
		if (b_readed == -1)
			return (free(hold), free (buffer), buffer = NULL, hold = NULL);
		buffer[b_readed] = '\0';
		hold = ft_strjoin(hold, buffer);
	}
	free (buffer);
	line = before_newline(hold);
	hold = after_newline(hold);
	return (line);
}

// #include <fcntl.h>
// int main ()
// {
// 	int fd = open ("test", O_RDWR | O_CREAT , 0700);
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// }