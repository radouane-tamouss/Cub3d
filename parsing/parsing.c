/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:00:39 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/18 22:00:39 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	check_file(char *str, int *fd)
{
	char	*res;
	ssize_t	bytes_read;
	char	buff[5];

	if (str == NULL)
		return (0);
	res = ft_strrchr(str, '.');
	if (res == NULL || ft_strcmp(res, ".cub") != 0 || ft_strlen(str) <= 4)
		return ((printf("invalid file\n"), 0));
	*fd = open(str, O_RDONLY);
	if (*fd < 0)
		return (printf("Open failed\n"), 0);
	bytes_read = read(*fd, &buff, 1);
	if (bytes_read == 0)
		return (printf("File is empty\n"), 0);
	else if (bytes_read < 0)
		return (printf("Read failed\n"), 0);
	return (1);
}

// int parse_texture_info(char *line, t_game *game)
// {

// }

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

int	check_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (check_charset(" \t\r\n\v\f", line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	fill_map(char **map, char *file, char *line)
{
	int	fd;
	int	i;
	int	filled_lines;

	fd = open(file, O_RDONLY);
	filled_lines = 0;
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (filled_lines <= 6
			&& (ft_strcmp(line, "") == 0 || check_line_empty(line) == 1))
		{
			free_ptr(line);
			line = get_next_line(fd);
			continue ;
		}
		map[i] = line;
		line = get_next_line(fd);
		filled_lines++;
		i++;
	}
	while (i > 0 && (ft_strcmp(map[i - 1], "") == 0
			|| check_line_empty(map[i - 1]) == 1))
	{
		free_ptr(map[i - 1]);
		i--;
	}
	map[i] = NULL;
	close(fd);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("[%s]\n", map[i]);
		// free(map[i]);
		i++;
	}
}

// TODO remove last empty lines
void	check_file_exists_or_empty(char *file)
{
	int		fd;
	ssize_t	bytes_read;
	char	buff[5];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	bytes_read = read(fd, &buff, 1);
	if (bytes_read == 0)
	{
		printf("Error : File %s is empty\n", file);
		exit(1);
	}
	else if (bytes_read < 0)
	{
		printf("Error : Read failed\n");
		exit(1);
	}
	close(fd);
}

void	parse_north_texture(t_game *game, char **split)
{
	if (game->north.path != NULL)
	{
		printf("error duplicate north texture\n");
		exit(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for north texture\n");
		exit(1);
	}
	game->north.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->north.path);
}

void	parse_south_texture(t_game *game, char **split)
{
	if (game->south.path != NULL)
	{
		printf("error duplicate south texture\n");
		exit(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for south texture\n");
		exit(1);
	}
	game->south.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->south.path);
}

void	parse_west_texture(t_game *game, char **split)
{
	if (game->west.path != NULL)
	{
		printf("error duplicate west texture\n");
		exit(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for west texture\n");
		exit(1);
	}
	game->west.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->west.path);
}

void	parse_east_texture(t_game *game, char **split)
{
	if (game->east.path != NULL)
	{
		printf("error duplicate east texture\n");
		exit(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for east texture\n");
		exit(1);
	}
	game->east.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->east.path);
}

int	check_file_extension(char *str)
{
	char	*res;

	res = ft_strrchr(str, '.');
	if (res == NULL || ft_strcmp(res, ".xpm") != 0 || ft_strlen(str) <= 4)
		return (0);
	return (1);
}

int	ft_count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	parse_color(char *color, t_color *color_struct)
{
	int		count;
	char	**rgb;

	count = ft_count_commas(color);
	if (count != 2)
	{
		printf("Error: Invalid color format\n");
		exit(1);
	}
	rgb = ft_split2(color, ",");
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		printf("Error: Invalid color format\n");
		exit(1);
	}
	color_struct->r = ft_atoi(rgb[0]);
	color_struct->g = ft_atoi(rgb[1]);
	color_struct->b = ft_atoi(rgb[2]);
	if (color_struct->r < 0 || color_struct->r > 255 || color_struct->g < 0
		|| color_struct->g > 255 || color_struct->b < 0
		|| color_struct->b > 255)
	{
		printf("Error: Invalid color format\n");
		exit(1);
	}
}

