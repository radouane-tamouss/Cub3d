/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:00:50 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 19:00:53 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off
void	pad_map_with_spaces_helper(t_game *game, int j, int i, int map_width)
{
	char	*line;
	int		k;

	k = 0;
	line = mallocate(sizeof(char) * (map_width + 1));
	while (game->map.grid[i][j])
	{
		line[k] = game->map.grid[i][j];
		k++;
		j++;
	}
	while (k < map_width)
	{
		line[k] = ' ';
		k++;
	}
	line[k] = '\0';
	free_ptr(game->map.grid[i]);
	game->map.grid[i] = ft_strdup(line);
	free_ptr(line);
}

void	check_invalid_map_helper(t_game *game, int i, int j)
{
	if ((i > 0 && (game->map.grid[i - 1][j] != '0' && game->map.grid[i
				- 1][j] != '1' && game->map.grid[i - 1][j] != 'D'
				&& !check_if_player_direction(game->map.grid[i - 1][j])))
		|| (i < game->map.height - 1 && (game->map.grid[i + 1][j] != '0'
				&& game->map.grid[i + 1][j] != '1' && game->map.grid[i
				+ 1][j] != 'D' && !check_if_player_direction(game->map.grid[i
					+ 1][j]))) ||
		(j > 0 && (game->map.grid[i][j - 1] != '0' && game->map.grid[i][j
				- 1] != '1' && game->map.grid[i][j - 1] != 'D'
				&& !check_if_player_direction(game->map.grid[i][j - 1])))
			|| (j < (int)ft_strlen(game->map.grid[i]) - 1
			&& (game->map.grid[i][j + 1] != '0' && game->map.grid[i][j
				+ 1] != '1' && game->map.grid[i][j + 1] != 'D'
				&& !check_if_player_direction(game->map.grid[i][j + 1]))))
	{
		if (check_if_player_direction(game->map.grid[i][j]) == 1)
			printf("invalid player direction at (%d, %d)\n", i, j);
		else if (game->map.grid[i][j] == 'D')
			printf("invalid door at (%d, %d)\n", i, j);
		else
			printf("invalid zero at (%d, %d)\n", i, j);
		exiter(1);
	}
}

void	check_invalid_spaces_helper(t_game *game, int i, int j)
{
	if (game->map.grid[i][j] == ' ')
	{
		if ((i > 0 && game->map.grid[i - 1][j] != '1' && game->map.grid[i
				- 1][j] != ' ') || (i < game->map.height - 1 && game->map.grid[i
				+ 1][j] != '1' && game->map.grid[i + 1][j] != ' ') || (j > 0
				&& game->map.grid[i][j - 1] != '1' && game->map.grid[i][j
				- 1] != ' ') || (j < (int)ft_strlen(game->map.grid[i]) - 1
				&& game->map.grid[i][j + 1] != '1' && game->map.grid[i][j
				+ 1] != ' '))
		{
			printf("Error: Invalid space found at (%d, %d)\n", i, j);
			exiter(1);
		}
	}
}

void	check_invalid_spaces(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			check_invalid_spaces_helper(game, i, j);
			j++;
		}
		i++;
	}
}

void	check_invalid_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'M' && (game->map.grid[i][j] == '0'
				|| game->map.grid[i][j] == 'D'
				|| check_if_player_direction(game->map.grid[i][j]) == 1))
			{
				check_invalid_map_helper(game, i, j);
			}
			j++;
		}
		i++;
	}
}
