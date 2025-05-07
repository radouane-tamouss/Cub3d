/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:56:43 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:56:46 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
void	handle_door_helper(int door_x, int door_y)
{
	door_x = get_data()->front_ray.map_x;
	door_y = get_data()->front_ray.map_y;
	if (get_data()->map[door_y][door_x] == 'D')
	{
		get_data()->map[door_y][door_x] = 'P';
		get_data()->door.is_opening = 1;
		get_data()->door.current_frame = 0;
		get_data()->door.frame_delay = 2;
	}
	else if (get_data()->map[door_y][door_x] == 'O')
	{
		get_data()->map[door_y][door_x] = 'P';
		get_data()->door.is_closing = 1;
		get_data()->door.current_frame = 16;
		get_data()->door.frame_delay = 0;
	}
}

void	decrease_zoom_factor(void)
{
	get_data()->zoom_factor -= 0.04;
	if (get_data()->zoom_factor < 0.7)
		get_data()->zoom_factor = 0.7;
}

void	increase_zoom_factor(void)
{
	get_data()->zoom_factor += 0.04;
	if (get_data()->zoom_factor > 1)
		get_data()->zoom_factor = 1;
}

void	handle_door(int keycode)
{
	int	door_x;
	int	door_y;

	door_x = 0;
	door_y = 0;
	if (keycode == E_LIN)
	{
		if ((get_data()->front_ray.object_hitted == 'D'
				|| get_data()->front_ray.object_hitted == 'O')
			&& get_data()->front_ray.dist < 2 * GRID_DIST
			&& !get_data()->door.is_opening && !get_data()->door.is_closing)
			handle_door_helper(door_x, door_y);
	}
}
