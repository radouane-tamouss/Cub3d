/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:10:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:49:29 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	initialize_door_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/door_frames/1.xpm";
	frame_paths[1] = "textures/door_frames/2.xpm";
	frame_paths[2] = "textures/door_frames/3.xpm";
	frame_paths[3] = "textures/door_frames/4.xpm";
	frame_paths[4] = "textures/door_frames/5.xpm";
	frame_paths[5] = "textures/door_frames/6.xpm";
	frame_paths[6] = "textures/door_frames/7.xpm";
	frame_paths[7] = "textures/door_frames/8.xpm";
	frame_paths[8] = "textures/door_frames/9.xpm";
	frame_paths[9] = "textures/door_frames/10.xpm";
	frame_paths[10] = "textures/door_frames/11.xpm";
	frame_paths[11] = "textures/door_frames/12.xpm";
	frame_paths[12] = "textures/door_frames/13.xpm";
	frame_paths[13] = "textures/door_frames/14.xpm";
	frame_paths[14] = "textures/door_frames/15.xpm";
	frame_paths[15] = "textures/door_frames/16.xpm";
	frame_paths[16] = "textures/door_frames/17.xpm";
}

void	load_door_frames(void)
{
	t_data	*data;
	char	*frame_paths[17];
	int		i;

	initialize_door_frames_paths(frame_paths);
	data = get_data();
	i = -1;
	while (++i < 17)
	{
		data->door.images[i].img_data.img = safer_xpm_file_to_image(data->mlx,
				frame_paths[i],
				&data->door.images[i].width, &data->door.images[i].height);
		data->door.images[i].img_data.addr
			= safer_get_data_addr(data->door.images[i].img_data.img,
				&(data->door.images[i].img_data.bits_per_pixel),
				&(data->door.images[i].img_data.line_length),
				&(data->door.images[i].img_data.endian));
	}
	data->door.current_frame = 0;
	data->door.frame_delay = 0;
	data->door.is_opening = 0;
	data->door.is_open = 0;
	data->door.is_closed = 1;
	data->door.active_x = 0;
	data->door.active_y = 0;
}

void	init_door_textures_helper(void)
{
	t_data	*data;

	data = get_data();
	data->door_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			"textures/door_frames/1.xpm", &(data->door_img.width),
			&(data->door_img.height));
	data->door_img.img_data.addr
		= safer_get_data_addr(data->door_img.img_data.img,
			&(data->door_img.img_data.bits_per_pixel),
			&(data->door_img.img_data.line_length),
			&(data->door_img.img_data.endian));
}

void	init_door_textures(void)
{
	t_data	*data;

	data = get_data();
	init_door_textures_helper();
	data->door_open_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			"textures/door_frames/17.xpm", &(data->door_open_img.width),
			&(data->door_open_img.height));
	data->door_open_img.img_data.addr
		= safer_get_data_addr(data->door_open_img.img_data.img,
			&(data->door_open_img.img_data.bits_per_pixel),
			&(data->door_open_img.img_data.line_length),
			&(data->door_open_img.img_data.endian));
}
