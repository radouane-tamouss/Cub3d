/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:33:28 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:33:32 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	next_step_square(t_vector *next_step_square, t_vector center,
		float square_lenght, t_vector dir)
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
	if (square[0].x != '1' && square[1].x != '1' && square[2].x != '1'
		&& square[3].x != '1' && square[0].x != 'D' && square[1].x != 'D'
		&& square[2].x != 'D' && square[3].x != 'D' && square[0].x != 'P'
		&& square[1].x != 'P' && square[2].x != 'P' && square[3].x != 'P')
		sprite->position.x += dir.x;
	if (square[0].y != '1' && square[1].y != '1' && square[2].y != '1'
		&& square[3].y != '1' && square[0].y != 'D' && square[1].y != 'D'
		&& square[2].y != 'D' && square[3].y != 'D' && square[0].y != 'P'
		&& square[1].y != 'P' && square[2].y != 'P' && square[3].y != 'P')
		sprite->position.y += dir.y;
}

void	find_display_postion(t_sprite *sprite, float angle)
{
	int		position;
	float	scale;

	position = (angle / (FOV * get_data()->zoom_factor)) * WIN_WIDTH;
	sprite->dist = ft_max(sprite->dist, 10);
	scale = ((WIN_WIDTH) / sprite->dist) * 0.1 * (1 / get_data()->zoom_factor);
	sprite->display_start_x = position + ((float)WIN_WIDTH / 2)
		- (sprite->texture.width * scale) / 2;
	sprite->display_start_y = sprite->z + scale;
	sprite->display_end_x = (sprite->texture.width * scale) / 2 + position
		+ ((float)WIN_WIDTH / 2);
	sprite->display_end_y = (sprite->texture.height * scale) + sprite->z
		+ scale;
}

int	sprite_angle_valide(t_sprite *sprite, float *angle)
{
	t_vector	vector_to_sprite;

	vector_to_sprite.x = sprite->position.x - get_data()->player_pos.x;
	vector_to_sprite.y = sprite->position.y - get_data()->player_pos.y;
	if (dot_product(vector_to_sprite, get_data()->player_dir) < 0)
		return (0);
	*angle = atan2(vector_to_sprite.y, vector_to_sprite.x)
		- normalise_angle(get_data()->player_angle);
	while (*angle >= (MY_PI) || *angle <= (-MY_PI))
	{
		if (*angle >= (MY_PI))
			*angle -= 2 * MY_PI;
		if (*angle <= (-MY_PI))
			*angle += 2 * MY_PI;
	}
	if (*angle < -((FOV * get_data()->zoom_factor) / 2) || *angle > ((FOV
				* get_data()->zoom_factor) / 2))
		return (0);
	return (1);
}

void	calc_square_points_pos(t_vector *square_position, t_vector center,
		float square_lenght)
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
