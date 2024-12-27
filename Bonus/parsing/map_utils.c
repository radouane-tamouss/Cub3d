/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:33:51 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 21:34:01 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("[%s]\n", map[i]);
		i++;
	}
}

void	check_if_map_contains_only_valid_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		game->map.grid[i] = ft_strtrim(game->map.grid[i], "\n");
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] != 'M' && game->map.grid[i][j] != 'D' &&
				game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1' &&
				game->map.grid[i][j] != 'N' && game->map.grid[i][j] != 'S' &&
				game->map.grid[i][j] != 'E' && game->map.grid[i][j] != 'W' &&
				game->map.grid[i][j] != ' ')
			{
				printf("Error: Invalid character in map\n");
				exiter(1);
			}
			j++;
		}
		i++;
	}
}

void	check_map_sourrounded_by_walls(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		if (game->map.grid[i][0] == '\0')
			(printf("Error: Empty line in map\n"), exiter(1));
		while (game->map.grid[i][j])
		{
			if (i == 0 || i == game->map.height - 1 || j == 0
				|| j == (int)(ft_strlen(game->map.grid[i])) - 1)
			{
				if (game->map.grid[i][j] != '1' && game->map.grid[i][j] != ' ')
				{
					printf("Error: Map is not surrounded by walls\n");
					exiter(1);
				}
			}
			j++;
		}
		i++;
	}
}

int	calc_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	calc_map_width(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (map[i] != NULL)
	{
		j = 0;
		if (check_line_empty(map[i]) != 1)
			map[i] = ft_strtrim_last(map[i], " ");
		while (map[i][j])
		{
			j++;
		}
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}
