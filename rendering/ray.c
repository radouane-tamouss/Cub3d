/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:35:58 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/06 02:49:01 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// this init the direction (vector) of the ray
void	init_ray_dir(t_ray_data *ray, float ray_angle)
{
	ray->angle = ray_angle;
	ray->ray_dir.x = cos(ray_angle);
	ray->ray_dir.y = sin(ray_angle);
	ray->map_x = (int)(get_data()->player_pos.x / GRID_DIST);
	ray->map_y = (int)(get_data()->player_pos.y / GRID_DIST);
}

// calc the delta that we need to travel to hit the intersact with the next line of grid
void	calc_delta_dist(t_ray_data *ray)
{
	ray->delta_dist.x = ft_abs(1 / ray->ray_dir.x);
	ray->delta_dist.y = ft_abs(1 / ray->ray_dir.y);
}

//calc the distance need to travel from intersection to another 
void	calc_step_and_side_dist(t_ray_data *ray)
{
	float	player_x;
	float	player_y;

	player_x = get_data()->player_pos.x / GRID_DIST;
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (player_x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - player_x) * ray->delta_dist.x;
	}
	player_y = get_data()->player_pos.y / GRID_DIST;
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (player_y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - player_y) * ray->delta_dist.y;
	}
}

void	calculate_ray_distance(t_ray_data *ray)
{
	if (ray->side == 0)
		ray->dist = (ray->side_dist.x - ray->delta_dist.x) * GRID_DIST;
	else
		ray->dist = (ray->side_dist.y - ray->delta_dist.y) * GRID_DIST;
}

t_ray_data	create_ray(float angle)
{
	t_ray_data	ray;

	init_ray_dir(&ray, angle);
	calc_delta_dist(&ray);
	calc_step_and_side_dist(&ray);
	return (ray);
}
