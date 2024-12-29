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

// Helper function to convert string to integer while handling spaces
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
		print_err("RGB values must be between 0 and 255");
		exiter(1);
	}
}

void	check_ceiling_color(t_game *game, char **split)
{
	char	*joined_color;
	char	*temp;
	int		i;

	if (game->ceiling.color != NULL)
	{
		print_err("Duplicate ceiling color");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		print_err("Missing color for ceiling");
		exiter(1);
	}
	joined_color = ft_strdup(split[1]);
	i = 2;
	while (split[i] != NULL)
	{
		temp = ft_strjoin(joined_color, " ");
		joined_color = ft_strjoin(temp, split[i]);
		i++;
	}
	game->ceiling.color = ft_strdup(joined_color);
	parse_color(game->ceiling.color, &game->ceiling);
}

void	check_floor_color(t_game *game, char **split)
{
	char	*joined_color;
	char	*temp;
	int		i;

	if (game->floor.color != NULL)
	{
		print_err("Duplicate floor color");
		exiter(1);
	}
	if (split[1] == NULL)
	{
		print_err("Missing color for floor");
		exiter(1);
	}
	joined_color = ft_strdup(split[1]);
	i = 2;
	while (split[i] != NULL)
	{
		temp = ft_strjoin(joined_color, " ");
		joined_color = ft_strjoin(temp, split[i]);
		i++;
	}
	game->floor.color = ft_strdup(joined_color);
	parse_color(game->floor.color, &game->floor);
}

void	count_commas_and_validate_basic_format(char *color,
		t_color *color_struct)
{
	int	count;
	int	i;

	(void) color_struct;
	count = ft_count_commas(color);
	if (count != 2)
	{
		print_err("Color must have exactly 2 commas (R,G,B format)");
		exiter(1);
	}
	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',' && !ft_isspace(color[i]))
		{
			print_err("Invalid character in color format");
			exiter(1);
		}
		i++;
	}
}
