/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:33:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/23 13:48:21 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
// this will put backgrouind image to the window
void	render_background(void)
{
	mlx_put_image_to_window(get_data()->mlx, get_data()->win,
		get_data()->background_img.img, 0, 0);
}

/* this will create the background img
by putting colors of cieling and floor to it */
void	init_background(void)
{
	int			x;
	int			y;
	int			color;
	float		shift_value;
	t_texture	ceiling_tex;

	ceiling_tex = get_data()->ceiling_img;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
			{
				// Use ceiling texture for the ceiling
				color = pull_pixel(ceiling_tex, 
					x % ceiling_tex.width, 
					((float)y / (WIN_HEIGHT / 2)) * ceiling_tex.height);
			}
			else
			{
				color = get_data()->floor_color;
				shift_value = (float)(y - (WIN_HEIGHT / 2)) / (WIN_HEIGHT / 2);
				if (get_data()->dark_mode)
					color = create_trgb(0, ((int)(get_r(color) * shift_value)),
							((int)(get_g(color) * shift_value)),
							((int)(get_b(color) * shift_value)));
			}
			put_pixel(&(get_data()->background_img), x, y, color);
		}
	}
}
