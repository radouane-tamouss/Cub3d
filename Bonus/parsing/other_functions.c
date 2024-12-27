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

void	check_door_left_and_right_should_be_wall(t_game *game)
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
			if (game->map.grid[i][j] == 'D')
			{
				if (game->map.grid[i][j - 1] != '1' || game->map.grid[i][j
					+ 1] != '1')
				{
					printf("Error: Door should be surrounded by walls\n");
					exiter(1);
				}
			}
			j++;
		}
		i++;
	}
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
