/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scope_frames.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:35:29 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:36:17 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
void	load_shooting_scope_frames(void)
{
	t_data	*data;
	char	*frame_paths[6];
	int		i;

	initialize_zoom_shoot_frames_paths(frame_paths);
	data = get_data();
	i = 0;
	i = 0;
	while (i < 6)
	{
		data->gun.scope_shooting_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun.width, &data->gun.height);
		i++;
	}
	data->gun.current_frame = 4;
	data->gun.frame_delay = 0;
	data->gun.is_reloading = 0;
	data->gun.is_shooting = 0;
	data->gun.shooted = 0;
	data->gun.is_showing_scope = 0;
	data->gun.is_showing_scope = 0;
}

void	load_last_scope_frames(void)
{
	t_data	*data;
	char	*frame_paths[5];
	int		i;

	data = get_data();
	initialize_last_scope_frames_paths(frame_paths);
	i = 0;
	while (i < 5)
	{
		data->gun.last_scope_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun.width, &data->gun.height);
		i++;
	}
	data->gun.current_frame = 4;
	data->gun.frame_delay = 0;
	data->gun.is_reloading = 0;
	data->gun.is_shooting = 0;
	data->gun.shooted = 0;
	data->gun.is_showing_scope = 0;
}

void	load_first_scope_frames(void)
{
	t_data	*data;
	char	*frame_paths[6];
	int		i;

	initialize_first_scope_frames_paths(frame_paths);
	data = get_data();
	i = 0;
	while (i < 6)
	{
		data->gun.first_scope_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun.width, &data->gun.height);
		i++;
	}
	data->gun.current_frame = 0;
	data->gun.frame_delay = 0;
	data->gun.is_reloading = 0;
	data->gun.is_shooting = 0;
	data->gun.shooted = 0;
	data->gun.is_showing_scope = 0;
}
