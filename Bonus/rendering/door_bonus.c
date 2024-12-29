/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:12:31 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:47:01 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
void	render_closing_door(int door_x, int door_y)
{
	t_data	*data;

	data = get_data();
	if (data->door.frame_delay++ >= DOOR_FRAME_DELAY)
	{
		data->door.frame_delay = 0;
		data->door.current_frame--;
		if (data->door.current_frame <= 0)
		{
			data->door.current_frame = 0;
			data->door.is_closing = 0;
			data->door.is_open = 0;
			data->door.is_closed = 1;
			data->map[door_y][door_x] = 'D';
		}
	}
}

void	render_opening_door(int door_x, int door_y)
{
	t_data	*data;

	data = get_data();
	if (data->door.frame_delay++ >= DOOR_FRAME_DELAY)
	{
		data->door.frame_delay = 0;
		data->door.current_frame++;
		if (data->door.current_frame > 16)
		{
			data->door.current_frame = 16;
			data->door.is_opening = 0;
			data->door.is_open = 1;
			data->map[door_y][door_x] = 'O';
		}
	}
}

int	find_door_position(int *door_x, int *door_y)
{
	int	found;
	int	y;
	int	x;

	found = 0;
	y = 0;
	while (y < get_data()->height && !found)
	{
		x = 0;
		while (x < get_data()->width && !found)
		{
			if (get_data()->map[y][x] == 'P')
			{
				*door_x = x;
				*door_y = y;
				found = 1;
			}
			x++;
		}
		y++;
	}
	return (found);
}

void	update_door_animation(void)
{
	int	found;
	int	door_x;
	int	door_y;

	found = 0;
	door_x = 0;
	door_y = 0;
	found = find_door_position(&door_x, &door_y);
	if (!found)
		return ;
	if (get_data()->door.is_opening)
		render_opening_door(door_x, door_y);
	else if (get_data()->door.is_closing)
		render_closing_door(door_x, door_y);
}
