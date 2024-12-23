/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:10:15 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/18 18:10:15 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "garbage_collector/heap_controller.h"

// clang-format off
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
// clan-format off

int	init_dest_src_y_data(int **dest_data, int **src_data, t_img_data *dest,
		t_img_data *src)
{
	int	y;

	y = -1;
	*dest_data = (int *)dest->addr;
	*src_data = (int *)src->addr;
	return (y);
}

void	put_xpm_image(t_img_data *dest, t_img_data *src, int start_x,
		int start_y)
{
	int	y;
	int	x;
	int	src_pixel;
	int	*dest_data;
	int	*src_data;

	if (!dest || !src || !dest->addr || !src->addr)
		return ;
	y = init_dest_src_y_data(&dest_data, &src_data, dest, src);
	while (++y < src->height)
	{
		if ((start_y + y) < 0 || (start_y + y) >= WIN_HEIGHT)
			continue ;
		x = -1;
		while (++x < src->width)
		{
			if ((start_x + x) < 0 || (start_x + x) >= WIN_WIDTH)
				continue ;
			src_pixel = src_data[y * (dest->line_length / 4) + x];
			if ((src_pixel & 0x00FFFFFF) == 0)
				continue ;
			dest_data[(start_y + y) * (src->line_length / 4)
				+ (start_x + x)] = src_pixel;
		}
	}
}

void	render_transparent_frame(void *frame_img, int width, int height)
{
	t_img_data	current_frame;
	int			pos_x;
	int			pos_y;

	if (!frame_img)
	{
		printf("frame_img is null\n");
		return ;
	}
	current_frame.img = frame_img;
	current_frame.width = width;
	current_frame.height = height;
	current_frame.addr = safer_get_data_addr(current_frame.img,
			&current_frame.bits_per_pixel, &current_frame.line_length,
			&current_frame.endian);
	pos_x = (WIN_WIDTH / 2 - width / 2) + (int)get_data()->gun_offset_x;
	pos_y = WIN_HEIGHT - height + 4;
	put_xpm_image(&get_data()->background_img, &current_frame, pos_x, pos_y);
}

void	render_gun_with_transparency(void)
{
	if (get_data()->gun.is_shooting)
	{
		if (get_data()->gun.frame_delay++ >= 14)
		{
			get_data()->gun.frame_delay = 0;
			get_data()->gun.current_frame++;
			if (get_data()->gun.current_frame >= 18)
			{
				get_data()->gun.current_frame = 0;
				get_data()->gun.is_shooting = 0;
			}
		}
	}
	render_transparent_frame(
		get_data()->gun.reloading_frames[get_data()->gun.current_frame],
		get_data()->gun.width, get_data()->gun.height);
}

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
	i = 0;
	while (i < 17)
	{
		data->door.img[i] = mlx_xpm_file_to_image(data->mlx, frame_paths[i],
				&data->door.width, &data->door.height);
		if (!data->door.img[i])
		{
			print_err("Failed to load door frame\n");
			exiter(1);
		}
		i++;
	}
	data->door.current_frame = 0;
	data->door.frame_delay = 0;
	data->door.is_opening = 0;
	data->door.is_open = 0;
	data->door.is_closed = 1;
	data->door.active_x = 0;
	data->door.active_y = 0;
}

void	init_data_helper(t_game *game)
{
	t_data	*data;

	data = get_data();
	if (data->mlx != NULL)
		data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");
	if (data->mlx == NULL || data->win == NULL)
	{
		print_err("CUB3D: mlx failed\n");
		exiter(1);
	}
	data->background_img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data->background_img.img == NULL)
	{
		print_err("CUB3D: mlx_new_image failed\n");
		exiter(1);
	}
	data->background_img.addr = safer_get_data_addr(data->background_img.img,
			&(data->background_img.bits_per_pixel),
			&(data->background_img.line_length),
			&(data->background_img.endian));
	data->floor_color = CREATE_TRGB(0, game->floor.r, game->floor.g,
			game->floor.b);
	data->ceiling_color = CREATE_TRGB(0, game->ceiling.r, game->ceiling.g,
			game->ceiling.b);
}

