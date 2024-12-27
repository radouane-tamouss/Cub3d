/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_gun_frames.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:33:32 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:50:48 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	load_shooting_gun3_frames(void)
{
	t_data	*data;
	char	*frame_paths[15];
	int		i;

	initialize_gun3shoot_frames_paths(frame_paths);
	data = get_data();
	i = 0;
	while (i < 15)
	{
		data->gun.shooting_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun.width, &data->gun.height);
		i++;
	}
	data->gun.current_frame = 0;
	data->gun.frame_delay = 0;
	data->gun.is_reloading = 0;
	data->gun.is_shooting = 0;
	data->gun.shooted = 0;
	data->gun.show_scope = 0;
}

void	load_running_gun3_frames(void)
{
	t_data	*data;
	char	*frame_paths[11];
	int		i;

	data = get_data();
	initialize_running_gun3_frames_paths(frame_paths);
	i = 0;
	while (i < 11)
	{
		data->gun.running_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun.width, &data->gun.height);
		i++;
	}
	data->gun.current_frame = 0;
	data->gun.frame_delay = 0;
}

void	load_reloading_gun3_frames(void)
{
	t_data	*data;
	char	*frame_paths[12];
	int		i;

	data = get_data();
	initialize_reloading_gun3_frames_paths(frame_paths);
	i = 0;
	while (i < 12)
	{
		data->gun.reloading_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun.width, &data->gun.height);
		i++;
	}
	data->gun.current_frame = 0;
	data->gun.frame_delay = 0;
	data->gun.is_reloading = 0;
	data->gun.is_shooting = 0;
	data->gun.shooted = 0;
}

void	load_walking_gun3_frames(void)
{
	t_data	*data;
	char	*frame_paths[11];
	int		i;

	initialize_walking_frames_paths(frame_paths);
	data = get_data();
	i = 0;
	while (i < 11)
	{
		data->gun.walking_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun.width, &data->gun.height);
		i++;
	}
	data->gun.current_frame = 0;
	data->gun.frame_delay = 0;
}
