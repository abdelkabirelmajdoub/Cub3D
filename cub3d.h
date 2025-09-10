/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:23:51 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/09/10 11:55:39 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

/* ***********************************************get_next_line*******************************************/
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 45
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);
int		ft_strchr(char *str);
int		ft_strlen(char *str);
char	*after_newline(char *str);
char	*before_newline(char *str);
#endif
/* ***********************************************get_next_line*******************************************/

/* ***********************************************parsing*************************************************/