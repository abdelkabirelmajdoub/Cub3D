/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:30:25 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/10/30 11:47:11 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**main_helper(char *map_name, t_player *player_pos)
{
	char		**map;
	t_textures	*paths;
	int			fd;
	int			map_lines;
	int			map_s;

	fd = open(map_name, O_RDONLY);
	paths = malloc(sizeof(t_textures));
	if (!paths)
		return (free(player_pos), NULL);
	map_s = map_start(map_name);
	map = convert_map(map_name, map_s);
	get_paths(paths, fd, map_s);
	map_lines = 0;
	while (map[map_lines])
		map_lines++;
	if (map_pars(map, map_lines, player_pos) == 0
		|| path_check(paths) == 0)
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

	if (ac != 2)
	{
		perror("Wrong Number of args!");
		return (1);
	}
	game.map = main_helper(av[1], &game.player);
	if (!game.map)
	{
		perror("Fix your map/paths");
		return (1);
	}
	init_game(&game);
	init_player(&game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	free_up(game.map);
	mlx_terminate(game.mlx);
}
