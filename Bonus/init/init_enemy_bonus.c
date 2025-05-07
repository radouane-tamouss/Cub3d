/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:28:01 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:50:07 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
void	update_enemy_frames(void)
{
	int	i;

	i = 0;
	while (i < get_data()->num_sprites)
	{
		if (get_data()->sprites[i].frame_delay >= ENEMY_FRAME_DELAY)
		{
			get_data()->sprites[i].current_frame++;
			if (get_data()->sprites[i].current_frame >= 16)
				get_data()->sprites[i].current_frame = 0;
			get_data()->sprites[i].frame_delay = 0;
		}
		else
			get_data()->sprites[i].frame_delay++;
		i++;
	}
}

void	initialize_dying_zombie_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/dying_zombie/1.xpm";
	frame_paths[1] = "textures/dying_zombie/2.xpm";
	frame_paths[2] = "textures/dying_zombie/3.xpm";
	frame_paths[3] = "textures/dying_zombie/4.xpm";
	frame_paths[4] = "textures/dying_zombie/5.xpm";
	frame_paths[5] = "textures/dying_zombie/6.xpm";
	frame_paths[6] = "textures/dying_zombie/7.xpm";
	frame_paths[7] = "textures/dying_zombie/8.xpm";
	frame_paths[8] = "textures/dying_zombie/9.xpm";
	frame_paths[9] = "textures/dying_zombie/10.xpm";
	frame_paths[10] = "textures/dying_zombie/11.xpm";
	frame_paths[11] = "textures/dying_zombie/12.xpm";
	frame_paths[12] = "textures/dying_zombie/13.xpm";
	frame_paths[13] = "textures/dying_zombie/14.xpm";
	frame_paths[14] = "textures/dying_zombie/15.xpm";
}

void	load_dying_sprite_frames(void)
{
	t_data	*data;
	char	*frame_paths[15];
	int		i;

	initialize_dying_zombie_frames_paths(frame_paths);
	data = get_data();
	i = 0;
	while (i < 15)
	{
		data->dying_frames[i].img_data.img = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->dying_frames[i].width,
				&data->dying_frames[i].height);
		data->dying_frames[i].img_data.addr
			= safer_get_data_addr(data->dying_frames[i].img_data.img,
				&data->dying_frames[i].img_data.bits_per_pixel,
				&data->dying_frames[i].img_data.line_length,
				&data->dying_frames[i].img_data.endian);
		i++;
	}
}

void	initialize_load_sprite_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/zombie/1.xpm";
	frame_paths[1] = "textures/zombie/2.xpm";
	frame_paths[2] = "textures/zombie/3.xpm";
	frame_paths[3] = "textures/zombie/4.xpm";
	frame_paths[4] = "textures/zombie/5.xpm";
	frame_paths[5] = "textures/zombie/6.xpm";
	frame_paths[6] = "textures/zombie/7.xpm";
	frame_paths[7] = "textures/zombie/8.xpm";
	frame_paths[8] = "textures/zombie/9.xpm";
	frame_paths[9] = "textures/zombie/10.xpm";
	frame_paths[10] = "textures/zombie/11.xpm";
	frame_paths[11] = "textures/zombie/12.xpm";
	frame_paths[12] = "textures/zombie/13.xpm";
	frame_paths[13] = "textures/zombie/14.xpm";
	frame_paths[14] = "textures/zombie/15.xpm";
	frame_paths[15] = "textures/zombie/16.xpm";
}

void	load_load_sprite_frames(void)
{
	t_data	*data;
	char	*frame_paths[16];
	int		i;

	initialize_load_sprite_frames_paths(frame_paths);
	data = get_data();
	i = 0;
	while (i < 16)
	{
		data->sprites_frames[i].img_data.img
			= safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->sprites_frames[i].width,
				&data->sprites_frames[i].height);
		data->sprites_frames[i].img_data.addr
			= safer_get_data_addr(data->sprites_frames[i].img_data.img,
				&data->sprites_frames[i].img_data.bits_per_pixel,
				&data->sprites_frames[i].img_data.line_length,
				&data->sprites_frames[i].img_data.endian);
		i++;
	}
}
