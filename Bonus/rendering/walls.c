/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:25:16 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/22 18:48:21 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_col(t_ray_data ray, int col)
{
	int	start;
	int	end;
	int	i;

	ray.wall_height = (GRID_DIST / (ray.dist * cos(ray.angle
					- get_data()->player_angle))) * ((WIN_WIDTH / 2) / tan((FOV
					* get_data()->zoom_factor) / 2));
	start = (WIN_HEIGHT - (int)ray.wall_height) / 2;
	end = start + (int)ray.wall_height;
	if (start < 0)
		start = 0;
	if (end > WIN_HEIGHT)
		end = WIN_HEIGHT;
	i = start;
	while (i < end)
	{
		put_pixel(&(get_data()->background_img), col, i,
			calc_color(ray, start, i, end));
		i++;
	}
}

void	collect_front_ray_data(t_ray_data *ray, char current_tile
	, int *data_taken)
{
	ray->object_hitted = current_tile;
	if (!(*data_taken) && ray->angle == get_data()->player_angle)
	{
		get_data()->front_ray = *ray;
		calculate_ray_distance(&(get_data()->front_ray));
		(*data_taken) = 1;
	}
}

int	check_hitting_object(t_ray_data *ray, char current_tile
	, int data_taken, int col)
{
	if (current_tile == '1')
		collect_front_ray_data(ray, current_tile, &data_taken);
	else if (current_tile == 'P')
	{
		collect_front_ray_data(ray, current_tile, &data_taken);
		perform_dda(*ray, data_taken, col);
	}
	else if (current_tile == 'D')
		collect_front_ray_data(ray, current_tile, &data_taken);
	else if (current_tile == 'O')
	{
		collect_front_ray_data(ray, current_tile, &data_taken);
		perform_dda(*ray, data_taken, col);
	}
	else
		return (0);
	return (1);
}

void	perform_dda(t_ray_data ray, int data_taken, int col)
{
	while (1)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (check_hitting_object(&ray, get_data()->map[ray.map_y][ray.map_x]
			, data_taken, col))
		{
			calculate_ray_distance(&ray);
			draw_col(ray, col);
			return ;
		}
	}
}

void	render_walls(void)
{
	int		col;
	float	ray_angle;

	col = 0;
	while (col < WIN_WIDTH)
	{
		ray_angle = normalise_angle(get_data()->player_angle
				- ((FOV * get_data()->zoom_factor) / 2)
				+ (col * ((FOV * get_data()->zoom_factor) / WIN_WIDTH)));
		perform_dda(create_ray(ray_angle), 0, col);
		++col;
	}
}
