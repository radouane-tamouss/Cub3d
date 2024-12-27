/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:31:10 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:31:14 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ray_hit_sprite(t_ray_data ray, t_sprite sprite)
{
	char	current_tile;

	while (1)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		current_tile = get_data()->map[ray.map_y][ray.map_x];
		if (current_tile == '1' || current_tile == 'D' || current_tile == 'P')
		{
			calculate_ray_distance(&ray);
			if (ray.dist < sprite.dist)
				return (0);
			return (1);
		}
	}
}

void	update_enemies_data_helper(int i, t_vector *sprite_to_player,
		float *angle)
{
	t_data	*data;

	data = get_data();
	if (data->sprites[i].is_dead == 0)
	{
		data->sprites[i].dist = calc_dist_f(data->sprites[i].position.x,
				data->sprites[i].position.y, data->player_pos);
		sprite_to_player->x = data->player_pos.x - data->sprites[i].position.x;
		sprite_to_player->y = data->player_pos.y - data->sprites[i].position.y;
		if (data->sprites[i].dist <= 5 * GRID_DIST)
			sprite_on_minimap(*sprite_to_player);
		*angle = atan2(-sprite_to_player->y, -sprite_to_player->x);
		*angle = normalise_angle(*angle);
		enemy_move(data->sprites + i, *sprite_to_player);
	}
	else if (data->sprites[i].is_dead == 1 || data->sprites[i].is_dying == 1)
	{
		data->sprites[i].dist = calc_dist_f(data->sprites[i].position.x,
				data->sprites[i].position.y, data->player_pos);
	}
}

void	update_enemies_data(void)
{
	t_data		*data;
	int			i;
	t_vector	sprite_to_player;
	float		angle;

	data = get_data();
	i = 0;
	while (i < data->num_sprites)
	{
		update_enemies_data_helper(i, &sprite_to_player, &angle);
		++i;
	}
}

void	sprite_on_minimap(t_vector dir)
{
	float	x;
	float	y;

	x = (5 * SQUARE_SIZE) - (dir.x / GRID_DIST) * SQUARE_SIZE;
	y = (5 * SQUARE_SIZE) - (dir.y / GRID_DIST) * SQUARE_SIZE;
	render_cyrcle(x, y, 6, RED);
}

void	update_dying_frames(t_sprite *sprite)
{
	int	i;

	if (sprite->frame_delay >= 10)
	{
		sprite->current_dying_frame++;
		if (sprite->current_dying_frame >= 14)
		{
			sprite->current_dying_frame = 0;
			sprite->is_dead = 1;
			sprite->is_dying = 0;
		}
		sprite->frame_delay = 0;
	}
	else
	{
		sprite->frame_delay++;
	}
}
