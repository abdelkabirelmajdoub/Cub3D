/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserlotfi <yasserlotfi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:30:25 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/11/06 11:37:36 by yasserlotfi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int        map_name_check (char *map_name)
{
    if (ft_strlen(map_name) <= 4
        || map_name[ft_strlen(map_name) - 1] != 'b'
        || map_name[ft_strlen(map_name) - 2] != 'u'
        || map_name[ft_strlen(map_name) - 3] != 'c'
        || map_name[ft_strlen(map_name) - 4] != '.'
        || map_name[ft_strlen(map_name) - 5] == '/')
        return (0);
    return (1);
}

char    **main_helper(char *map_name, t_player *player_pos, t_textures *paths, t_game *game)
{
    char	**map;
    int		fd;
    int		map_lines;
    int		map_s;
    int		x; 

    if (map_name_check(map_name) == 0)
        return (NULL);
    fd = open(map_name, O_RDONLY);
    paths = malloc(sizeof(t_textures));
    if (!paths)
        return (free(player_pos), NULL);
    map_s = map_start(map_name);
    map = convert_map(map_name, map_s);
    x = get_paths(paths, fd, map_s);
    map_lines = 0;
    while (map[map_lines])
        map_lines++;
    if (map_pars(map, map_lines, player_pos) == 0
        || path_check(paths, game) == 0
		|| x == 0)
        return (NULL);
    return (map);
}

void	tree_d_render(t_game *g)
{
	float	start_angle;
	int		i;

	i = 0;
	start_angle = g->player.angle - FOV / 2;
	while (i < WIDTH)
	{
		start_angle += FOV / WIDTH;
		draw_line(g, start_angle, i);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_game		game;
    t_textures  paths;

	if (ac != 2)
	{
		perror("Wrong Number of args!");
		return (1);
	}
	game.map = main_helper(av[1], &game.player, &paths, &game);
	if (!game.map)
	{
		perror("Fix your map/paths");
		return (1);
	}
    texture_init(&game);
	init_game(&game);
	init_player(&game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	free_up(game.map);
	mlx_terminate(game.mlx);
}
