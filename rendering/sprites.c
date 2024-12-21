/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:31:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/20 00:49:16 by eouhrich         ###   ########.fr       */
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
		if (current_tile == '1' || current_tile == 'D')
		{
			calculate_ray_distance(&ray);
			if (ray.dist < sprite.dist) return (0);
			return (1);
		}
	}
}

static void	calc_square_points_pos(t_vector *square_position, t_vector center, float square_lenght)
{
	square_position[0].x = center.x - square_lenght;
	square_position[0].y = center.y - square_lenght;
	square_position[1].x = center.x + square_lenght;
	square_position[1].y = center.y - square_lenght;
	square_position[2].x = center.x - square_lenght;
	square_position[2].y = center.y + square_lenght;
	square_position[3].x = center.x + square_lenght;
	square_position[3].y = center.y + square_lenght;
}

void	next_step_square(t_vector *next_step_square, t_vector center, float square_lenght, t_vector dir)
{
	t_vector	square_position[4];

	calc_square_points_pos(square_position, center, square_lenght);
	next_step_square[0].x = get_data()->map[(int)square_position[0].y
		/ GRID_DIST][(int)(square_position[0].x + dir.x) / GRID_DIST];
	next_step_square[0].y = get_data()->map[(int)(square_position[0].y + dir.y)
		/ GRID_DIST][(int)(square_position[0].x) / GRID_DIST];
	next_step_square[1].x = get_data()->map[(int)square_position[1].y
		/ GRID_DIST][(int)(square_position[1].x + dir.x) / GRID_DIST];
	next_step_square[1].y = get_data()->map[(int)(square_position[1].y + dir.y)
		/ GRID_DIST][(int)(square_position[1].x) / GRID_DIST];
	next_step_square[2].x = get_data()->map[(int)square_position[2].y
		/ GRID_DIST][(int)(square_position[2].x + dir.x) / GRID_DIST];
	next_step_square[2].y = get_data()->map[(int)(square_position[2].y + dir.y)
		/ GRID_DIST][(int)(square_position[2].x) / GRID_DIST];
	next_step_square[3].x = get_data()->map[(int)square_position[3].y
		/ GRID_DIST][(int)(square_position[3].x + dir.x) / GRID_DIST];
	next_step_square[3].y = get_data()->map[(int)(square_position[3].y + dir.y)
		/ GRID_DIST][(int)(square_position[3].x) / GRID_DIST];
}

void	enemy_move(t_sprite *sprite, t_vector dir)
{
	float		magnitude;
	t_vector	square[4];

	magnitude = ft_max(vector_magnitude(dir), 1.0);
	dir.x = (dir.x / magnitude) * ENEMY_SPEED;
	dir.y = (dir.y / magnitude) * ENEMY_SPEED;
	next_step_square(square, sprite->position, ((float)GRID_DIST / 8), dir);
	if (square[0].x != '1' && square[1].x != '1' && square[2].x != '1' &&
		square[3].x != '1' && square[0].x != 'D' && square[1].x != 'D' &&
		square[2].x != 'D' && square[3].x != 'D' && square[0].x != 'P' &&
		square[1].x != 'P' && square[2].x != 'P' && square[3].x != 'P')
		sprite->position.x += dir.x;
	if (square[0].y != '1' && square[1].y != '1' && square[2].y != '1' &&
		square[3].y != '1' && square[0].y != 'D' && square[1].y != 'D' &&
		square[2].y != 'D' && square[3].y != 'D' && square[0].y != 'P' &&
		square[1].y != 'P' && square[2].y != 'P' && square[3].y != 'P')
		sprite->position.y += dir.y;
}

void	sprite_on_minimap(t_vector dir)
{
	int			radius;
	int			i;
	int			j;
	t_vector	center;

	radius = 6;
	center.x = (5 * SQUARE_SIZE) - (dir.x / GRID_DIST) * SQUARE_SIZE;
	center.y = (5 * SQUARE_SIZE) - (dir.y / GRID_DIST) * SQUARE_SIZE;
	// mlx_put_image_to_window(get_data()->mlx, get_data()->win, get_data()->enemie_on_map.img, center.x, center.y);
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= radius * radius)
				put_pixel(&(get_data()->background_img), center.x + j,
						  center.y + i, RED);
			++j;
		}
		++i;
	}
}

