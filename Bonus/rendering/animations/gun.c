/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:20:27 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:46:43 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

// clang-format off
void	render_gun_frames(int num_frames, t_gun *gun, int frame_delay)
{
	if (gun->frame_delay++ >= frame_delay)
	{
		gun->frame_delay = 1;
		gun->current_frame++;
		if (gun->current_frame >= num_frames)
		{
			gun->current_frame = 0;
			gun->is_shooting = 0;
			gun->is_reloading = 0;
		}
	}
}

void	render_shootin_frames(void)
{
	t_data	*data;

	data = get_data();
	render_gun_frames(15, &data->gun, 6);
	if (data->gun.frame_delay++ >= 5)
	{
		data->gun.frame_delay = 1;
		data->gun.current_frame++;
		if (data->gun.current_frame >= 12)
		{
			data->gun.current_frame = 4;
			data->gun.is_shooting = 0;
			data->gun.is_reloading = 0;
		}
	}
	render_transparent_frame(
		data->gun.shooting_frames[data->gun.current_frame],
		data->gun.width, data->gun.height);
	render_frame();
}

void	render_walking(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.frame_delay++ >= 6)
	{
		data->gun.frame_delay = 0;
		data->gun.current_frame = (data->gun.current_frame + 1) % 11;
	}
	render_transparent_frame(
		data->gun.walking_frames[data->gun.current_frame],
		data->gun.width, data->gun.height);
}

void	render_running(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.frame_delay++ >= 10)
	{
		data->gun.frame_delay = 0;
		data->gun.current_frame = (data->gun.current_frame + 1) % 11;
	}
	render_transparent_frame(
		data->gun.running_frames[data->gun.current_frame],
		data->gun.width, data->gun.height);
}

void	render_gun(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.is_showing_scope)
	{
		if (data->gun.show_scope)
			return (render_show_scope_frames());
		else
			return (render_unshowing_scope());
	}
	if (data->gun.is_shooting)
		return (handle_shooting_animation());
	if (data->gun.is_reloading)
		return (render_reloading());
	reload_gun_when_empty();
	if (data->is_walking && !data->gun.show_scope)
		return (render_walking());
	if (data->is_running && !data->gun.show_scope)
		return (render_running());
	render_last_frame_gun();
	render_frirst_gun_frame();
	render_frame();
}
