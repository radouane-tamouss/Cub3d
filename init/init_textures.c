/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:48:41 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/29 01:48:41 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cube.h"

// clang-format off
void	init_west_east_textures(t_game *game)
{
	t_data	*data;

	data = get_data();
	data->east_img.img_data.img
		= safer_xpm_file_to_image(data->mlx,
			game->east.path, &(data->east_img.width), &(data->east_img.height));
	data->east_img.img_data.addr
		= safer_get_data_addr(data->east_img.img_data.img,
			&(data->east_img.img_data.bits_per_pixel),
			&(data->east_img.img_data.line_length),
			&(data->east_img.img_data.endian));
	data->west_img.img_data.img
		= safer_xpm_file_to_image(data->mlx,
			game->west.path, &(data->west_img.width), &(data->west_img.height));
	data->west_img.img_data.addr
		= safer_get_data_addr(data->west_img.img_data.img,
			&(data->west_img.img_data.bits_per_pixel),
			&(data->west_img.img_data.line_length),
			&(data->west_img.img_data.endian));
}

void	init_direction(t_game *game)
{
	t_data	*data;

	data = get_data();
	if (data->player_direction == 'E')
		data->player_angle = 0.0;
	else if (data->player_direction == 'S')
		data->player_angle = MY_PI / 2;
	else if (data->player_direction == 'W')
		data->player_angle = MY_PI;
	else if (data->player_direction == 'N')
		data->player_angle = 3 * MY_PI / 2;
	else
		data->player_angle = 0.0;
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
	data->south_img.img_data.img
		= safer_xpm_file_to_image(data->mlx,
			game->south.path, &(data->south_img.width),
			&(data->south_img.height));
	data->south_img.img_data.addr
		= safer_get_data_addr(data->south_img.img_data.img,
			&(data->south_img.img_data.bits_per_pixel),
			&(data->south_img.img_data.line_length),
			&(data->south_img.img_data.endian));
}