void	hooks(void)
{
	t_data	*data;

	data = get_data();
	mlx_hook(data->win, 2, 1L << 0, handle_keys, NULL);
	mlx_hook(data->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(data->win, 17, 1L << 0, ft_close, NULL);
	mlx_hook(data->win, 6, 1L << 6, mouse_event, NULL);
	mlx_mouse_hook(data->win, handle_mouse_event, NULL);
}

void	initialize_variables(t_game *game)
{
	t_data	*data;

	data = get_data();
	data->speed = 4;
	data->player_pos.x = game->player.pos_x * GRID_DIST + (float)GRID_DIST / 2;
	data->player_pos.y = game->player.pos_y * GRID_DIST + (float)GRID_DIST / 2;
	data->player_angle = 0;
	data->player_dir.x = cos(data->player_angle) * data->speed;
	data->player_dir.y = sin(data->player_angle) * data->speed;
	data->map = game->map.grid;
	data->height = game->map.height;
	data->width = game->map.width;
	data->move_forward = 0;
	data->move_backward = 0;
	data->move_left = 0;
	data->move_right = 0;
	data->rotate_left = 0;
	data->rotate_right = 0;
	data->show_scope = 0;
	data->zoom_factor = 1;
	data->gun_id = 1;
	data->show_tab = 0;
	data->number_of_shoots = 0;
	data->gun_offset_x = 0.0;
}

void	init_north_south_textures(t_game *game)
{
	t_data	*data;

	data = get_data();
	data->north_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			game->north.path, &(data->north_img.width),
			&(data->north_img.height));
	data->north_img.img_data.addr
		= safer_get_data_addr(data->north_img.img_data.img,
			&(data->north_img.img_data.bits_per_pixel),
			&(data->north_img.img_data.line_length),
			&(data->north_img.img_data.endian));
	data->south_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			game->south.path, &(data->south_img.width),
			&(data->south_img.height));
	data->south_img.img_data.addr
		= safer_get_data_addr(data->south_img.img_data.img,
			&(data->south_img.img_data.bits_per_pixel),
			&(data->south_img.img_data.line_length),
			&(data->south_img.img_data.endian));
}

void	init_west_east_textures(t_game *game)
{
	t_data	*data;

	data = get_data();
	data->east_img.img_data.img = safer_xpm_file_to_image(data->mlx,
			game->east.path, &(data->east_img.width), &(data->east_img.height));
	data->east_img.img_data.addr
		= safer_get_data_addr(data->east_img.img_data.img,
			&(data->east_img.img_data.bits_per_pixel),
			&(data->east_img.img_data.line_length),
			&(data->east_img.img_data.endian));
	data->west_img.img_data.img = mlx_xpm_file_to_image(data->mlx,
			game->west.path, &(data->west_img.width), &(data->west_img.height));
	data->west_img.img_data.addr
		= mlx_get_data_addr(data->west_img.img_data.img,
			&(data->west_img.img_data.bits_per_pixel),
			&(data->west_img.img_data.line_length),
			&(data->west_img.img_data.endian));
}

void	init_door_textures_helper(void)
{
	t_data	*data;

	data = get_data();
	data->door_img.img_data.img = mlx_xpm_file_to_image(data->mlx,
			"textures/door_frames/1.xpm", &(data->door_img.width),
			&(data->door_img.height));
	data->door_img.img_data.addr
		= mlx_get_data_addr(data->door_img.img_data.img,
			&(data->door_img.img_data.bits_per_pixel),
			&(data->door_img.img_data.line_length),
			&(data->door_img.img_data.endian));
}

void	init_door_textures(void)
{
	t_data	*data;

	data = get_data();
	init_door_textures_helper();
	data->door_open_img.img_data.img = mlx_xpm_file_to_image(data->mlx,
			"textures/door_frames/17.xpm", &(data->door_open_img.width),
			&(data->door_open_img.height));
	data->door_open_img.img_data.addr
		= mlx_get_data_addr(data->door_open_img.img_data.img,
			&(data->door_open_img.img_data.bits_per_pixel),
			&(data->door_open_img.img_data.line_length),
			&(data->door_open_img.img_data.endian));
	data->door_animating_img.img_data.img = mlx_xpm_file_to_image(data->mlx,
			"textures/door_frames/13.xpm", &(data->door_animating_img.width),
			&(data->door_animating_img.height));
	data->door_animating_img.img_data.addr
		= mlx_get_data_addr(data->door_animating_img.img_data.img,
			&(data->door_animating_img.img_data.bits_per_pixel),
			&(data->door_animating_img.img_data.line_length),
			&(data->door_animating_img.img_data.endian));
}

