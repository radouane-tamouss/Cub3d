/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:40:25 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 21:40:29 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off
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
	char	**rgb;

	check_for_null_pointers(color, color_struct);
	count_commas_and_validate_basic_format(color, color_struct);
	rgb = ft_split2(color, ",");
	split_and_trime_whitespaces(rgb, color);
	color_struct->r = ft_atoi(rgb[0]);
	color_struct->g = ft_atoi(rgb[1]);
	color_struct->b = ft_atoi(rgb[2]);
	if (color_struct->r < 0 || color_struct->r > 255 || color_struct->g < 0
		|| color_struct->g > 255 || color_struct->b < 0
		|| color_struct->b > 255)
	{
		printf("Error: RGB values must be between 0 and 255\n");
		exiter(1);
	}
}

void	check_ceiling_color(t_game *game, char **split)
{
	if (game->ceiling.color != NULL)
	{
		printf("error duplicate ceiling color\n");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing color for ceiling\n");
		exiter(1);
	}
	game->ceiling.color = ft_strdup(split[1]);
	parse_color(game->ceiling.color, &game->ceiling);
}

void	check_floor_color(t_game *game, char **split)
{
	if (game->floor.color != NULL)
	{
		printf("error duplicate floor color\n");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		printf("Error: Missing color for floor\n");
		exiter(1);
	}
	game->floor.color = ft_strdup(split[1]);
	parse_color(game->floor.color, &game->floor);
}

void	count_commas_and_validate_basic_format(char *color,
		t_color *color_struct)
{
	int	count;
	int	i;

	count = ft_count_commas(color);
	(void) color_struct;
	if (count != 2)
	{
		printf("Error: Color must have exactly 2 commas (R,G,B format)\n");
		exiter(1);
	}
	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',' && !ft_isspace(color[i]))
		{
			printf("Error: Invalid character in color format\n");
			exiter(1);
		}
		i++;
	}
}
