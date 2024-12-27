/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:46:39 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 21:46:44 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cube.h"

void	parse_north_texture(t_game *game, char **split)
{
	if (game->north.path != NULL)
	{
		printf("error duplicate north texture\n");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for north texture\n");
		exiter(1);
	}
	game->north.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->north.path);
}

void	parse_south_texture(t_game *game, char **split)
{
	if (game->south.path != NULL)
	{
		printf("error duplicate south texture\n");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for south texture\n");
		exiter(1);
	}
	game->south.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->south.path);
}

void	parse_west_texture(t_game *game, char **split)
{
	if (game->west.path != NULL)
	{
		printf("error duplicate west texture\n");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for west texture\n");
		exiter(1);
	}
	game->west.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->west.path);
}

void	parse_east_texture(t_game *game, char **split)
{
	if (game->east.path != NULL)
	{
		printf("error duplicate east texture\n");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing path for east texture\n");
		exiter(1);
	}
	game->east.path = ft_strdup(split[1]);
	check_file_exists_or_empty(game->east.path);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