void	update_enemies_data()
{
	int			i;
	t_vector	sprite_to_player;
	float	angle;

	i = 0;
	while (i < get_data()->num_sprites)
	{
		// For living enemies
		if (get_data()->sprites[i].is_dead == 0)
		{
			// Calculate distance and movement as before
			get_data()->sprites[i].dist = calc_dist_f(
				get_data()->sprites[i].position.x,
				get_data()->sprites[i].position.y, get_data()->player_pos);
			sprite_to_player.x =
				get_data()->player_pos.x - get_data()->sprites[i].position.x;
			sprite_to_player.y =
				get_data()->player_pos.y - get_data()->sprites[i].position.y;
			if (get_data()->sprites[i].dist <= 5 * GRID_DIST)
				sprite_on_minimap(sprite_to_player);
			angle = atan2(-sprite_to_player.y, -sprite_to_player.x);
			angle = normalise_angle(angle);
			enemy_move(get_data()->sprites + i, sprite_to_player);
		}
		else if (get_data()->sprites[i].is_dead == 1 ||
				 get_data()->sprites[i].is_dying == 1)
		{
			// Calculate teh distance basedd on the Position when the enemy
			// dieeeeeeed
			get_data()->sprites[i].dist = calc_dist_f(
				get_data()->sprites[i].position.x,
				get_data()->sprites[i].position.y, get_data()->player_pos);
		}
		++i;
	}
}

// void update_enemies_data()
// {
//	 int i;
//	 t_vector sprite_to_player;
//	 float angle;
//	 float magnitude;
//
//	 i = 0;
//	 while (i < get_data()->num_sprites)
//	 {
//		 if (get_data()->sprites[i].is_dead == 0)
//		 {
//			 get_data()->sprites[i].dist = calc_dist_f(
//				 get_data()->sprites[i].position.x,
//				 get_data()->sprites[i].position.y, get_data()->player_pos);
//			 sprite_to_player.x =
//				 get_data()->player_pos.x - get_data()->sprites[i].position.x;
//			 sprite_to_player.y =
//				 get_data()->player_pos.y - get_data()->sprites[i].position.y;
//			 if (get_data()->sprites[i].dist <= 5 * GRID_DIST)
//				 sprite_on_minimap(sprite_to_player);
//			 angle = atan2(-sprite_to_player.y, -sprite_to_player.x);
//			 angle = normalise_angle(angle);
//			 enemy_move(get_data()->sprites + i, sprite_to_player);
//		 }
//		 ++i;
//	 }
// }

void sort_sprites(void)
{
	t_sprite tmp_sprite;
	int i;
	int j;

	i = 0;
	while (i < get_data()->num_sprites - 1)
	{
		j = i + 1;
		while (j < get_data()->num_sprites)
		{
			if (get_data()->sprites[i].dist < get_data()->sprites[j].dist)
			{
				tmp_sprite = get_data()->sprites[i];
				get_data()->sprites[i] = get_data()->sprites[j];
				get_data()->sprites[j] = tmp_sprite;
			}
			j++;
		}
		i++;
	}
}

void	update_dying_frames(t_sprite *sprite)
{
	int i;
	if (sprite->frame_delay >= 10)
	{
		sprite->current_dying_frame++;
		printf("current frame %d\n", sprite->current_dying_frame);
		if (sprite->current_dying_frame >= 14)
		{
			sprite->current_dying_frame = 0;
			sprite->is_dead = 1;
			sprite->is_dying = 0;
			printf("%sreseted to 0%s\n", CRED, CWHITE);
		}
		sprite->frame_delay = 0;
	}
	else
	{
		sprite->frame_delay++;
	}
}

