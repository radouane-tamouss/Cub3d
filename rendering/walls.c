/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:13:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/01 02:29:59 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float nearest_y_wall(float ray_angle)
{
	// float	dist;
	t_vector first_point;
	
	if (ray_angle >= 0 && ray_angle <= MY_PI)
		first_point.y = round(get_data()->player_pos.y / GRID_DIST) * GRID_DIST;
	else
		first_point.y = floor(get_data()->player_pos.y / GRID_DIST) * GRID_DIST;
	if(ray_angle <= (MY_PI / 2) && ray_angle >= - (MY_PI / 2))
		first_point.x = get_data()->player_pos.x - ft_abs(first_point.y - get_data()->player_pos.y) / tan(ray_angle);
	else
		first_point.x =  get_data()->player_pos.x + ft_abs(first_point.y - get_data()->player_pos.y) / tan(ray_angle);

	while (1)// TODO add if x and y are outside of the map
	{
		// fprintf(stderr, " find y wall == first_point.y / GRID_DIST ==> %d, first_point.x / GRID_DIST == > %d || map = %c\n", (int)(first_point.y / GRID_DIST), (int)(first_point.x / GRID_DIST), get_data()->map[(int)(first_point.y / GRID_DIST)][(int)(first_point.x / GRID_DIST)]);
		if ((int)(first_point.y / GRID_DIST) < 0 || (int)(first_point.x / GRID_DIST) < 0||  (int)(first_point.y / GRID_DIST) >= get_data()->height || (int)(first_point.x / GRID_DIST) >= get_data()->width)
		{
			fprintf(stderr, "out of border\n");
			return ((float)INT_MAX);
		}
		if (get_data()->map[(int)(first_point.y / GRID_DIST)][(int)(first_point.x / GRID_DIST)] == '1')
		{
			fprintf(stderr, " ========== found y wall ======================\n");	
			return (calc_dist(first_point.x, first_point.y, get_data()->player_pos));
		}
		if (ray_angle >= 0 && ray_angle <= MY_PI)
			first_point.y += GRID_DIST;
		else
			first_point.y -= GRID_DIST;
		if(ray_angle <= (MY_PI / 2) && ray_angle >= - (MY_PI / 2))
			first_point.x += GRID_DIST / tan(ray_angle);
		else
			first_point.x -= GRID_DIST / tan(ray_angle);
	}
	
	// return (dist);
}


float nearest_x_wall(float ray_angle)
{
	// float	dist;
	t_vector first_point;
	
	if (ray_angle <= (MY_PI / 2) && ray_angle >= -(MY_PI / 2))
		first_point.x = round(get_data()->player_pos.x / GRID_DIST) * GRID_DIST;
	else
		first_point.x = floor(get_data()->player_pos.x / GRID_DIST) * GRID_DIST;
	if(ray_angle >= 0 && ray_angle <= MY_PI)
		first_point.y = get_data()->player_pos.y + ft_abs(first_point.x - get_data()->player_pos.x) * tan(ray_angle);
	else
		first_point.y =  get_data()->player_pos.y - ft_abs(first_point.x - get_data()->player_pos.x) * tan(ray_angle);

	while (1)// TODO add if x and y are outside of the map
	{
		// fprintf(stderr, "first_point.y / GRID_DIST ==> %d, first_point.x / GRID_DIST == > %d || map = %c\n", (int)(first_point.y / GRID_DIST), (int)(first_point.x / GRID_DIST), get_data()->map[(int)(first_point.y / GRID_DIST)][(int)(first_point.x / GRID_DIST)]);
		if ((int)(first_point.y / GRID_DIST) < 0 || (int)(first_point.x / GRID_DIST) < 0||  (int)(first_point.y / GRID_DIST) >= get_data()->height || (int)(first_point.x / GRID_DIST) >= get_data()->width)
		{
			fprintf(stderr, "out of border\n");
			return ((float)INT_MAX);
		}
		if (get_data()->map[(int)(first_point.y / GRID_DIST)][(int)(first_point.x / GRID_DIST)] == '1')
		{
			fprintf(stderr, " ========== found x wall ======================\n");
			return (calc_dist(first_point.x, first_point.y, get_data()->player_pos));
		}
		if (ray_angle <= (MY_PI / 2) && ray_angle >= -(MY_PI / 2))
			first_point.x += GRID_DIST;
		else
			first_point.x -= GRID_DIST;
		if(ray_angle >= 0 && ray_angle <= MY_PI)
			first_point.y += GRID_DIST * tan(ray_angle);
		else
			first_point.y -= GRID_DIST * tan(ray_angle);
	}
	
	// return (dist);
}

void	draw_col(float dist, int col)
{
	int	i;
	
	float projected ;
	if (dist != 0)
		projected = (GRID_DIST / dist) * ZOOM * 5;
	else
		projected =  WIN_HEIGHT / 2;
		
	i = WIN_HEIGHT/2 - projected;
	fprintf(stderr, "dist %f\n", dist / GRID_DIST);
	fprintf(stderr, "projected %f\n", projected);
	while (i < WIN_HEIGHT/2 + projected)
	{
		// fprintf(stderr, "drawin to (%d, %d)\n",i, col);
		put_pixel(&(get_data()->background_img), col, i, RED);
		i++;
	}
}

void	cast_ray(float col)
{
	float	ray_angle;

	ray_angle = get_data()->player_angle - (FOV/2) + (col * (FOV/WIN_WIDTH));

	float	dist_x;
	float	dist_y;
	fprintf(stderr, "\n\n\tray_angle == %f\n", ray_angle * (180 / MY_PI));
	dist_x = nearest_x_wall(ray_angle);
	dist_y = nearest_y_wall(ray_angle);


	fprintf(stderr, "dist_x %f , dist_y %f\n", dist_x / GRID_DIST, dist_y/ GRID_DIST);
	draw_col(ft_min(dist_x, dist_y), col);
}

void	render_walls(void)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		cast_ray(i);//render the colm
		i++;
	}
}