void	init_data(t_game game)
{
	t_data	*data;

	data = get_data();
	data->mlx = mlx_init();
	init_data_helper(&game);
	hooks();
	initialize_variables(&game);
	init_north_south_textures(&game);
	init_west_east_textures(&game);
	init_door_textures();
}

void	render_frame(void)
{
	t_data	*data;
	int		shake_x;
	int		shake_y;

	shake_x = 0;
	shake_y = 0;
	if (get_data()->screen_shake_timer > 0)
	{
		shake_x = (rand() % (2 * get_data()->screen_shake_intensity))
			- get_data()->screen_shake_intensity;
		shake_y = (rand() % (2 * get_data()->screen_shake_intensity))
			- get_data()->screen_shake_intensity;
		get_data()->screen_shake_timer--;
	}
	mlx_clear_window(get_data()->mlx, get_data()->win);
	mlx_put_image_to_window(get_data()->mlx, get_data()->win,
		get_data()->background_img.img, shake_x, shake_y);
}

void	initialize_gun3shoot_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/gun3shoot/1.xpm";
	frame_paths[1] = "textures/gun3shoot/2.xpm";
	frame_paths[2] = "textures/gun3shoot/3.xpm";
	frame_paths[3] = "textures/gun3shoot/4.xpm";
	frame_paths[4] = "textures/gun3shoot/5.xpm";
	frame_paths[5] = "textures/gun3shoot/6.xpm";
	frame_paths[6] = "textures/gun3shoot/7.xpm";
	frame_paths[7] = "textures/gun3shoot/8.xpm";
	frame_paths[8] = "textures/gun3shoot/9.xpm";
	frame_paths[9] = "textures/gun3shoot/10.xpm";
	frame_paths[10] = "textures/gun3shoot/11.xpm";
	frame_paths[11] = "textures/gun3shoot/12.xpm";
	frame_paths[12] = "textures/gun3shoot/13.xpm";
	frame_paths[13] = "textures/gun3shoot/14.xpm";
	frame_paths[14] = "textures/gun3shoot/15.xpm";
}

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
		data->gun3.shooting_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun3.width, &data->gun3.height);
		i++;
	}
	data->gun3.current_frame = 0;
	data->gun3.frame_delay = 0;
	data->gun3.is_reloading = 0;
	data->gun3.is_shooting = 0;
	data->gun3.shooted = 0;
	data->gun3.show_scope = 0;
}

void	update_enemy_frames(void)
{
	int	i;

	i = 0;
	while (i < get_data()->num_sprites)
	{
		if (get_data()->sprites[i].frame_delay >= 20)
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

void	initialize_running_gun3_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/running_gun3/1.xpm";
	frame_paths[1] = "textures/running_gun3/2.xpm";
	frame_paths[2] = "textures/running_gun3/3.xpm";
	frame_paths[3] = "textures/running_gun3/4.xpm";
	frame_paths[4] = "textures/running_gun3/5.xpm";
	frame_paths[5] = "textures/running_gun3/6.xpm";
	frame_paths[6] = "textures/running_gun3/7.xpm";
	frame_paths[7] = "textures/running_gun3/8.xpm";
	frame_paths[8] = "textures/running_gun3/9.xpm";
	frame_paths[9] = "textures/running_gun3/10.xpm";
	frame_paths[10] = "textures/running_gun3/11.xpm";
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
		data->gun3.running_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun3.width, &data->gun3.height);
		i++;
	}
	data->gun3.current_frame = 0;
	data->gun3.frame_delay = 0;
}

void	initialize_reloading_gun3_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/reloading_gun3/1.xpm";
	frame_paths[1] = "textures/reloading_gun3/2.xpm";
	frame_paths[2] = "textures/reloading_gun3/3.xpm";
	frame_paths[3] = "textures/reloading_gun3/4.xpm";
	frame_paths[4] = "textures/reloading_gun3/5.xpm";
	frame_paths[5] = "textures/reloading_gun3/6.xpm";
	frame_paths[6] = "textures/reloading_gun3/7.xpm";
	frame_paths[7] = "textures/reloading_gun3/8.xpm";
	frame_paths[8] = "textures/reloading_gun3/9.xpm";
	frame_paths[9] = "textures/reloading_gun3/10.xpm";
	frame_paths[10] = "textures/reloading_gun3/11.xpm";
	frame_paths[11] = "textures/reloading_gun3/12.xpm";
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
		data->gun3.reloading_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun3.width, &data->gun3.height);
		i++;
	}
	data->gun3.current_frame = 0;
	data->gun3.frame_delay = 0;
	data->gun3.is_reloading = 0;
	data->gun3.is_shooting = 0;
	data->gun3.shooted = 0;
}

