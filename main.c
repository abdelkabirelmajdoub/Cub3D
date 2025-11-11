/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:30:25 by yasserlotfi       #+#    #+#             */
/*   Updated: 2025/11/11 12:18:50 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_name_check (char *map_name)
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

char	**main_helper(char *map_name, t_player *player_pos, t_textures *paths, t_game *game)
{
	char	**map;
	int		fd;
	int		map_lines;
	int		map_s;
	int		x; 

	if (map_name_check(map_name) == 0)
		return (NULL);
	fd = open(map_name, O_RDONLY);
	map_s = map_start(map_name);
	map = convert_map(map_name, map_s);
	if (!map || !*map)
		return (NULL);
	x = get_paths(paths, fd, map_s);
	map_lines = 0;
	while (map[map_lines])
		map_lines++;
	if (map_pars(map, map_lines, player_pos) == 0
		|| path_check(paths, game) == 0
		|| x == 0)
		return (free_up(map), NULL);
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

void	init_paths(t_textures *path, t_game *g)
{
	path->ceiling_color = NULL;
	path->floor_color = NULL;
	path->ea_path = NULL;
	path->we_path = NULL;
	path->so_path = NULL;
	path->no_path = NULL;
	g->ea = NULL;
	g->we = NULL;
	g->so = NULL;
	g->no = NULL;
}
void ll(){system("leaks -q cub3D");}
int	main(int ac, char **av)
{
	t_game		game;
	t_textures  *paths;
atexit(ll);
	if (ac != 2)
	{
		perror("Error\nWrong Number of args!");
		return (1);
	}
	paths = malloc(sizeof(t_textures));
	if (!paths)
		return (0);
	init_paths(paths, &game);
	game.map = main_helper(av[1], &game.player, paths, &game);
	if (!game.map)
		return (free_path(paths, &game), perror("Error\nFix your map/paths"), 1);
	texture_init(&game, paths);
	init_game(&game);
	init_player(&game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_up(game.map);
	free_path(paths, &game);
}
