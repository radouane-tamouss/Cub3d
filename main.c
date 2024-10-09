/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:26 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/09 00:59:00 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// this will be used to store data and share it
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
void	init_data(t_game game)
{
	get_data()->mlx = mlx_init();
	if (get_data()->mlx != NULL)
		get_data()->win = mlx_new_window(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");
	if (get_data()->mlx == NULL || get_data()->win == NULL)
	{
		print_err("CUB3D: mlx failed\n");
		exiter(1);
	}
	get_data()->background_img.img = mlx_new_image(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);// TODO protect failing
	get_data()->background_img.addr = mlx_get_data_addr(get_data()->background_img.img,
		&(get_data()->background_img.bits_per_pixel), &(get_data()->background_img.line_length),
		&(get_data()->background_img.endian)); // TODO protect failing

	get_data()->floor_color = CREATE_TRGB(0, game.floor.r, game.floor.g, game.floor.b);//BROWN;// TODO this just for startin befroe parsing is complete
	get_data()->ceiling_color = CREATE_TRGB(0, game.ceiling.r, game.ceiling.g, game.ceiling.b);//CYAN;// TODO this just for startin befroe parsing is complete
	// init_background();
	mlx_hook(get_data()->win, 2, 1L << 0, handle_keys, NULL);// this to handle when a key pressed
	mlx_hook(get_data()->win, 17, 1L << 0, ft_close, NULL);// this to handle when red arrow clicked
	mlx_hook(get_data()->win, 6, 1L<<6, mouse_event, NULL);
	get_data()->player_pos.x = game.player.pos_x * GRID_DIST + GRID_DIST/2;//1. * GRID_DIST;// TODO for test only
	get_data()->player_pos.y =  game.player.pos_y * GRID_DIST + GRID_DIST/2;//1. * GRID_DIST;// TODO for test only
	get_data()->player_angle = 0;//MY_PI / 4;
	get_data()->player_dir.x = cos(get_data()->player_angle) * SPEED;
	get_data()->player_dir.y = sin(get_data()->player_angle) * SPEED;

	get_data()->map = game.map.grid;
	get_data()->height = game.map.height;
	get_data()->width = game.map.width;

	get_data()->north_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->north_img.width), &(get_data()->north_img.height));
	get_data()->north_img.img_data.addr = mlx_get_data_addr(get_data()->north_img.img_data.img, &(get_data()->north_img.img_data.bits_per_pixel), &(get_data()->north_img.img_data.line_length), &(get_data()->north_img.img_data.endian));

	get_data()->south_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->south_img.width), &(get_data()->south_img.height));
	get_data()->south_img.img_data.addr = mlx_get_data_addr(get_data()->south_img.img_data.img, &(get_data()->south_img.img_data.bits_per_pixel), &(get_data()->south_img.img_data.line_length), &(get_data()->south_img.img_data.endian));

	get_data()->east_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->east_img.width), &(get_data()->east_img.height));
	get_data()->east_img.img_data.addr = mlx_get_data_addr(get_data()->east_img.img_data.img, &(get_data()->east_img.img_data.bits_per_pixel), &(get_data()->east_img.img_data.line_length), &(get_data()->east_img.img_data.endian));
	
	get_data()->west_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->west_img.width), &(get_data()->west_img.height));
	get_data()->west_img.img_data.addr = mlx_get_data_addr(get_data()->west_img.img_data.img, &(get_data()->west_img.img_data.bits_per_pixel), &(get_data()->west_img.img_data.line_length), &(get_data()->west_img.img_data.endian));
	//=====
	get_data()->door_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/gate.xpm", &(get_data()->door_img.width), &(get_data()->door_img.height));
	get_data()->door_img.img_data.addr = mlx_get_data_addr(get_data()->door_img.img_data.img, &(get_data()->door_img.img_data.bits_per_pixel), &(get_data()->door_img.img_data.line_length), &(get_data()->door_img.img_data.endian));
}

void	draw_circle(t_img_data *img, int cho3a3, t_vector point)
{
	int i = point.y - cho3a3;
	int j;

	while (i < point.y + cho3a3)
	{
		j = point.x - cho3a3;
		while (j < point.x + cho3a3)
		{
			if (calc_dist(j, i, point) <= cho3a3)
			{
				// printf("pixeled the point x ==%d  | y == %d | with dist == %d\n", j, i, calc_dist(j, i, point));
				put_pixel(img, j, i, RED);
			}
			j++;
		}
		i++;
	}
}

