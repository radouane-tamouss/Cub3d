/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:36:10 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 21:36:14 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
int	has_wall_at(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = round(x);
	map_y = round(y);
	if (map_x < 0 || map_x >= game->map.height || map_y < 0
		|| map_y >= game->map.width)
		return (1);
	if (game->map.grid[map_x][map_y] == '1')
		return (1);
	return (0);
}

size_t	calc_height(int fd, char *file, t_map *m2, char *line)
{
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	m2->height++;
	while (line)
	{
		free_ptr(line);
		line = get_next_line(fd);
		m2->height++;
	}
	close(fd);
	return (m2->height);
}

void	fill_map_helper(int fd, char *line, char **map, int *i)
{
	int	filled_lines;

	filled_lines = 0;
	while (line)
	{
		if (filled_lines <= 6 && (ft_strcmp(line, "") == 0
				|| check_line_empty(line) == 1))
		{
			free_ptr(line);
			line = get_next_line(fd);
			continue ;
		}
		map[*i] = line;
		line = get_next_line(fd);
		filled_lines++;
		(*i)++;
	}
}

void	fill_map(char **map, char *file, char *line)
{
	int	fd;
	int	i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	line = get_next_line(fd);
	i = 0;
	fill_map_helper(fd, line, map, &i);
	while (i > 0 && (ft_strcmp(map[i - 1], "") == 0
			|| check_line_empty(map[i - 1]) == 1))
	{
		free_ptr(map[i - 1]);
		i--;
	}
	map[i] = NULL;
	close(fd);
}
