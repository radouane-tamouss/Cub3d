/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:33:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/25 11:40:41 by rtamouss         ###   ########.fr       */
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
void	init_background()
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
			{
				color = get_data()->ceiling_color;
				// color = CREATE_TRGB(0,
					// (GET_R(color) - (int)(GET_R(color) * ((float)y / (float)(WIN_HEIGHT/2)))),
					// (GET_G(color) - (int)(GET_G(color) * ((float)y / (float)(WIN_HEIGHT/2)))),
					// (GET_B(color) - (int)(GET_B(color) * ((float)y / (float)(WIN_HEIGHT/2)))));
			}
			else
			{
				color = get_data()->floor_color;
				if (get_data()->dark_mode)
					color = CREATE_TRGB(0,
						((int)(GET_R(color) * ((float)(y - (WIN_HEIGHT/2)) / (float)(WIN_HEIGHT/2)))),
						((int)(GET_G(color) * ((float)(y - (WIN_HEIGHT/2)) / (float)(WIN_HEIGHT/2)))),
						((int)(GET_B(color) * ((float)(y - (WIN_HEIGHT/2)) / (float)(WIN_HEIGHT/2)))));
			}
			put_pixel(&(get_data()->background_img), x, y, color);
			x++;
		}
		y++;
	}
}
