/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:33:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/15 22:59:38 by eouhrich         ###   ########.fr       */
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

/* this will create the background img
by putting colors of cieling and floor to it */
void	init_background(void)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
				color = get_data()->ceiling_color;
			else
			{
				color = get_data()->floor_color;
				if (get_data()->dark_mode)
					color = CREATE_TRGB(0,
							((int)(GET_R(color) * ((float)(y - (WIN_HEIGHT / 2)) / (float)(WIN_HEIGHT / 2)))),
							((int)(GET_G(color) * ((float)(y - (WIN_HEIGHT / 2)) / (float)(WIN_HEIGHT / 2)))),
							((int)(GET_B(color) * ((float)(y - (WIN_HEIGHT / 2)) / (float)(WIN_HEIGHT / 2)))));
			}
			put_pixel(&(get_data()->background_img), x, y, color);
			++x;
		}
		++y;
	}
}
