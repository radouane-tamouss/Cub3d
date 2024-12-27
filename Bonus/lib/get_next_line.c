/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:09:56 by rtamouss          #+#    #+#             */
/*   Updated: 2024/02/19 19:20:52 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc(i + 2, 1);
	else if (buffer[i] == 0)
		line = ft_calloc(i + 1, 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	return (line);
}

char	*ft_rest(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free_ptr(str);
		return (0);
	}
	temp = (char *)mallocate(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!temp)
		return (0);
	i++;
	while (str[i])
		temp[j++] = str[i++];
	temp[j] = '\0';
	free_ptr(str);
	return (temp);
}

char	*join_and_free(char *result, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(result, buffer);
	free_ptr(result);
	return (temp);
}

char	*read_file(int fd, char *result)
{
	char	*buffer;
	int		bytesread;

	bytesread = 1;
	if (!result)
		result = ft_calloc(1, 1);
	buffer = mallocate(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free_ptr(buffer);
			free_ptr(result);
			return (NULL);
		}
		buffer[bytesread] = 0;
		result = join_and_free(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free_ptr(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	stock = read_file(fd, stock);
	if (!stock)
		return (NULL);
	line = ft_get_line(stock);
	stock = ft_rest(stock);
	return (line);
}

// int main()
// {
// 	int fd = open("map3.ber", O_RDONLY);
// 	char *line;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }