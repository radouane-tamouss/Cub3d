/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_and_color_infos.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:44:37 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/21 21:45:08 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off
void	split_and_trime_whitespaces(char **rgb, char *color)
{
	int	i;
	int	j;

	(void) color;
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		printf("here Error: Invalid color format\n");
		exiter(1);
	}
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]) && !ft_isspace(rgb[i][j]))
			{
				printf("Error: Invalid number in color format\n");
				exiter(1);
			}
			j++;
		}
		i++;
	}
}

void	check_for_null_pointers(char *color, t_color *color_struct)
{
	if (!color || !color_struct)
	{
		printf("Error: Invalid color parameters\n");
		exiter(1);
	}
}

void	validate_split(char **split)
{
	if (split == NULL || split[0] == NULL)
	{
		printf("Error: Invalid map\n");
		exiter(1);
	}
	else if (split[1] == NULL || split[2] != NULL)
	{
		printf("Error: Invalid Map\n");
		exiter(1);
	}
	if (check_file_extension(split[1]) == 0 && ft_strcmp(split[0], "F") != 0
		&& ft_strcmp(split[0], "C") != 0)
	{
		printf("Error: Invalid file extension\n");
		exiter(1);
	}
}

void	parse_texture_and_colors_info(char *line, t_game *game, t_map *map)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split2(line, " \t\r\n\v\f");
	(void) map;
	validate_split(split);
	if (ft_strcmp(split[0], "NO") == 0)
		parse_north_texture(game, split);
	else if (ft_strcmp(split[0], "SO") == 0)
		parse_south_texture(game, split);
	else if (ft_strcmp(split[0], "WE") == 0)
		parse_west_texture(game, split);
	else if (ft_strcmp(split[0], "EA") == 0)
		parse_east_texture(game, split);
	else if (ft_strcmp(split[0], "F") == 0)
		check_floor_color(game, split);
	else if (ft_strcmp(split[0], "C") == 0)
		check_ceiling_color(game, split);
	while (split[i])
	{
		free_ptr(split[i]);
		i++;
	}
	free_ptr(split);
}
