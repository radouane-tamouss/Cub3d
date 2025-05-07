/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:17:01 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 02:01:53 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
void	init_west_east_textures(t_game *game)
{
	t_data	*data;

	data = get_data();
	data->east_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			game->east.path, &(data->east_img.width), &(data->east_img.height));
	data->east_img.img_data.addr
		= safer_get_data_addr(data->east_img.img_data.img,
			&(data->east_img.img_data.bits_per_pixel),
			&(data->east_img.img_data.line_length),
			&(data->east_img.img_data.endian));
	data->west_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			game->west.path, &(data->west_img.width), &(data->west_img.height));
	data->west_img.img_data.addr
		= safer_get_data_addr(data->west_img.img_data.img,
			&(data->west_img.img_data.bits_per_pixel),
			&(data->west_img.img_data.line_length),
			&(data->west_img.img_data.endian));
}

void	init_north_south_textures(t_game *game)
{
	t_data	*data;

	data = get_data();
	data->north_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			game->north.path, &(data->north_img.width),
			&(data->north_img.height));
	data->north_img.img_data.addr
		= safer_get_data_addr(data->north_img.img_data.img,
			&(data->north_img.img_data.bits_per_pixel),
			&(data->north_img.img_data.line_length),
			&(data->north_img.img_data.endian));
	data->south_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			game->south.path, &(data->south_img.width),
			&(data->south_img.height));
	data->south_img.img_data.addr
		= safer_get_data_addr(data->south_img.img_data.img,
			&(data->south_img.img_data.bits_per_pixel),
			&(data->south_img.img_data.line_length),
			&(data->south_img.img_data.endian));
}

void	init_ceiling_texture(void)
{
	t_data	*data;

	data = get_data();
	data->ceiling_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			"textures/wall.xpm", &(data->ceiling_img.width),
			&(data->ceiling_img.height));
	data->ceiling_img.img_data.addr
		= safer_get_data_addr(data->ceiling_img.img_data.img,
			&(data->ceiling_img.img_data.bits_per_pixel),
			&(data->ceiling_img.img_data.line_length),
			&(data->ceiling_img.img_data.endian));
}