void	parse_texture_and_colors_info(char *line, t_game *game, t_map *map)
{
	char	**split;
	int		i;

	i = 0;
	(void)map;
	split = ft_split2(line, " \t\r\n\v\f");
	if (split[0] == NULL)
	{
		printf("Error: Invalid map\n");
		exit(1);
	}
	else if (split[1] == NULL || split[2] != NULL)
	{
		printf("Error: Invalid Map\n");
		exit(1);
	}
	if (check_file_extension(split[1]) == 0 && ft_strcmp(split[0], "F") != 0
		&& ft_strcmp(split[0], "C") != 0)
	{
		printf("Error: Invalid file extension\n");
		exit(1);
	}
	if (ft_strcmp(split[0], "NO") == 0)
		parse_north_texture(game, split);
	else if (ft_strcmp(split[0], "SO") == 0)
		parse_south_texture(game, split);
	else if (ft_strcmp(split[0], "WE") == 0)
		parse_west_texture(game, split);
	else if (ft_strcmp(split[0], "EA") == 0)
		parse_east_texture(game, split);
	else if (ft_strcmp(split[0], "F") == 0)
	{
		// parse_floor_color
		if (game->floor.color != NULL)
		{
			printf("error duplicate floor color\n");
			exit(1);
		}
		if (split[1] == NULL)
		{
			printf("Error: Missing color for floor\n");
			exit(1);
		}
		game->floor.color = ft_strdup(split[1]);
		parse_color(game->floor.color, &game->floor);
	}
	else if (ft_strcmp(split[0], "C") == 0)
	{
		// parse_floor_color
		if (game->ceiling.color != NULL)
		{
			printf("error duplicate ceiling color\n");
			exit(1);
		}
		if (split[1] == NULL)
		{
			printf("Error: Missing color for ceiling\n");
			exit(1);
		}
		game->ceiling.color = ft_strdup(split[1]);
		parse_color(game->ceiling.color, &game->ceiling);
	}
	// Free split array to avoid memory leak
	while (split[i])
	{
		free_ptr(split[i]);
		i++;
	}
	free_ptr(split);
}