void	initialize_first_scope_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/zoom_shoot_gun3/1.xpm";
	frame_paths[1] = "textures/zoom_shoot_gun3/2.xpm";
	frame_paths[2] = "textures/zoom_shoot_gun3/3.xpm";
	frame_paths[3] = "textures/zoom_shoot_gun3/4.xpm";
	frame_paths[4] = "textures/zoom_shoot_gun3/5.xpm";
	frame_paths[5] = "textures/zoom_shoot_gun3/6.xpm";
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
		data->gun3.first_scope_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun3.width, &data->gun3.height);
		i++;
	}
	data->gun3.current_frame = 0;
	data->gun3.frame_delay = 0;
	data->gun3.is_reloading = 0;
	data->gun3.is_shooting = 0;
	data->gun3.shooted = 0;
	data->gun3.is_showing_scope = 0;
}

void	initialize_last_scope_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/zoom_shoot_gun3/12.xpm";
	frame_paths[1] = "textures/zoom_shoot_gun3/13.xpm";
	frame_paths[2] = "textures/zoom_shoot_gun3/14.xpm";
	frame_paths[3] = "textures/zoom_shoot_gun3/15.xpm";
	frame_paths[4] = "textures/zoom_shoot_gun3/16.xpm";
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
		data->gun3.last_scope_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun3.width, &data->gun3.height);
		i++;
	}
	data->gun3.current_frame = 4;
	data->gun3.frame_delay = 0;
	data->gun3.is_reloading = 0;
	data->gun3.is_shooting = 0;
	data->gun3.shooted = 0;
	data->gun3.is_showing_scope = 0;
}

void	initialize_zoom_shoot_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/zoom_shoot_gun3/6.xpm";
	frame_paths[1] = "textures/zoom_shoot_gun3/7.xpm";
	frame_paths[2] = "textures/zoom_shoot_gun3/8.xpm";
	frame_paths[3] = "textures/zoom_shoot_gun3/9.xpm";
	frame_paths[4] = "textures/zoom_shoot_gun3/10.xpm";
	frame_paths[5] = "textures/zoom_shoot_gun3/10.xpm";
}

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
		data->gun3.scope_shooting_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun3.width, &data->gun3.height);
		i++;
	}
	data->gun3.current_frame = 4;
	data->gun3.frame_delay = 0;
	data->gun3.is_reloading = 0;
	data->gun3.is_shooting = 0;
	data->gun3.shooted = 0;
	data->gun3.is_showing_scope = 0;
	data->gun3.is_showing_scope = 0;
}

void	initialize_walking_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/movin_walk_gun3_slow/1.xpm";
	frame_paths[1] = "textures/movin_walk_gun3_slow/2.xpm";
	frame_paths[2] = "textures/movin_walk_gun3_slow/3.xpm";
	frame_paths[3] = "textures/movin_walk_gun3_slow/4.xpm";
	frame_paths[4] = "textures/movin_walk_gun3_slow/5.xpm";
	frame_paths[5] = "textures/movin_walk_gun3_slow/6.xpm";
	frame_paths[6] = "textures/movin_walk_gun3_slow/7.xpm";
	frame_paths[7] = "textures/movin_walk_gun3_slow/8.xpm";
	frame_paths[8] = "textures/movin_walk_gun3_slow/9.xpm";
	frame_paths[9] = "textures/movin_walk_gun3_slow/10.xpm";
	frame_paths[10] = "textures/movin_walk_gun3_slow/11.xpm";
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
		data->gun3.walking_frames[i] = safer_xpm_file_to_image(data->mlx,
				frame_paths[i], &data->gun3.width, &data->gun3.height);
		i++;
	}
	data->gun3.current_frame = 0;
	data->gun3.frame_delay = 0;
}

