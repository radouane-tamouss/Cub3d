/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:22:52 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/26 19:00:39 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	render_sprite(t_sprite sprite)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;
	
	i = sprite.display_start_y;
	while (i < sprite.display_end_y)
	{
		j =  sprite.display_start_x;
		while (j < sprite.display_end_x)
		{
			pixel_x = ((float)(j - sprite.display_start_x) / (float)(sprite.display_end_x - sprite.display_start_x)) * sprite.texture.width;
			pixel_y = (((float)(i - sprite.display_start_y) / (float)(sprite.display_end_y - sprite.display_start_y)) * sprite.texture.height);
			// color = pull_pixel(sprite.texture, pixel_x, pixel_y);
				put_pixel(&(get_data()->background_img), j , i, pull_pixel(sprite.texture, pixel_x, pixel_y));
			j++;
		}
		i++;
	}
}

static int	should_render(t_sprite sprite, float *angle)
{
	t_vector	vector_to_sprite;
	
	vector_to_sprite.x = sprite.position.x - get_data()->player_pos.x;
	vector_to_sprite.y = sprite.position.y - get_data()->player_pos.y;
	if (dot_product(vector_to_sprite, get_data()->player_dir) < 0)
		return (0);
	*angle = atan2(vector_to_sprite.y,  vector_to_sprite.x) - normalise_angle(get_data()->player_angle);
	//=========== normilaze angle from -PI to PI =======================
	while (*angle >= (MY_PI) || *angle <= (-MY_PI))
	{
		if (*angle >= (MY_PI))
			*angle -= 2 * MY_PI;
		if (*angle <= (-MY_PI))
			*angle += 2 * MY_PI;
	}
	//===================================================================
	if (*angle < -(FOV/2) || *angle > (FOV/2))
		return (0);
	return (1);
}

static void	find_display_postion(t_sprite *sprite, float angle)
{
	int	position;
	float scale;

	position =   (angle / FOV) * WIN_WIDTH;
	sprite->dist = calc_dist_f(sprite->position.x, sprite->position.y, get_data()->player_pos);
	sprite->dist = ft_max(sprite->dist, 10);
	scale =  ((WIN_WIDTH) / sprite->dist);
	sprite->display_start_x = position + (WIN_WIDTH / 2) - (sprite->texture.width * scale) / 2;
	sprite->display_start_y = sprite->z;
	sprite->display_end_x = (sprite->texture.width * scale) / 2 + position + (WIN_WIDTH / 2);
	sprite->display_end_y = (sprite->texture.height * scale) + sprite->z;
}

// func to render sprites
void	render_sprites(void)
{
	// t_sprite sprite;
	float angle;
	int	i;

	// sprite = get_data()->sprites;
	i = 0;
	while (i < get_data()->num_sprites)
	{
		if (should_render(get_data()->sprites[i], &angle))
		{
			find_display_postion(get_data()->sprites + i, angle);
			render_sprite(get_data()->sprites[i]);		
		}
		i++;
	}
}
