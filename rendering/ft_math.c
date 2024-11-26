/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:49:10 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/26 18:51:12 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_power(int nbr, int power)
{
	int i = 0;
	int r = 1;
	while (i < power)
	{
		r *= nbr;
		i++;
	}
	return (r);
}

double	ft_abs(double nbr)
{
	return (((nbr >= 0) - (nbr < 0)) * nbr);
}

float	ft_min(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr2);
	return (nbr1);
}

float	ft_max(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr1);
	return (nbr2);
}
int calc_dist(int x, int y, t_vector point)
{
	int r;

	r = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
	return (r);
}

float calc_dist_f(float x, float y, t_vector point)
{
	float r;

	r = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
	return (r);
}

float	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

void	line_between_2points(t_vector point1,
				t_vector point2, int color)
{
	int	x;
	int	y;

	// if ((point1.x == -1 && point1.y == -1)
	// 	|| (point2.x == -1 && point2.y == -1))
	// 	return ;
	y = ft_max(ft_min(point1.y, point2.y), 0);
	while ((point2.y - point1.y) != 0
		&& y <= ft_max(point1.y, point2.y) && y < WIN_HEIGHT)
	{
		x = (((y - point1.y) * (point2.x - point1.x))
				/ (point2.y - point1.y)) + point1.x;
		put_pixel(&(get_data()->background_img), x, y++, color);
	}
	x = ft_max(ft_min(point1.x, point2.x), 0);
	while ((point2.x - point1.x) != 0
		&& x <= ft_max(point1.x, point2.x) && x < WIN_WIDTH)
	{
		y = (((point2.y - point1.y) * (x - point1.x))
				/ (point2.x - point1.x)) + point1.y;
		put_pixel(&(get_data()->background_img), x++, y, color);
	}
}
