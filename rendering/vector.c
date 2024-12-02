/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:32:00 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/02 19:27:21 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	calc_dist(int x, int y, t_vector point)
{
	int	r;

	r = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
	return (r);
}

float	calc_dist_f(float x, float y, t_vector point)
{
	float	r;

	r = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
	return (r);
}

float	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float	vector_magnitude(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y));
}

// t_vector	normalise_vector(t_vector vector)
// {
// 	float	magnitude;

// 	magnitude = vector_magnitude(vector);
// 	vector.x = vector.x / magnitude;
// 	vector.y = vector.y / magnitude;
// 	return	(vector);
// }