void	draw_player(void)
{
	t_vector player_front;

	player_front.x = get_data()->player_pos.x / SQUARE_SIZE + 5 * get_data()->player_dir.x;
	player_front.y = get_data()->player_pos.y  / SQUARE_SIZE + 5 * get_data()->player_dir.y;
	draw_circle(&(get_data()->background_img), 7, get_data()->player_pos);
	line_between_2points(get_data()->player_pos,
				player_front, RED);
}

// check file 
	// check extension
	// check the file if exists or empty 

int check_file(char *str, int *fd)
{
	int i = 0;
	char *res;
	ssize_t bytes_read;
	char buff[5];
	if (str == NULL)
		return (0);
	res = ft_strrchr(str, '.');
	if (res == NULL || ft_strcmp(res, ".cub") != 0 || ft_strlen(str) <= 4)
		return (printf("invalid file\n"), 0);
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

size_t calc_height(int fd, char *file, t_map *m2, char *line)
{
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	m2->height++;
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		m2->height++;
	}
	close(fd);
	return (m2->height);
}

int check_line_empty(char *line)
{
	int i = 0;
	while(line[i])
	{
		if (check_charset(" \t\r\n\v\f", line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
void fill_map(char **map, char *file, char *line)
{
	int fd;
	int i;
	int filled_lines;
	
	fd = open(file, O_RDONLY);
	filled_lines = 0;
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		if (filled_lines <= 6 && (ft_strcmp(line, "") == 0 || check_line_empty(line) == 1))
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		map[i] = line;
		line = get_next_line(fd);
		filled_lines++;
		i++;
	}
	// Remove trailing empty lines
    while (i > 0 && (ft_strcmp(map[i - 1], "") == 0 || check_line_empty(map[i - 1]) == 1))
    {
        free(map[i - 1]);
        i--;
    }
	map[i] = NULL;
	close(fd);
}
void print_map(char **map)
{
	int i = 0;
	while(map[i] != NULL)
	{
		printf("[%s]\n",map[i]);
		// free(map[i]);
		i++;
	}
}
// TODO remove last empty lines
void check_file_exists_or_empty(char *file)
{
	int fd;
	ssize_t bytes_read;
	char buff[5];
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

void parse_north_texture(t_game *game, char **split)
{
    if (game->north.path != NULL)
    {
        printf("error duplicate north texture\n");
        exit(1);
    }
    if (split[1] == NULL) {
        printf("Error: Missing path for north texture\n");
        exit(1);
    }
    game->north.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->north.path);
}
void parse_south_texture(t_game *game, char **split)
{
	if (game->south.path != NULL)
	{
		printf("error duplicate south texture\n");
		exit(1);
	}
	if (split[1] == NULL) {
		printf("Error: Missing path for south texture\n");
		exit(1);
	}
	game->south.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->south.path);
}
void parse_west_texture(t_game *game,char **split)
{
	if (game->west.path != NULL)
	{
		printf("error duplicate west texture\n");
		exit(1);
	}
	if (split[1] == NULL) {
		printf("Error: Missing path for west texture\n");
		exit(1);
	}
	game->west.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->west.path);
}

void parse_east_texture(t_game *game, char **split)
{
	if (game->east.path != NULL)
	{
		printf("error duplicate east texture\n");
		exit(1);
	}
	if (split[1] == NULL) {
		printf("Error: Missing path for east texture\n");
		exit(1);
	}
	game->east.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->east.path);
}

