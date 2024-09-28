/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:26 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/28 22:01:56 by rtamouss         ###   ########.fr       */
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
	if (res == NULL || ft_strcmp(res, ".cub") != 0)
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

void fill_map(char **map, char *file, char *line)
{
	int fd;
	int i;
	
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
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

void parse_texture_info(char *line, t_game *game, t_map *map)
{
	char **split;
	
	split = ft_split(line, ' ');
	if (ft_strcmp(split[0], "NO") == 0)
	{
		if (game->north.path != NULL)
		{
			printf("error duplicate north texture\n");
			exit(1);
		}
		game->north.path = ft_strtrim(split[1], "\n");
		int fd = open(game->north.path, O_RDONLY);
        if (fd == -1)
        {
			perror("open");
            map->valid = 0;
            exit(55);
        }
        close(fd);
		printf("[the north is %s]\n", game->north.path);
	}
	else if(ft_strcmp(split[0], "SO") == 0)
	{
		if (game->south.path != NULL)
		{
			printf("error duplicate south texture\n");
			exit(1);
		}
		game->south.path = ft_strtrim(split[1], "\n");
		int fd = open(game->south.path, O_RDONLY);
        if (fd == -1)
        {
			perror("open");
            map->valid = 0;
            exit(1);
        }
        close(fd);
		printf("[the south is %s]\n", game->south.path);
	}
	else if(ft_strcmp(split[0], "WE") == 0)
	{
		if (game->west.path != NULL)
		{
			printf("error duplicate west texture\n");
			exit(1);
		}
		int fd = open(split[1], O_RDONLY);
        if (fd == -1)
        {
            printf("error: west texture file does not exist: %s\n", split[1]);
            map->valid = 0;
            exit(1);
        }
        close(fd);
		game->west.path = split[1];
		printf("the west is %s\n", game->west.path);
	}
	else if(ft_strcmp(split[0], "EA") == 0)
	{
		if (game->west.path != NULL)
		{
			printf("error duplicate west texture\n");
			exit(1);
		}
		 int fd = open(split[1], O_RDONLY);
        if (fd == -1)
        {
            printf("error: east texture file does not exist: %s\n", split[1]);
            map->valid = 0;
            exit(1);
        }
        close(fd);
		game->east.path = split[1];
		printf("the east path is %s\n", game->east.path);
	}
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
	int i = 0;
	while(map[i])
	{
		parse_texture_info(map[i], &game, &m2);
		i++;
	}
	// parse_texture_info(map[0], &game);
	// print_map(map);
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