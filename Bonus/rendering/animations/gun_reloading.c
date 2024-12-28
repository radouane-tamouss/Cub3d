/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_reloading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:45:31 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 02:20:14 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

// clang-format off
void	render_reloading(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.frame_delay++ >= RELOADING_FRAME_DELAY)
	{
		data->gun.frame_delay = 1;
		data->gun.current_frame++;
		if (data->gun.current_frame >= 12)
		{
			data->gun.current_frame = 0;
			data->gun.is_shooting = 0;
			data->gun.is_reloading = 0;
		}
	}
	render_transparent_frame(
		data->gun.reloading_frames[data->gun.current_frame],
		data->gun.width, data->gun.height);
	data->number_of_shoots = 0;
}

void	reload_gun_when_empty(void)
{
	if (get_data()->number_of_shoots >= 8)
	{
		get_data()->gun.is_reloading = 1;
		render_reloading();
		return ;
	}
}

void	render_frirst_gun_frame(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun.show_scope && !data->gun.is_reloading
		&& !data->gun.is_shooting)
	{
		render_transparent_frame(
			data->gun.first_scope_frames[data->gun.current_frame],
			data->gun.width, data->gun.height);
		return ;
	}
}

void	render_last_frame_gun(void)
{
	t_data	*data;

	data = get_data();
	if (!data->gun.show_scope && !data->gun.is_reloading
		&& !data->gun.is_shooting && !data->is_running)
	{
		data->gun.current_frame = 4;
		render_transparent_frame(
			data->gun.last_scope_frames[data->gun.current_frame],
			data->gun.width, data->gun.height);
		return ;
	}
}