void	render_closing_door(int door_x, int door_y)
{
	t_data	*data;

	data = get_data();
	if (data->door.frame_delay++ >= 3)
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
		data->door_animating_img.img_data.img
			= data->door.img[data->door.current_frame];
		data->door_animating_img.img_data.addr
			= mlx_get_data_addr(data->door_animating_img.img_data.img,
				&data->door_animating_img.img_data.bits_per_pixel,
				&data->door_animating_img.img_data.line_length,
				&data->door_animating_img.img_data.endian);
		data->is_updated = 1;
	}
}

// clang-format off
void	render_opening_door(int door_x, int door_y)
{
	t_data	*data;

	data = get_data();
	if (data->door.frame_delay++ >= 3)
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
		data->door_animating_img.img_data.img
			= data->door.img[data->door.current_frame];
		data->door_animating_img.img_data.addr
			= mlx_get_data_addr(data->door_animating_img.img_data.img,
				&data->door_animating_img.img_data.bits_per_pixel,
				&data->door_animating_img.img_data.line_length,
				&data->door_animating_img.img_data.endian);
		data->is_updated = 1;
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

// Implementation of gun loading and animation functions

void	render_scope_frames(int num_frames, t_gun *gun, int frame_delay)
{
	if (gun->frame_delay++ >= frame_delay)
	{
		gun->frame_delay = 1;
		gun->current_frame++;
		if (gun->current_frame >= num_frames)
		{
			gun->current_frame = 0;
			gun->is_shooting = num_frames;
			gun->is_reloading = 0;
		}
	}
}

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

void	render_reloading(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.frame_delay++ >= 23)
	{
		data->gun3.frame_delay = 1;
		data->gun3.current_frame++;
		if (data->gun3.current_frame >= 12)
		{
			data->gun3.current_frame = 0;
			data->gun3.is_shooting = 0;
			data->gun3.is_reloading = 0;
		}
	}
	render_transparent_frame(
		data->gun3.reloading_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
	data->number_of_shoots = 0;
}

void	render_shooting(int gun_id)
{
	t_data	*data;

	data = get_data();
	if (gun_id == 2)
		render_gun_frames(15, &data->gun3, 6);
}

void	reload_gun_when_empty(void)
{
	if (get_data()->number_of_shoots >= 8)
	{
		get_data()->gun3.is_reloading = 1;
		render_reloading();
		return ;
	}
}

void	render_frist_gun_frame(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.show_scope && !data->gun3.is_reloading
		&& !data->gun3.is_shooting)
	{
		render_transparent_frame(
			data->gun3.first_scope_frames[data->gun3.current_frame],
			data->gun3.width, data->gun3.height);
		return ;
	}
}

void	render_last_frame_gun(void)
{
	t_data	*data;

	data = get_data();
	if (!data->gun3.show_scope && !data->gun3.is_reloading
		&& !data->gun3.is_shooting && !data->is_running)
	{
		data->gun3.current_frame = 4;
		render_transparent_frame(
			data->gun3.last_scope_frames[data->gun3.current_frame],
			data->gun3.width, data->gun3.height);
		return ;
	}
}

void	render_shooting_in_scope(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.frame_delay++ >= 5)
	{
		data->gun3.frame_delay = 1;
		data->gun3.current_frame++;
		if (data->gun3.current_frame >= 6)
		{
			data->gun3.current_frame = 5;
			data->gun3.is_shooting = 0;
			data->gun3.is_reloading = 0;
		}
	}
	render_transparent_frame(
		data->gun3.scope_shooting_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
	render_frame();
}

void	render_shootin_frames(void)
{
	t_data	*data;

	data = get_data();
	render_shooting(2);
	if (data->gun3.frame_delay++ >= 5)
	{
		data->gun3.frame_delay = 1;
		data->gun3.current_frame++;
		if (data->gun3.current_frame >= 12)
		{
			data->gun3.current_frame = 4;
			data->gun3.is_shooting = 0;
			data->gun3.is_reloading = 0;
		}
	}
	render_transparent_frame(
		data->gun3.shooting_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
	render_frame();
}

void	render_scope_shooting_frames(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.frame_delay++ >= 5)
	{
		data->gun3.frame_delay = 1;
		data->gun3.current_frame++;
		if (data->gun3.current_frame >= 6)
		{
			data->gun3.current_frame = 5;
			data->gun3.is_shooting = 0;
			data->gun3.is_reloading = 0;
		}
	}
	render_transparent_frame(
		data->gun3.scope_shooting_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
	render_frame();
}

void	handle_shooting_animation(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.show_scope == 1)
		render_scope_shooting_frames();
	else
		render_shootin_frames();
}