int	check_if_file_empty(char *file)
{
	int		fd;
	ssize_t	bytes_read;
	char	buff[5];

	fd = open(file, O_RDONLY);
	bytes_read = read(fd, &buff, 1);
	if (bytes_read == 0)
		return (1);
	else if (bytes_read < 0)
		return (printf("Read failed\n"), 0);
	close(fd);
	return (0);
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
				game->map.grid[i][j] != ' ' && game->map.grid[i][j] != 'O')
			{
				printf("Error: Invalid character in map\n");
				exit(1);
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
		// game->map.grid[i] = ft_strtrim(game->map.grid[i], " ");
		printf("map[%d] = [%s]\n", i, game->map.grid[i]);
		if (game->map.grid[i][0] == '\0')
		{
			printf("Error: Empty line in map\n");
			exit(1);
		}
		while (game->map.grid[i][j])
		{
			if (i == 0 || i == game->map.height - 1 || j == 0
				|| j == (int)(ft_strlen(game->map.grid[i])) - 1)
			{
				if (game->map.grid[i][j] != '1' && game->map.grid[i][j] != ' ')
				{
					printf("Error: Map is not surrounded by walls\n");
					exit(1);
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

char	*ft_strtrim_last(char *s1, char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && check_charset(set, s1[i]) == 1)
	{
		s1[i] = '\0';
		i--;
	}
	return (s1);
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

void	verify_player_starting_position(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' ||
				game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				player_count++;
				if (player_count > 1)
				{
					printf("Error: More than one player starting position\n");
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
	{
		printf("Error: No player starting position\n");
		exit(1);
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
			if (game->map.grid[i][j] == ' ')
			{
				if ((i > 0 && game->map.grid[i - 1][j] != '1'
					&& game->map.grid[i - 1][j] != ' ')
					|| (i < game->map.height - 1 &&
					game->map.grid[i + 1][j] != '1' &&
					game->map.grid[i + 1][j] != ' ') ||
					(j > 0 && game->map.grid[i][j - 1] != '1' &&
					game->map.grid[i][j - 1] != ' ') ||
					(j < (int)ft_strlen(game->map.grid[i]) - 1 &&
					game->map.grid[i][j + 1] != '1' &&
					game->map.grid[i][j + 1] != ' '))
				{
					printf("Error: Invalid space found at (%d, %d)\n", i, j);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

int	check_if_player_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
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
			if (game->map.grid[i][j] == 'M' && game->map.grid[i][j] == '0'
				|| game->map.grid[i][j] == 'D' || game->map.grid[i][j] == 'O'
				|| check_if_player_direction(game->map.grid[i][j]) == 1)
			{
				if ((i > 0 && (game->map.grid[i - 1][j] != '0'
						&& game->map.grid[i - 1][j] != '1'
					&& game->map.grid[i - 1][j] != 'D'
						&& game->map.grid[i - 1][j] != 'O'
						&& !check_if_player_direction(game->map.grid[i
								- 1][j]))) ||
					// above
					(i < game->map.height - 1 && (game->map.grid[i
							+ 1][j] != '0' && game->map.grid[i + 1][j] != '1'
							&& game->map.grid[i + 1][j] != 'D'
							&& game->map.grid[i + 1][j] != 'O'
							&& !check_if_player_direction(game->map.grid[i
								+ 1][j]))) || // below
					(j > 0 && (game->map.grid[i][j - 1] != '0'
							&& game->map.grid[i][j - 1] != '1'
							&& game->map.grid[i][j - 1] != 'D'
							&& game->map.grid[i][j - 1] != 'O'
							&& !check_if_player_direction(game->map.grid[i][j
								- 1]))) ||
					// left
					(j < (int)ft_strlen(game->map.grid[i]) - 1
						&& (game->map.grid[i][j + 1] != '0'
							&& game->map.grid[i][j + 1] != '1'
							&& game->map.grid[i][j + 1] != 'D'
							&& game->map.grid[i][j + 1] != 'O'
							&& !check_if_player_direction(game->map.grid[i][j
								+ 1])))) // right
				{
					if (check_if_player_direction(game->map.grid[i][j]) == 1)
						printf("invalid player direction at (%d, %d)\n", i, j);
					else if (game->map.grid[i][j] == 'D')
						printf("invalid door at (%d, %d)\n", i, j);
					else if (game->map.grid[i][j] == 'O')
						printf("invalid object at (%d, %d)\n", i, j);
					else
						printf("invalid zero at (%d, %d)\n", i, j);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

void	get_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// t_player player;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' ||
				game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				game->player.pos_y = i;
				game->player.pos_x = j;
				fprintf(stderr, "x == %d,  y == %d \n", i, j);
				// game->player = player;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	calc_num_sprites(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	get_data()->num_sprites = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'M')
			{
				get_data()->num_sprites++;
			}
			j++;
		}
		i++;
	}
}

// clang-format off
void	init_sprites(t_game *game)
{
	t_data	*data;
	int		i;
	int		j;
	int		n;

	data = get_data();
	i = 0;
	j = 0;
	calc_num_sprites(game);
	data->sprites = malloc(sizeof(t_sprite) * data->num_sprites);
	n = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'M')
			{
				data->sprites[n].is_dead = 0;
				data->sprites[n].position.x
					= j * GRID_DIST + ((float)GRID_DIST / 2);
				data->sprites[n].position.y
					= i * GRID_DIST + ((float)GRID_DIST / 2);
				data->sprites[n].z = (float)(WIN_HEIGHT) / 2;
				data->sprites[n].texture.img_data.img
					= safer_xpm_file_to_image(data->mlx,
						"textures/zombie/1.xpm",
						&(data->sprites[n].texture.width),
						&(data->sprites[n].texture.height));
				data->sprites[n].texture.img_data.addr
					= safer_get_data_addr(data->sprites[n].texture.img_data.img,
						&(data->sprites[n].texture.img_data.bits_per_pixel),
						&(data->sprites[n].texture.img_data.line_length),
						&(data->sprites[n].texture.img_data.endian));
				data->sprites[n].current_frame = 0;
				data->sprites[n].current_dying_frame = 0;
				data->sprites[n].frame_delay = 0;
				n++;
			}
			j++;
		}
		i++;
	}
	i = 0;
}

void	pad_map_with_spaces(t_game *game)
{
	int		i;
	int		j;
	int		map_width;
	char	*line;
	int		k;

	i = 0;
	j = 0;
	map_width = calc_map_width(game->map.grid);
	game->map.width = map_width;
	printf("map width  2 = %d\n", map_width);
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		if ((int)ft_strlen(game->map.grid[i]) < map_width)
		{
			line = mallocate(sizeof(char) * (map_width + 1));
			k = 0;
			// Copy the original line
			while (game->map.grid[i][j])
			{
				line[k] = game->map.grid[i][j];
				k++;
				j++;
			}
			// Add the necessary spaces
			while (k < map_width)
			{
				line[k] = ' ';
				k++;
			}
			line[k] = '\0';
			// Free the original line
			free_ptr(game->map.grid[i]);
			// Duplicate the new padded line
			game->map.grid[i] = ft_strdup(line);
			// Free the temporary line
			free_ptr(line);
		}
		i++;
	}
	printf("------------ after padding ------------\n");
	print_map(game->map.grid);
	printf("------------\n");
}

t_game	check_map(int fd, char *file)
{
	t_map	m2;
	char	*line;
	char	**map;
	t_game	game;
	int		i;
	int		map_height;
	int		j;
	int		map_width;

	m2.width = 0;
	m2.height = 0;
	m2.valid = 0;
	line = NULL;
	m2.height = calc_height(fd, file, &m2, line);
	map = mallocate(sizeof(char *) * (m2.height + 1));
	if (!map)
	{
		printf("Error\n Malloc failed\n");
		exit(1);
	}
	fill_map(map, file, line);
	game.north.path = NULL;
	game.south.path = NULL;
	game.west.path = NULL;
	game.east.path = NULL;
	game.floor.color = NULL;
	game.ceiling.color = NULL;
	i = 0;
	// printf("map length = %d\n", m2.height);
	// print_map(map);
	while (i < 6)
	{
		parse_texture_and_colors_info(map[i], &game, &m2);
		i++;
	}
	// printf("east texture is [%s]\n", game.east.path);
	// printf("west texture is [%s]\n", game.west.path);
	// printf("south texture is [%s]\n", game.south.path);
	// printf("north texture is [%s]\n", game.north.path);
	// printf("floor color is [%d,%d,%d]\n", game.floor.r, game.floor.g,
	// game.floor.b); printf("ceiling color is [%d,%d,%d]\n", game.ceiling.r,
	// game.ceiling.g, game.ceiling.b); printf("------------\n");
	map_height = 0;
	while (map[map_height] != NULL)
	{
		map_height++;
	}
	map_height = map_height - 6;
	game.map.height = map_height;
	j = 0;
	game.map.grid = mallocate(sizeof(char *) * (map_height + 1));
	while (j < map_height)
	{
		// game.map.grid[j] = ft_strtrim(map[j + 6], " ");
		// game.map.grid[j] = ft_strtrim(game.map.grid[j], "\n");
		game.map.grid[j] = ft_strdup(map[j + 6]);
		j++;
	}
	game.map.grid[j] = NULL;
	// print_map(game.map.grid);
	// TODO parse the map
	// [x] Identify the start of the map (should be after texture and color
	// information) [x] Read the map lines and store them in a 2d array or
	// similar structure [x] Validate that the map contains only valid
	// characters (0, 1, N, S, E W) [x] Ensure the map is surrounded by walls
	// (1's) [x] Verify that there is exactly one player starting position (N,
	// S, E, or W) [x] check for invalid spaces in the map
	// check_invalid_spaces(&game);
	// printf("------------\n");
	// print_map(game.map.grid);
	// printf("------------\n");
	map_width = calc_map_width(game.map.grid);
	map_height = calc_map_height(game.map.grid);
	check_if_map_contains_only_valid_characters(&game);
	check_map_sourrounded_by_walls(&game);
	printf("map width = %d\n", map_width);
	printf("map height = %d\n", map_height);
	pad_map_with_spaces(&game);
	check_invalid_map(&game);
	verify_player_starting_position(&game);
	get_player_position(&game);
	// printf("player position = [%f,%f]\n", game.player.pos_x,
	// game.player.pos_y);
	// parse_texture_info(map[0], &game);
	// free(map);
	return (game);
}

int	has_wall_at(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	// printf("x = %f\n", x);
	// printf("y = %f\n", y);
	map_x = round(x);
	map_y = round(y);
	// printf("map_x = %d\n", map_x);
	// printf("map_y = %d\n", map_y);
	// printf("map[map_x][map_y] = %c\n", game->map.grid[map_x][map_y]);
	if (map_x < 0 || map_x >= game->map.height || map_y < 0 || map_y >= game->map.width)
		return (1);
	if (game->map.grid[map_x][map_y] == '1')
		return (1);
	return (0);
}
