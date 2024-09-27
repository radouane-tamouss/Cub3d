/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:33:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/17 23:39:34 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// this will put backgrouind image to the window
void	render_background(void)
{
	mlx_put_image_to_window(get_data()->mlx,
		get_data()->win,
		get_data()->background_img.img, 0, 0);
}

//this will create the background img by putting colors of cieling and floor to it
void	create_background(void)
{
	int	x;
	int	y;
	int	color;

	get_data()->background_img.img = mlx_new_image(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);// TODO protect failing
		get_data()->background_img.addr = mlx_get_data_addr(get_data()->background_img.img,
			&(get_data()->background_img.bits_per_pixel), &(get_data()->background_img.line_length),
			&(get_data()->background_img.endian)); // TODO protect failing
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
				color = get_data()->ceiling_color;
			else
				color = get_data()->floor_color;
			put_pixel(&(get_data()->background_img), x, y, color);
			x++;
		}
		y++;
	}
}