int check_file_extension(char *str)
{
	char *res;
	res = ft_strrchr(str, '.');
	if (res == NULL || ft_strcmp(res, ".xpm") != 0 || ft_strlen(str) <= 4)
		return (0);
	return (1);
}
int ft_count_commas(char *str)
{
	int i = 0;
	int count = 0;
	while(str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
void parse_color(char *color, t_color *color_struct)
{
	int count = ft_count_commas(color);
	if (count != 2)
	{
		printf("Error: Invalid color format\n");
		exit(1);
	}
	char **rgb = ft_split2(color, ",");
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		printf("Error: Invalid color format\n");
		exit(1);
	}
	color_struct->r = ft_atoi(rgb[0]);
	color_struct->g = ft_atoi(rgb[1]);
	color_struct->b = ft_atoi(rgb[2]);
	if (color_struct->r < 0 || color_struct->r > 255
			|| color_struct->g < 0 || color_struct->g > 255
			|| color_struct->b < 0 || color_struct->b > 255)
	{
		printf("Error: Invalid color format\n");
		exit(1);
	}
}
void parse_texture_and_colors_info(char *line, t_game *game, t_map *map)
{
    char **split;
    
    split = ft_split2(line, " \t\r\n\v\f");
    if (split[0] == NULL) {
        printf("Error: Invalid map\n");
        exit(1);
    }
	else if (split[1] == NULL || split[2] != NULL) {
		printf("Error: Invalid Map\n");
		exit(1);
	}
	if (check_file_extension(split[1]) == 0 && ft_strcmp(split[0], "F") != 0 && ft_strcmp(split[0], "C") != 0)
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
		if (game->floor.color!= NULL)
		{
			printf("error duplicate floor color\n");
			exit(1);
		}
		if (split[1] == NULL) {
			printf("Error: Missing color for floor\n");
			exit(1);
		}
		game->floor.color = ft_strdup(split[1]);
		parse_color(game->floor.color, &game->floor);
	}
	else if (ft_strcmp(split[0], "C") == 0)
	{
		// parse_floor_color
		if (game->ceiling.color!= NULL)
		{
			printf("error duplicate ceiling color\n");
			exit(1);
		}
		if (split[1] == NULL) {
			printf("Error: Missing color for ceiling\n");
			exit(1);
		}
		game->ceiling.color = ft_strdup(split[1]);
		parse_color(game->ceiling.color, &game->ceiling);
	}
    // Free split array to avoid memory leak
    int i = 0;
    while (split[i]) {
        free(split[i]);
        i++;
    }
    free(split);
}

