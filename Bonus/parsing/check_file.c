/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:38:04 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 21:38:08 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off
int	check_file(char *str, int *fd)
{
	char	*res;
	ssize_t	bytes_read;
	char	buff[5];

	if (str == NULL)
		return (0);
	res = ft_strrchr(str, '.');
	if (res == NULL || ft_strcmp(res, ".cub") != 0 || ft_strlen(str) <= 4
		|| (ft_strlen(str) > 4 && str[ft_strlen(str) - 5] == '/'))
		return ((print_err("invalid file"), 0));
	*fd = open(str, O_RDONLY);
	if (*fd < 0)
		return (print_err("Open failed"), 0);
	bytes_read = read(*fd, &buff, 1);
	if (bytes_read == 0)
		return (print_err("File is empty"), 0);
	else if (bytes_read < 0)
		return (print_err("Read failed"), 0);
	return (1);
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

int	check_file_extension(char *str)
{
	char	*res;

	res = ft_strrchr(str, '.');
	if (res == NULL || ft_strcmp(res, ".xpm") != 0 || ft_strlen(str) <= 4)
		return (0);
	return (1);
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
		return (print_err("Read failed"), 0);
	close(fd);
	return (0);
}

void	check_file_exists_or_empty(char *file)
{
	int		fd;
	ssize_t	bytes_read;
	char	buff[5];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exiter(1);
	}
	bytes_read = read(fd, &buff, 1);
	if (bytes_read == 0)
	{
		printf("Error\nFile %s is empty\n", file);
		exiter(1);
	}
	else if (bytes_read < 0)
	{
		print_err("Read failed");
		exiter(1);
	}
	close(fd);
}
