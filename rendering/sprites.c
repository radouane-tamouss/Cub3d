/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:22:52 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/30 18:21:30 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

# define ENEMY_SPEED 2.5


int	ray_hit_sprite(t_ray_data ray, t_sprite sprite)
{
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
        
        char current_tile = get_data()->map[ray.map_y][ray.map_x];

        if (current_tile == '1' || current_tile == 'D' /* || current_tile == 'O'*/) // TODO find a way to display the opened door with the sprite accorfingly
        {
            calculate_distance(&ray);
			// printf("dists :   ray ==> %f  ||| sprite ==> %f\n", ray.dist, sprite.dist);
			// printf("angles :   ray ==> %f  ||| player ==> %f\n", ray.angle, get_data()->player_angle);
			if (ray.dist < sprite.dist)
				return (0);
            return (1);
        }
    }
}

void	update_enemies_data()
{
	int	i;
	t_vector	sprite_to_player;
	float angle;
	float	magnitude;

	i = 0;
	while (i < get_data()->num_sprites)
	{
		get_data()->sprites[i].dist = calc_dist_f(get_data()->sprites[i].position.x, get_data()->sprites[i].position.y, get_data()->player_pos);
		sprite_to_player.x = get_data()->player_pos.x - get_data()->sprites[i].position.x;
		sprite_to_player.y = get_data()->player_pos.y - get_data()->sprites[i].position.y;
		angle = atan2(-sprite_to_player.y,  -sprite_to_player.x) ;//- normalise_angle(get_data()->player_angle);
		angle = normalise_angle(angle);
		// printf("angle => %f\n", angle * (180 / MY_PI));
		// printf("angles :   ray ==> %f  ||| player ==> %f\n", angle * (180 / MY_PI), get_data()->player_angle * (180 / MY_PI));
		if (ray_hit_sprite(create_ray(angle), get_data()->sprites[i]))
		{
			// printf(" y moving\n");

			magnitude = vector_magnitude(sprite_to_player);
			// printf("magnitude => %f", magnitude);
			get_data()->sprites[i].position.x += ((sprite_to_player.x) / ft_max(1, magnitude)) * ENEMY_SPEED;
			get_data()->sprites[i].position.y += ((sprite_to_player.y) / ft_max(1, magnitude)) * ENEMY_SPEED;
			// printf("player: x=>%f, y=> %f | sprite x =>%f, y=>%f\n", get_data()->player_pos.x, get_data()->player_pos.y, get_data()->sprites[i].position.x, get_data()->sprites[i].position.y);
		}
		// else
		// 	printf(" x not moving\n");
		
		i++;
	}
}
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
		pixel_y = (((float)(i - sprite.display_start_y) / (float)(sprite.display_end_y - sprite.display_start_y)) * sprite.texture.height);
		while (j < sprite.display_end_x)
		{
			pixel_x = ((float)(j - sprite.display_start_x) / (float)(sprite.display_end_x - sprite.display_start_x)) * sprite.texture.width;
			if (ray_hit_sprite(create_ray(get_data()->player_angle - (FOV/2) + (j * (FOV/WIN_WIDTH))), sprite))
			{
				// printf("ray hitted sprite`s pixel\n");
				put_pixel(&(get_data()->background_img), j , i, pull_pixel(sprite.texture, pixel_x, pixel_y));
			}
			j++;
		}
		i++;
	}
}


static void	find_display_postion(t_sprite *sprite, float angle)
{
	int	position;
	float scale;

	position =   (angle / FOV) * WIN_WIDTH;
	sprite->dist = ft_max(sprite->dist, 10);
	scale =  ((WIN_WIDTH) / sprite->dist);
	sprite->display_start_x = position + (WIN_WIDTH / 2) - (sprite->texture.width * scale) / 2, 0.;
	sprite->display_start_y = sprite->z, 0.;
	sprite->display_end_x = (sprite->texture.width * scale) / 2 + position + (WIN_WIDTH / 2), WIN_WIDTH;
	sprite->display_end_y = (sprite->texture.height * scale) + sprite->z, WIN_HEIGHT;
}

static int	should_render(t_sprite *sprite, float *angle)
{
	t_vector	vector_to_sprite;
	t_ray_data start_ray;
	t_ray_data end_ray;
	
	vector_to_sprite.x = sprite->position.x - get_data()->player_pos.x;
	vector_to_sprite.y = sprite->position.y - get_data()->player_pos.y;
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
	find_display_postion(sprite, *angle);
	start_ray = create_ray(get_data()->player_angle - (FOV/2) + (sprite->display_start_x * (FOV/WIN_WIDTH)));
	if (ray_hit_sprite(start_ray, *sprite))  //  cast ray to start of sprite to check if somthing will render
		return (1);
	end_ray = create_ray(get_data()->player_angle - (FOV/2) + (sprite->display_end_x * (FOV/WIN_WIDTH)));
	if (ray_hit_sprite(end_ray, *sprite))  // cast ray end of sprite to check if somthing will render
		return (1);
	// printf("did the ray hit\n");
	// if (ray_hit_sprite(create_ray(*angle + get_data()->player_angle), *sprite))
		// return (printf("yes it hits\n"), 1);
	// printf("no it didnt hit\n");
	return (0);
}

void	sort_sprites(void)
{
	t_sprite	tmp_sprite;
	int	i;
	int	j;
	
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

void	render_sprites(void)
{
	float angle;
	int	i;
	
	update_enemies_data();//TODO just for testin
	sort_sprites();// sorting enemies by there dist from the player
	i = 0;
	while (i < get_data()->num_sprites)
	{
		// get_data()->sprites[i].dist = calc_dist_f(get_data()->sprites[i].position.x, get_data()->sprites[i].position.y, get_data()->player_pos);
		if (get_data()->sprites[i].dist < GRID_DIST)
		{
			printf("sprite ignored\n");// TODO this will replcae dying or taking damage for now
			i++;
			continue ;
		}
		if (should_render(get_data()->sprites + i, &angle))
		{
			render_sprite(get_data()->sprites[i]);
		}
		i++;
	}
}
