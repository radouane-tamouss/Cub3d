/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:59:58 by atamousse.r       #+#    #+#             */
/*   Updated: 2024/12/25 20:54:27 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	calc_num_sprites(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	get_data()->num_sprites = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'M')
			{
				get_data()->num_sprites++;
			}
			j++;
		}
		i++;
	}
}

void	init_sprites_helper(t_game *game, int i, int j, int n)
{
	t_data	*data;

	data = get_data();
	data->sprites[n].is_dead = 0;
	data->sprites[n].position.x
		= j * GRID_DIST + ((float)GRID_DIST / 2);
	data->sprites[n].position.y
		= i * GRID_DIST + ((float)GRID_DIST / 2);
	data->sprites[n].z = (float)(WIN_HEIGHT) / 2;
	data->sprites[n].texture.img_data.img
		= safer_xpm_file_to_image(data->mlx,
			"textures/zombie/1.xpm",
			&(data->sprites[n].texture.width),
			&(data->sprites[n].texture.height));
	data->sprites[n].texture.img_data.addr
		= safer_get_data_addr(data->sprites[n].texture.img_data.img,
			&(data->sprites[n].texture.img_data.bits_per_pixel),
			&(data->sprites[n].texture.img_data.line_length),
			&(data->sprites[n].texture.img_data.endian));
	data->sprites[n].current_frame = 0;
	data->sprites[n].display_start_x = 0;
	data->sprites[n].display_end_x = 0;
	data->sprites[n].display_start_y = 0;
	data->sprites[n].display_end_y = 0;
	data->sprites[n].current_dying_frame = 0;
	data->sprites[n].frame_delay = 0;
	data->sprites[n].is_dead = 0;
	data->sprites[n].is_dying = 0;
}

// clang-format off
void	init_sprites(t_game *game)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	calc_num_sprites(game);
	if (get_data()->num_sprites == 0)
		return ;
	get_data()->sprites = mallocate(sizeof(t_sprite) * get_data()->num_sprites);
	n = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'M')
				init_sprites_helper(game, i, j, n++);
			j++;
		}
		i++;
	}
	i = 0;
	load_load_sprite_frames();
	load_dying_sprite_frames();
}
