/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:23:30 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/10/12 12:06:29 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*n_str;

	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	n_str = malloc(ft_strlen(s1) + ft_strlen(s2)+ 1);
	if (n_str == NULL)
		return (free(s1), s1 = NULL);
	while (s1[i] != '\0')
	{
		n_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		n_str[i + j] = s2[j];
		j++;
	}
	n_str[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (n_str);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*n_str;
	int		s_len;

	i = 0;
	s_len = ft_strlen(str);
	n_str = malloc (s_len + 1);
	if (n_str == NULL)
		return (free(str), str = NULL);
	while (str[i] != '\0')
	{
		n_str[i] = str[i];
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}

int	ft_strchr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
