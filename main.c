/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rtamouss <rtamouss@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 20:55:26 by eouhrich      #+#    #+#                 */
/*   Updated: 2024/09/29 14:57:35by rtamouss      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// this will be used to store data and share it
// t_data	*get_data(void)
// {
// 	static t_data	data;

// 	return (&data);
// }
// // initialazing the struct data of cube
// void	init_data()
// {
// 	get_data()->mlx = mlx_init();
// 	if (get_data()->mlx != NULL)
// 	{
// 		get_data()->win = mlx_new_window(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
// 		get_data()->data.img = mlx_new_image(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	}
// 	if (get_data()->mlx == NULL || get_data()->win == NULL || get_data()->data.img == NULL)
// 	{
// 		ft_putstr_fd("CUB3D: mlx failed\n", 2);
// 		exiter(1);
// 	}
// 	vars->data.addr = mlx_get_data_addr(vars->data.img,
// 			&(vars->data.bits_per_pixel), &(vars->data.line_length),
// 			&(vars->data.endian));
// 	get_data()->floor_color = BROWN;// TODO this just for startin befroe parsing is complete
// 	get_data()->ceiling_color = CYAN;// TODO this just for startin befroe parsing is complete
// }

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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
	
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		if (ft_strcmp(line, "") == 0 || check_line_empty(line) == 1)
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
}
void print_map(char **map)
{
	int i = 0;
	while(map[i] != NULL)
	{
		printf("%s",map[i]);
		free(map[i]);
		i++;
	}
	printf("\n");
}
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
	printf("north texture is [%s]\n", game->north.path);
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
	printf("south texture is [%s]\n", game->south.path);
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
	printf("west texture is [%s]\n", game->west.path);
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
	printf("east texture is [%s]\n", game->east.path);
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
        printf("Error: Invalid line format\n");
        exit(1);
    }
	else if (split[1] == NULL || split[2] != NULL) {
		printf("Error: Invalid line format\n");
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
		printf("floor color is [%s]\n", game->floor.color);
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
		printf("ceiling color is [%s]\n", game->ceiling.color);
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
t_map check_map(int fd, char *file)
{
	t_map m2;
	char *line;
	char **map;
	m2.width = 0;
	m2.height = 0;
	m2.valid = 0;
	line = NULL;
	m2.height = calc_height(fd, file, &m2, line);
	printf("the height of the map is %d\n", m2.height);
	printf("------------\n");
	map = malloc(sizeof(char *) * (m2.height + 1));
	if (!map)
	{
		printf("Error\n Malloc failed\n");
		m2.valid = 0;
		return (m2);
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
	while(i < 7)
	{
		parse_texture_and_colors_info(map[i], &game, &m2);
		i++;
	}

	// parse_texture_info(map[0], &game);
	// free(map);
	return (m2);
}

int	main(int ac, char **av)
{
	int		fd;
	t_map map;

	if (ac != 2 || check_file(av[1], &fd) == 0)
		return (printf("Error\nUsage: ./Cube3d map.cub\n"), 0);
	map = check_map(fd, av[1]);
	close(fd);
	

	// init_data();
	// render_background();

	//TODO complete .. 
	return (0);
}