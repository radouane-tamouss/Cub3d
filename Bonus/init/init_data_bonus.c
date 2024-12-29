/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:14:04 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:37:47 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
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
	data->floor_color = create_trgb(0, game->floor.r, game->floor.g,
			game->floor.b);
	data->ceiling_color = create_trgb(0, game->ceiling.r, game->ceiling.g,
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

void	init_direction(t_game *game)
{
	t_data	*data;

	data = get_data();
	if (data->player_direction == 'E')
		data->player_angle = 0.0;
	else if (data->player_direction == 'S')
		data->player_angle = MY_PI / 2;
	else if (data->player_direction == 'W')
		data->player_angle = MY_PI;
	else if (data->player_direction == 'N')
		data->player_angle = 3 * MY_PI / 2;
	else
		data->player_angle = 0.0;
}

void	initialize_variables(t_game *game)
{
	t_data	*data;

	data = get_data();
	data->speed = 4;
	data->player_pos.x = game->player.pos_x * GRID_DIST + (float)GRID_DIST / 2;
	data->player_pos.y = game->player.pos_y * GRID_DIST + (float)GRID_DIST / 2;
	init_direction(game);
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
	data->number_of_shoots = 0;
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
