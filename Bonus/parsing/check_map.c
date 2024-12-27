/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:55:02 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 17:55:23 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off

void	pad_map_with_spaces(t_game *game)
{
	int		i;
	int		j;
	int		map_width;

	i = 0;
	j = 0;
	map_width = calc_map_width(game->map.grid);
	game->map.width = map_width;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		if ((int)ft_strlen(game->map.grid[i]) < map_width)
			pad_map_with_spaces_helper(game, j, i, map_width);
		i++;
	}
}

t_game	init_game_struct(void)
{
	t_game	game;

	game.north.path = NULL;
	game.south.path = NULL;
	game.west.path = NULL;
	game.east.path = NULL;
	game.floor.color = NULL;
	game.ceiling.color = NULL;
	return (game);
}

char	**init_map(int fd, char *file, t_map *m2)
{
	char	**map;
	char	*line;

	m2->width = 0;
	m2->height = 0;
	m2->valid = 0;
	line = NULL;
	m2->height = calc_height(fd, file, m2, line);
	map = mallocate(sizeof(char *) * (m2->height + 1));
	if (!map)
	{
		printf("Error\n Malloc failed\n");
		exiter(1);
	}
	fill_map(map, file, line);
	return (map);
}

void	check_map_helper(char **map, t_game *game, t_map m2)
{
	int	i;
	int	map_height;
	int	map_width;
	int	j;

	i = 0;
	while (i < 6)
		parse_texture_and_colors_info(map[i++], game, &m2);
	map_height = 0;
	while (map[map_height] != NULL)
		map_height++;
	map_height = map_height - 6;
	game->map.height = map_height;
	j = 0;
	game->map.grid = mallocate(sizeof(char *) * (map_height + 1));
	while (j < map_height)
	{
		game->map.grid[j] = ft_strdup(map[j + 6]);
		j++;
	}
	game->map.grid[j] = NULL;
	map_width = calc_map_width(game->map.grid);
	map_height = calc_map_height(game->map.grid);
}

t_game	check_map(int fd, char *file)
{
	t_map	m2;
	t_game	game;
	char	**map;

	game = init_game_struct();
	map = init_map(fd, file, &m2);
	check_map_helper(map, &game, m2);
	check_if_map_contains_only_valid_characters(&game);
	check_map_sourrounded_by_walls(&game);
	pad_map_with_spaces(&game);
	check_invalid_map(&game);
	verify_player_starting_position(&game);
	check_invalid_spaces(&game);
	get_player_position(&game);
	return (game);
}