int check_if_file_empty(char *file)
{
	int fd;
	ssize_t bytes_read;
	char buff[5];
	fd = open(file, O_RDONLY);
	bytes_read = read(fd, &buff, 1);
	if (bytes_read == 0)
		return (1);
	else if (bytes_read < 0)
		return (printf("Read failed\n"), 0);
	close(fd);
	return (0);
}
void check_if_map_contains_only_valid_characters(t_game *game)
{
	int i = 0;
	int j = 0;
	// printf("map[7][0] = [%s]\n", game->map.grid[7]);
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		// game->map.grid[i] = ft_strtrim(game->map.grid[i], " ");
		game->map.grid[i] = ft_strtrim(game->map.grid[i], "\n");
		// if (game->map.grid[i][0] == '\0')
		// {
		// 	printf("Error: Empty line in map\n");
		// 	exit(1);
		// }
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1' && game->map.grid[i][j] != 'N' && game->map.grid[i][j] != 'S' && game->map.grid[i][j] != 'E' && game->map.grid[i][j] != 'W' && game->map.grid[i][j] != ' ')
			{
				printf("Error: Invalid character in map\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}
void check_map_sourrounded_by_walls(t_game *game)
{
	int i = 0;
	int j = 0;
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
			if (i == 0 || i == game->map.height - 1 || j == 0 || j == ft_strlen(game->map.grid[i]) - 1)
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
int calc_map_height(char **map)
{
	int i = 0;
	while(map[i] != NULL)
	{
		i++;
	}
	return (i);
}
char *ft_strtrim_last(char *s1, char *set)
{
	int i = ft_strlen(s1) - 1;
	while (i >= 0 && check_charset(set, s1[i]) == 1)
	{
		s1[i] = '\0';
		i--;
	}
	return (s1);
}
int calc_map_width(char **map)
{
	int i = 0;
	int j = 0;
	int max = 0;
	while(map[i] != NULL)
	{
		j = 0;
		if (check_line_empty(map[i]) != 1)
			map[i] = ft_strtrim_last(map[i], " ");
		while(map[i][j])
		{
			j++;
		}
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}
void verify_player_starting_position(t_game *game)
{
	int i = 0;
	int j = 0;
	int player_count = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' || game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
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

void check_invalid_spaces(t_game *game)
{
	int i = 0;
	int j = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == ' ')
			{
				if ((i > 0 && game->map.grid[i - 1][j] != '1' && game->map.grid[i - 1][j] != ' ') ||  // above
					(i < game->map.height - 1 && game->map.grid[i + 1][j] != '1' && game->map.grid[i + 1][j] != ' ') ||  // below
					(j > 0 && game->map.grid[i][j - 1] != '1' && game->map.grid[i][j - 1] != ' ') ||  // left
					(j < ft_strlen(game->map.grid[i]) - 1 && game->map.grid[i][j + 1] != '1' && game->map.grid[i][j + 1] != ' '))  // right
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
int check_if_player_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
void check_invalid_map(t_game *game)
{
    int i = 0;
    int j = 0;
    while (game->map.grid[i] != NULL)
    {
        j = 0;
        while (game->map.grid[i][j])
        { 
            if (game->map.grid[i][j] == '0' || check_if_player_direction(game->map.grid[i][j]) == 1)
            {
                if ((i > 0 && (game->map.grid[i - 1][j] != '0' && game->map.grid[i - 1][j] != '1' && !check_if_player_direction(game->map.grid[i - 1][j]))) ||  // above
                    (i < game->map.height - 1 && (game->map.grid[i + 1][j] != '0' && game->map.grid[i + 1][j] != '1' && !check_if_player_direction(game->map.grid[i + 1][j]))) ||  // below
                    (j > 0 && (game->map.grid[i][j - 1] != '0' && game->map.grid[i][j - 1] != '1' && !check_if_player_direction(game->map.grid[i][j - 1]))) ||  // left
                    (j < ft_strlen(game->map.grid[i]) - 1 && (game->map.grid[i][j + 1] != '0' && game->map.grid[i][j + 1] != '1' && !check_if_player_direction(game->map.grid[i][j + 1]))))  // right
                {
					if (check_if_player_direction(game->map.grid[i][j]) == 1)
						printf("invalid player direction at (%d, %d)\n", i, j);
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
void get_player_position(t_game *game)
{
	int i = 0;
	int j = 0;
	// t_player player;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' || game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				game->player.pos_y = i;
				game->player.pos_x = j;
				fprintf(stderr, "x == %d,  y == %d \n", i, j);
				// game->player = player;
				return;
			}
			j++;
		}
		i++;
	}
}

void pad_map_with_spaces(t_game *game)
{
    int i = 0;
    int j = 0;
    int map_width = calc_map_width(game->map.grid);
	game->map.width = map_width;
	printf("map width  2 = %d\n", map_width);

    while (game->map.grid[i] != NULL)
    {
        j = 0;
        if (ft_strlen(game->map.grid[i]) < map_width)
        {
            char *line = malloc(sizeof(char) * (map_width + 1));
            int number_of_spaces_to_add = map_width - ft_strlen(game->map.grid[i]);
            int k = 0;

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
            free(game->map.grid[i]); // Free the original line
            game->map.grid[i] = ft_strdup(line); // Duplicate the new padded line
            free(line); // Free the temporary line
        }
        i++;
    }

    printf("------------ after padding ------------\n");
    print_map(game->map.grid);
    printf("------------\n");
}

t_game check_map(int fd, char *file)
{
	t_map m2;
	char *line;
	char **map;
	m2.width = 0;
	m2.height = 0;
	m2.valid = 0;
	line = NULL;
	m2.height = calc_height(fd, file, &m2, line);
	map = malloc(sizeof(char *) * (m2.height + 1));
	if (!map)
	{
		printf("Error\n Malloc failed\n");
		exit(1);
	}
	fill_map(map, file, line);
	t_game game;
	game.north.path = NULL;
	game.south.path = NULL;
	game.west.path = NULL;
	game.east.path = NULL;
	game.floor.color = NULL;
	game.ceiling.color = NULL;

	int i = 0;
	// printf("map length = %d\n", m2.height);
	// print_map(map);
	while(i < 6)
	{
		parse_texture_and_colors_info(map[i], &game, &m2);
		i++;
	}

	// printf("east texture is [%s]\n", game.east.path);
	// printf("west texture is [%s]\n", game.west.path);
	// printf("south texture is [%s]\n", game.south.path);
	// printf("north texture is [%s]\n", game.north.path);
	// printf("floor color is [%d,%d,%d]\n", game.floor.r, game.floor.g, game.floor.b);
	// printf("ceiling color is [%d,%d,%d]\n", game.ceiling.r, game.ceiling.g, game.ceiling.b);
	// printf("------------\n");
	
	
	int map_height = 0;
	while(map[map_height] != NULL)
	{
		map_height++;
	}
	map_height = map_height - 6;
	game.map.height = map_height;
	int j = 0;
	game.map.grid = malloc(sizeof(char *) * (map_height + 1));
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
	// [x] Identify the start of the map (should be after texture and color information) 
	// [x] Read the map lines and store them in a 2d array or similar structure
	// [x] Validate that the map contains only valid characters (0, 1, N, S, E W)
	// [x] Ensure the map is surrounded by walls (1's)
	// [x] Verify that there is exactly one player starting position (N, S, E, or W)
	// [x] check for invalid spaces in the map
	// check_invalid_spaces(&game);
	// printf("------------\n");
	// print_map(game.map.grid);
	// printf("------------\n");
	int map_width = calc_map_width(game.map.grid);
	map_height = calc_map_height(game.map.grid);
	check_if_map_contains_only_valid_characters(&game);
	check_map_sourrounded_by_walls(&game);
	printf("map width = %d\n", map_width);
	printf("map height = %d\n", map_height);
	pad_map_with_spaces(&game);
	check_invalid_map(&game);
	verify_player_starting_position(&game);
	get_player_position(&game);
	// printf("player position = [%f,%f]\n", game.player.pos_x, game.player.pos_y);

	// parse_texture_info(map[0], &game);
	// free(map);
	return (game);
}

// void render_background(t_game *game)
// {
// 	int i = 0;
// 	int j = 0;
// 	int color;
// 	int width = game->map.width * SQUARE_SIZE;
// 	int height = game->map.height * SQUARE_SIZE;
// 	while (i < height)
// 	{
// 		j = 0;
// 		while (j < width)
// 		{
// 			mlx_pixel_put(game->mlx, game->win, j, i, BLACK);
// 			j++;
// 		}
// 		i++;
// 	}
// }
// void my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
// {
// 	char *dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

void render_wall(int x, int y)
{
	int i = 0;
	int j = 0;

	while (i < SQUARE_SIZE - 1)
	{
		j = 0;
		while (j < SQUARE_SIZE - 1)
		{
			// mlx_pixel_put(game->mlx, game->win, j + x, i + y, RED);
			put_pixel(&(get_data()->minimap.img_data), j + x, i + y, CYAN);
			j++;
		}
		i++;
	}
}

void render_line(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double max = fmax(fabs(dx), fabs(dy));

    double x_step = dx / max;
    double y_step = dy / max;

    double x = x1;
    double y = y1;

    for (int i = 0; i <= max; i++)
    {
        put_pixel(&(get_data()->minimap.img_data), x, y, RED);
        x += x_step;
        y += y_step;
    }
}
// void update_player(t_game *game)
// {
// 	game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;

// }
int has_wall_at(t_game *game, double x, double y)
{
	// printf("x = %f\n", x);
	// printf("y = %f\n", y);
	int map_x = round(x);
	int map_y = round(y);
	// printf("map_x = %d\n", map_x);
	// printf("map_y = %d\n", map_y);
	// printf("map[map_x][map_y] = %c\n", game->map.grid[map_x][map_y]);
	if (map_x < 0 || map_x >= game->map.height || map_y < 0 || map_y >= game->map.width)
		return (1);
	if (game->map.grid[map_x][map_y] == '1')
		return (1);
	return (0);
}

void render_floor(int x, int y)
{
	int i = 0;
	int j = 0;
	while(i < SQUARE_SIZE - 1)
	{
		j = 0;
		while(j < SQUARE_SIZE - 1)
		{
			// mlx_pixel_put(game->mlx, game->win, j + x, i + y, game->floor.r << 16 | game->floor.g << 8 | game->floor.b);
			put_pixel(&(get_data()->minimap.img_data), j + x, i + y, get_data()->floor_color);
			j++;
		}
		i++;
	}
}
void render_map(void)
{
	int i,j;
	int x,y;
	i = 0;
	while(i < get_data()->height)
	{
		j = 0;
		while (j < get_data()->width)
		{
			x = j * SQUARE_SIZE;
			y = i * SQUARE_SIZE;
			if (get_data()->map[i][j] == '1')
			{
				render_wall(x, y);
			}
			else if (get_data()->map[i][j] == '0')
			{
				render_floor(x, y);
			}
			else if (check_if_player_direction(get_data()->map[i][j]) == 1)
			{
				render_floor(x, y);
			}
			j++;
		}
		i++;
	}
}

void render_ray(t_game *game, t_ray ray)
{
	// Calculate the end point of the ray
	int center_x = game->player.pos_y * SQUARE_SIZE + SQUARE_SIZE / 2;
	int center_y = game->player.pos_x * SQUARE_SIZE + SQUARE_SIZE / 2;
	int end_x = center_x + cos(ray.ray_angle) * 80;
	int end_y = center_y + sin(ray.ray_angle) * 80;

	// Render the ray
	render_line(center_x, center_y, end_x, end_y);
}
void render_rays(t_game *game)
{
	int i = 0;
	while (i < game->num_rays)
	{
		render_ray(game, game->rays[i]);
		i++;
	}
}
void render_player()
{
	int x, y;
	int radius = 3;
	// int radius = game->player.radius;
	int center_x = (get_data()->player_pos.x / GRID_DIST) * SQUARE_SIZE;
	int center_y = (get_data()->player_pos.y / GRID_DIST) * SQUARE_SIZE;

	// fprintf(stderr, "x== %d,  y==%d\n", center_x, center_y);

	for (y = -radius; y <= radius; y++)
	{
		for (x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				put_pixel(&(get_data()->minimap.img_data), center_x + x, center_y + y, RED);
			}
		}
	}
	// Calculate the end point of the direction line
    int end_x = center_x + cos(get_data()->player_angle) * 80;
    int end_y = center_y + sin(get_data()->player_angle) * 80;
	render_line(center_x, center_y, end_x, end_y);
	// render_rays(game);
}
void render_frame()
{
	ft_memset(get_data()->minimap.img_data.addr, 0, get_data()->width * SQUARE_SIZE * get_data()->height * SQUARE_SIZE * (get_data()->minimap.img_data.bits_per_pixel / 8));

	render_map();
	render_player();
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

// void	init_minimap(void)
// {
// 	ft_memset(get_data()->minimap.img_data.addr, 0, get_data()->width * SQUARE_SIZE * get_data()->height * SQUARE_SIZE * (get_data()->minimap.img_data.bits_per_pixel / 8));
// 	render_map();
// }

// void	render_minimap(void)
// {
	
// }
int key_press(int keycode, t_game *game)
{
   if (keycode == ESC_MAC)
	{
		exit(0);
	}
	else if (keycode == UP_MAC)
	{
		printf("UP\n");
		game->player.walk_direction = 1;
	}
	else if (keycode == DOWN_MAC)
	{
		printf("Down\n");
		game->player.walk_direction = -1;
	}
	else if (keycode == LEFT_MAC)
	{
		printf("Left\n");
		game->player.turn_direction = -1;
	}
	else if (keycode == RIGHT_MAC)
	{
		printf("Right\n");
		game->player.turn_direction = 1;
	} 
	return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == UP_MAC || keycode == DOWN_MAC)
        game->player.walk_direction = 0;
    if (keycode == LEFT_MAC || keycode == RIGHT_MAC)
        game->player.turn_direction = 0;
    return (0);
}
// void update_player(t_game *game)
// {
//     // game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
// 	// double move_step = game->player.walk_direction * game->player.move_speed;
// 	// double new_player_x = game->player.pos_x + sin(game->player.rotation_angle) * move_step;
// 	// double new_player_y = game->player.pos_y + cos(game->player.rotation_angle) * move_step;
// 	// if (has_wall_at(game, new_player_x, new_player_y) != 1)
// 	// {
// 	// 	game->player.pos_x = new_player_x;
// 	// 	game->player.pos_y = new_player_y;
// 	// 	printf("%snew_player_x = %.2f, new_player_y = %.2f\n%s",CRED,  new_player_x, new_player_y, CRESET);
// 	// }


// }
// void cast_all_rays(t_game *game)
// {
// 	int column_id = 0;

// 	game->ray_angle = game->player.rotation_angle - (FOV_ANGLE / 2);
// 	game->rays = malloc(sizeof(t_ray) * game->num_rays);
// 	while (column_id < game->num_rays)
// 	{
// 		// game->rays[column_id].ray_angle = normalize_angle(game->ray_angle);
// 		// game->rays[column_id].wall_hit_x = 0;
// 		// game->rays[column_id].wall_hit_y = 0;
// 		// game->rays[column_id].distance = 0;
// 		// game->rays[column_id].was_hit_vertical = 0;
// 		// cast_ray(game, column_id);
// 		game->rays[column_id].ray_angle = game->ray_angle;
// 		game->ray_angle += FOV_ANGLE / game->num_rays;
// 		column_id++;
// 	}

// 	// printf("%s========RAYS========%s\n", CRED, CRESET);
// 	// int i = 0;
// 	// while (i < game->num_rays)
// 	// {
// 	// 	printf("ray_angle = %f\n", game->rays[i].ray_angle);
// 	// 	i++;
// 	// }
// 	// printf("%s====================%s\n", CRED, CRESET);
// }
int loop_hook(t_game *game)
{
    // Update player position based on key presses
    // if (game->player.walk_direction != 0)
    // {
    //     game->player.pos_x += game->player.walk_direction * game->player.move_speed * sin(game->player.rotation_angle);
    //     game->player.pos_y += game->player.walk_direction * game->player.move_speed * cos(game->player.rotation_angle);
    // }
    // if (game->player.turn_direction != 0)
    // {
    //     game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
    // }

		// game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
		// double move_step = game->player.walk_direction * game->player.move_speed;
		// double new_player_x = game->player.pos_x + sin(game->player.rotation_angle) * move_step;
		// double new_player_y = game->player.pos_y + cos(game->player.rotation_angle) * move_step;
		// if (has_wall_at(game, new_player_x, new_player_y) != 1)
		// {
		// 	game->player.pos_x = new_player_x;
		// 	game->player.pos_y = new_player_y;
		// 	// printf("%snew_player_x = %.2f, new_player_y = %.2f\n%s",CRED,  new_player_x, new_player_y, CRESET);
		// }
		// cast_all_rays(game);

	// render_rays(game);
	init_background();
	render_walls();
    // Render the frame
    // render_player(game);
	render_background();
    render_frame();
	// draw_player();
	mlx_put_image_to_window(get_data()->mlx, get_data()->win, get_data()->minimap.img_data.img, 0, 0);

    return (0);
}
// cast all rays
// table of rays
// render the rays


int main(int ac, char **av)
{
    int fd;
    t_game game;

    if (ac != 2 || check_file(av[1], &fd) == 0)
        return (printf("Error\nUsage: ./Cube3d map.cub\n"), 0);
    game = check_map(fd, av[1]);
    close(fd);
    printf("width = %d\n", game.map.width * 32);
    printf("height = %d\n", game.map.height * 32);
    // game.mlx = mlx_init();
    // game.win = mlx_new_window(game.mlx, game.map.width * SQUARE_SIZE, game.map.height * SQUARE_SIZE, "cube3d");
    // game.img.img = mlx_new_image(get_data()->mlx, game.map.width * SQUARE_SIZE, game.map.height * SQUARE_SIZE);
    // game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);

    // game.player.radius = 3;
    // game.player.pos_x = game.map.height / 2;
    // game.player.pos_y = game.map.width / 2;
    // game.player.move_speed = MOVE_SPEED;
    // game.player.rotation_speed = ROTATION_SPEED;
    // game.player.turn_direction = 0;
    // game.player.walk_direction = 0;
	// game.win_width = game.map.width * SQUARE_SIZE;
	// game.win_height= game.map.height * SQUARE_SIZE;
	// game.num_rays = game.win_width / WALL_STRIP_WIDTH;
	// printf("num_rays = %d\n", game.num_rays);
	// render_background(&game);
	// cast_all_rays(&game);
    // mlx_hook(game.win, 2, 1L << 0, key_press, &game); // Register key press hook
    // mlx_hook(game.win, 3, 1L << 1, key_release, &game); // Register key release hook
    // mlx_loop_hook(game.mlx, loop_hook, &game);

    // mlx_loop_hook(game.mlx, loop_hook, &game);

	init_data(game);

	init_background();
	render_walls();
	render_background();
	get_data()->minimap.img_data.img = mlx_new_image(get_data()->mlx, get_data()->width * SQUARE_SIZE, get_data()->height * SQUARE_SIZE);
    get_data()->minimap.img_data.addr = mlx_get_data_addr(get_data()->minimap.img_data.img, &get_data()->minimap.img_data.bits_per_pixel, &get_data()->minimap.img_data.line_length, &get_data()->minimap.img_data.endian);
	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);

    mlx_loop(get_data()->mlx);

    return (0);
}