/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scope.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:41:15 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 02:20:28 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

// clang-format off
void	render_show_scope_frames(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.frame_delay++ >= SHOW_SCOPE_FRAME_DELAY)
	{
		data->gun.frame_delay = 1;
		data->gun.current_frame++;
		data->zoom_factor -= 0.08;
		if (data->gun.current_frame >= 5)
		{
			data->gun.current_frame = 5;
			data->gun.is_showing_scope = 0;
			data->zoom_factor += 0.04;
		}
	}
	render_transparent_frame(
		data->gun.first_scope_frames[data->gun.current_frame],
		data->gun.width, data->gun.height);
}

void	render_unshowing_scope(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.frame_delay++ >= SHOW_SCOPE_FRAME_DELAY)
	{
		data->gun.frame_delay = 1;
		data->gun.current_frame++;
		data->zoom_factor += 0.09;
		if (data->gun.current_frame >= 4)
		{
			data->gun.current_frame = 4;
			data->gun.is_showing_scope = 0;
		}
	}
	render_transparent_frame(
		data->gun.last_scope_frames[data->gun.current_frame],
		data->gun.width, data->gun.height);
}

void	render_scope_shooting_frames(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.frame_delay++ >= SHOOTING_FRAME_DELAY)
	{
		data->gun.frame_delay = 1;
		data->gun.current_frame++;
		if (data->gun.current_frame >= 6)
		{
			data->gun.current_frame = 5;
			data->gun.is_shooting = 0;
			data->gun.is_reloading = 0;
		}
	}
	render_transparent_frame(
		data->gun.scope_shooting_frames[data->gun.current_frame],
		data->gun.width, data->gun.height);
	render_frame();
}

void	handle_shooting_animation(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.show_scope == 1)
		render_scope_shooting_frames();
	else
		render_shootin_frames();
}