void	render_show_scope_frames(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.frame_delay++ >= 8)
	{
		data->gun3.frame_delay = 1;
		data->gun3.current_frame++;
		data->zoom_factor -= 0.09;
		if (data->gun3.current_frame >= 5)
		{
			data->gun3.current_frame = 5;
			data->gun3.is_showing_scope = 0;
			data->zoom_factor += 0.06;
		}
	}
	render_transparent_frame(
		data->gun3.first_scope_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
}

void	render_unshowing_scope(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.frame_delay++ >= 8)
	{
		data->gun3.frame_delay = 1;
		data->gun3.current_frame++;
		data->zoom_factor += 0.09;
		if (data->gun3.current_frame >= 4)
		{
			data->gun3.current_frame = 4;
			data->gun3.is_showing_scope = 0;
		}
	}
	render_transparent_frame(
		data->gun3.last_scope_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
}

void	render_walking(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.frame_delay++ >= 6)
	{
		data->gun3.frame_delay = 0;
		data->gun3.current_frame = (data->gun3.current_frame + 1) % 11;
	}
	render_transparent_frame(
		data->gun3.walking_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
}

void	render_running(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.frame_delay++ >= 10)
	{
		data->gun3.frame_delay = 0;
		data->gun3.current_frame = (data->gun3.current_frame + 1) % 11;
	}
	render_transparent_frame(
		data->gun3.running_frames[data->gun3.current_frame],
		data->gun3.width, data->gun3.height);
}

void	render_gun3(void)
{
	t_data	*data;

	data = get_data();
	if (data->gun3.is_showing_scope)
	{
		if (data->gun3.show_scope)
			return (render_show_scope_frames());
		else
			return (render_unshowing_scope());
	}
	if (data->gun3.is_shooting)
		return (handle_shooting_animation());
	if (data->gun3.is_reloading)
		return (render_reloading());
	reload_gun_when_empty();
	if (data->is_walking && !data->gun3.show_scope)
		return (render_walking());
	if (data->is_running && !data->gun3.show_scope)
		return (render_running());
	render_last_frame_gun();
	render_frist_gun_frame();
}

void	render_gun1(void)
{
	if (get_data()->gun.is_reloading)
		render_reloading();
	render_transparent_frame(
		get_data()->gun.reloading_frames[get_data()->gun.current_frame],
		get_data()->gun.width, get_data()->gun.height);
}

void	render_gun(void)
{
	get_data()->gun_id = 2;
	if (get_data()->gun_id == 2)
	{
		render_gun3();
	}
	render_frame();
}

int	player_is_close_to_door(void)
{
	return (get_data()->front_ray.dist < 2 * GRID_DIST);
}

void	render_cercle(void)
{
	int	radius;
	int	center_x;
	int	center_y;
	int	x;
	int	y;

	radius = 7;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				put_pixel(&(get_data()->background_img), center_x + x, center_y
					+ y, BLACK);
			}
			x++;
		}
		y++;
	}
}

int	loop_hook(void)
{
	if (get_data()->is_tab_pressed)
	{
		return (0);
	}
	if (get_data()->is_updated)
	{
		update_movement();
		init_background();
		render_walls();
		render_minimap();
		render_sprites();
		update_door_animation();
		render_background();
		render_gun();
		render_cercle();
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	if (ac != 2 || check_file(av[1], &fd) == 0)
		return (printf("Error\nUsage: ./Cube3d map.cub\n"), 0);
	game = check_map(fd, av[1]);
	close(fd);
	init_data(game);
	init_sprites(&game);
	init_background();
	render_walls();
	render_minimap();
	render_sprites();
	render_background();
	load_shooting_gun3_frames();
	load_running_gun3_frames();
	load_reloading_gun3_frames();
	load_first_scope_frames();
	load_last_scope_frames();
	load_shooting_scope_frames();
	load_walking_gun3_frames();
	load_door_frames();
	render_gun();
	mlx_mouse_hide(get_data()->mlx, get_data()->win);
	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);
	mlx_loop(get_data()->mlx);
	return (0);
}