static void	render_sprite(t_sprite sprite)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	j = ft_max(sprite.display_start_x, 0.0f);
	while (j < sprite.display_end_x && j < WIN_WIDTH)
	{
		if (ray_hit_sprite(create_ray(get_data()->player_angle - (FOV / 2) +
									  (j * (FOV / WIN_WIDTH))),
						   sprite))
		{
			pixel_x = ((float)(j - sprite.display_start_x) /
					   (float)(sprite.display_end_x - sprite.display_start_x)) *
					  sprite.texture.width;
			i = ft_max(sprite.display_start_y, 0.0f);
			while (i < sprite.display_end_y && i < WIN_HEIGHT)
			{
				pixel_y =
					(((float)(i - sprite.display_start_y) /
					  (float)(sprite.display_end_y - sprite.display_start_y)) *
					 sprite.texture.height);
				if (sprite.is_dead == 0 && sprite.is_dying == 0)
				{
					put_pixel(
						&(get_data()->background_img), j, i,
						pull_pixel(
							get_data()->sprites_frames[sprite.current_frame],
							pixel_x, pixel_y));
				}
				else if (sprite.is_dying == 1 && sprite.is_dead == 0)
				{
					// printf("here is dying\n");
					put_pixel(
						&(get_data()->background_img), j, i,
						pull_pixel(
							get_data()
								->dying_frames[sprite.current_dying_frame],
							pixel_x, pixel_y));
				}
				else if (sprite.is_dead == 1)
				{
					// printf("here is dead\n");
					put_pixel(&(get_data()->background_img), j, i,
							  pull_pixel(get_data()->dying_frames[14], pixel_x,
										 pixel_y));
				}
				else
				{
					put_pixel(
						&(get_data()->background_img), j, i,
						pull_pixel(
							get_data()->sprites_frames[sprite.current_frame],
							pixel_x, pixel_y));
				}
				++i;
			}
		}
		++j;
	}
}

static void	find_display_postion(t_sprite *sprite, float angle)
{
	int		position;
	float	scale;

	position = (angle / FOV) * WIN_WIDTH;
	sprite->dist = ft_max(sprite->dist, 10);
	scale = ((WIN_WIDTH) / sprite->dist) * 0.1;
	sprite->display_start_x =
		position + ((float)WIN_WIDTH / 2) - (sprite->texture.width * scale) / 2;
	sprite->display_start_y = sprite->z + scale;
	sprite->display_end_x =
		(sprite->texture.width * scale) / 2 + position + ((float)WIN_WIDTH / 2);
	sprite->display_end_y =
		(sprite->texture.height * scale) + sprite->z + scale;
}

static int sprite_angle_valide(t_sprite *sprite, float *angle)
{
	t_vector	vector_to_sprite;

	vector_to_sprite.x = sprite->position.x - get_data()->player_pos.x;
	vector_to_sprite.y = sprite->position.y - get_data()->player_pos.y;
	if (dot_product(vector_to_sprite, get_data()->player_dir) < 0) return (0);
	*angle = atan2(vector_to_sprite.y, vector_to_sprite.x) -
			 normalise_angle(get_data()->player_angle);
	while (*angle >= (MY_PI) || *angle <= (-MY_PI))
	{
		if (*angle >= (MY_PI)) *angle -= 2 * MY_PI;
		if (*angle <= (-MY_PI)) *angle += 2 * MY_PI;
	}
	if (*angle < -(FOV / 2) || *angle > (FOV / 2)) return (0);
	return (1);
}

int	should_render(t_sprite *sprite, float *angle)
{
	t_vector	vector_to_sprite;
	t_ray_data	start_ray;
	t_ray_data	end_ray;

	if (!sprite_angle_valide(sprite, angle))
		return (0);
	find_display_postion(sprite, *angle);
	start_ray = create_ray(get_data()->player_angle - (FOV / 2) +
						   (sprite->display_start_x * (FOV / WIN_WIDTH)));
	if (ray_hit_sprite(start_ray, *sprite)) return (1);
	end_ray = create_ray(get_data()->player_angle - (FOV / 2) +
						 (sprite->display_end_x * (FOV / WIN_WIDTH)));
	if (ray_hit_sprite(end_ray, *sprite)) return (1);
	return (0);
}

// sorting enemies by there dist from the player
void	render_sprites(void)
{
	float	angle;
	int		i;

	update_enemies_data();
	sort_sprites();
	i = 0;
	while (i < get_data()->num_sprites)
	{
		if (get_data()->sprites[i].dist < GRID_DIST)
		{
			++i;
			continue;
		}
		if (should_render(get_data()->sprites + i, &angle) &&
			get_data()->sprites[i].is_dead == 0)
		{
			update_enemy_frames();
			render_sprite(get_data()->sprites[i]);
		}
		if (should_render(get_data()->sprites + i, &angle) &&
			get_data()->sprites[i].is_dying == 1 &&
			get_data()->sprites[i].is_dead == 0)
		{
		update_dying_frames(&get_data()->sprites[i]);
			render_sprite(get_data()->sprites[i]);
		}
		if (should_render(get_data()->sprites + i, &angle) &&
			get_data()->sprites[i].is_dying == 0 &&
			get_data()->sprites[i].is_dead == 1)
			render_sprite(get_data()->sprites[i]);
		++i;
	}
}
