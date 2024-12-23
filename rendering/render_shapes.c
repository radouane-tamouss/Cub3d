/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:51:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/23 15:09:11 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	render_cyrcle(int x, int y, int radius, int color)
{
	int	i;
	int	j;

	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (j * j + i * i <= radius * radius)
				put_pixel(&(get_data()->background_img), x + j, y + i, color);
			++j;
		}
		++i;
	}
}

void	render_square(int x, int y, int color)
{
	t_vector	center;
	int			i;
	int			j;

	center.x = 5 * SQUARE_SIZE;
	center.y = 5 * SQUARE_SIZE;
	i = 0;
	while (i < SQUARE_SIZE)
	{
		j = 0;
		while (j < SQUARE_SIZE)
		{
			if (calc_dist(j + x, i + y, center) <= (5 * SQUARE_SIZE - 3))
				put_pixel(&(get_data()->background_img), j + x, i + y, color);
			++j;
		}
		++i;
	}
}

void	render_line(float x1, float y1, float x2, float y2)// TODO norm this
{
	float	max;
	float	x_step;
	float	y_step;
	int		i;

	max = ft_max(ft_abs(x2 - x1), ft_abs(y2 - y1));
	x_step = (x2 - x1) / max;
	y_step = (y2 - y1) / max;
	i = 0;
	while (i <= max)
	{
		put_pixel(&(get_data()->background_img), x1, y1, RED);
		x1 += x_step;
		y1 += y_step;
		++i;
	}
}
