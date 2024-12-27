/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:23:06 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:23:40 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//clang-format off
#include "../cube.h"

void	sort_sprites(void)
{
	t_sprite	tmp_sprite;
	int			i;
	int			j;

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

void	render_sprite_helper(t_sprite sprite, int *pixel_x, int i, int j)
{
	int	pixel_y;

	pixel_y = (((float)(i - sprite.display_start_y)
				/ (float)(sprite.display_end_y - sprite.display_start_y))
			* sprite.texture.height);
	if (sprite.is_dead == 0 && sprite.is_dying == 0)
		put_pixel(&(get_data()->background_img), j, i,
			pull_pixel(get_data()->sprites_frames[sprite.current_frame],
				*pixel_x, pixel_y));
	else if (sprite.is_dying == 1 && sprite.is_dead == 0)
		put_pixel(&(get_data()->background_img), j, i,
			pull_pixel(get_data()->dying_frames[sprite.current_dying_frame],
				*pixel_x, pixel_y));
	else if (sprite.is_dead == 1)
		put_pixel(&(get_data()->background_img), j, i,
			pull_pixel(get_data()->dying_frames[14], *pixel_x, pixel_y));
	else
		put_pixel(&(get_data()->background_img), j, i,
			pull_pixel(get_data()->sprites_frames[sprite.current_frame],
				*pixel_x, pixel_y));
}

int	should_render(t_sprite *sprite, float *angle)
{
	t_vector	vector_to_sprite;
	t_ray_data	start_ray;
	t_ray_data	end_ray;

	if (!sprite_angle_valide(sprite, angle))
		return (0);
	find_display_postion(sprite, *angle);
	start_ray = create_ray(get_data()->player_angle - ((FOV
					* get_data()->zoom_factor) / 2) + (sprite->display_start_x
				* ((FOV * get_data()->zoom_factor) / WIN_WIDTH)));
	if (ray_hit_sprite(start_ray, *sprite))
		return (1);
	end_ray = create_ray(get_data()->player_angle - ((FOV
					* get_data()->zoom_factor) / 2) + (sprite->display_end_x
				* ((FOV * get_data()->zoom_factor) / WIN_WIDTH)));
	if (ray_hit_sprite(end_ray, *sprite))
		return (1);
	return (0);
}

void	render_sprite(t_sprite sprite)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	j = ft_max(sprite.display_start_x, 0.0f);
	while (j < sprite.display_end_x && j < WIN_WIDTH)
	{
		if (ray_hit_sprite(create_ray(get_data()->player_angle - ((FOV
							* get_data()->zoom_factor) / 2) + (j * ((FOV
								* get_data()->zoom_factor) / WIN_WIDTH))),
				sprite))
		{
			pixel_x = ((float)(j - sprite.display_start_x)
					/ (float)(sprite.display_end_x - sprite.display_start_x))
				* sprite.texture.width;
			i = ft_max(sprite.display_start_y, 0.0f);
			while (i < sprite.display_end_y && i < WIN_HEIGHT)
			{
				render_sprite_helper(sprite, &pixel_x, i, j);
				++i;
			}
		}
		++j;
	}
}

void	render_sprites(void)
{
	float	angle;
	int		i;
	t_data	*data;

	data = get_data();
	update_enemies_data();
	sort_sprites();
	i = -1;
	while (++i < data->num_sprites)
	{
		if (data->sprites[i].dist < GRID_DIST)
			continue ;
		if (should_render(data->sprites + i, &angle)
			&& data->sprites[i].is_dead == 0)
			(update_enemy_frames(), render_sprite(data->sprites[i]));
		if (should_render(data->sprites + i, &angle)
			&& data->sprites[i].is_dying == 1 && data->sprites[i].is_dead == 0)
			(update_dying_frames(&data->sprites[i]),
				render_sprite(data->sprites[i]));
		if (should_render(data->sprites + i, &angle)
			&& data->sprites[i].is_dying == 0 && data->sprites[i].is_dead == 1)
			render_sprite(data->sprites[i]);
	}
}
