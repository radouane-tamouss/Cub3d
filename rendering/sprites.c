/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:22:52 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/06 16:52:27 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"




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
            calculate_ray_distance(&ray);
			// printf("dists :   ray ==> %f  ||| sprite ==> %f\n", ray.dist, sprite.dist);
			// printf("angles :   ray ==> %f  ||| player ==> %f\n", ray.angle, get_data()->player_angle);
			if (ray.dist < sprite.dist)
				return (0);
            return (1);
        }
    }
}



void	enemy_move(t_sprite *sprite, t_vector dir)
{
	float	magnitude = ft_max(vector_magnitude(dir), 1.0);
	dir.x = (dir.x / magnitude) * ENEMY_SPEED;
	dir.y = (dir.y / magnitude) * ENEMY_SPEED;

	float	d_square = (GRID_DIST/8) ;//
	t_vector a;
	a.x = sprite->position.x - d_square;
	a.y = sprite->position.y - d_square;
	t_vector b;
	b.x = sprite->position.x + d_square;
	b.y = sprite->position.y - d_square;
	t_vector c;
	c.x = sprite->position.x - d_square;
	c.y = sprite->position.y + d_square;
	t_vector d;
	d.x = sprite->position.x + d_square;
	d.y = sprite->position.y + d_square;
	////////////////////////////////////////
	int next_map_x_a = get_data()->map[(int)a.y/GRID_DIST][(int)(a.x  + dir.x)/GRID_DIST];
    int next_map_y_a = get_data()->map[(int)(a.y + dir.y)/GRID_DIST][(int)(a.x)/GRID_DIST];

	int next_map_x_b = get_data()->map[(int)b.y/GRID_DIST][(int)(b.x + dir.x)/GRID_DIST];
    int next_map_y_b = get_data()->map[(int)(b.y + dir.y)/GRID_DIST][(int)(b.x)/GRID_DIST]; 

	int next_map_x_c = get_data()->map[(int)c.y/GRID_DIST][(int)(c.x + dir.x)/GRID_DIST]; 
    int next_map_y_c = get_data()->map[(int)(c.y + dir.y)/GRID_DIST][(int)(c.x)/GRID_DIST]; 

	int next_map_x_d = get_data()->map[(int)d.y/GRID_DIST][(int)(d.x + dir.x)/GRID_DIST]; 
    int next_map_y_d = get_data()->map[(int)(d.y + dir.y)/GRID_DIST][(int)(d.x)/GRID_DIST]; 

	if (next_map_x_a != '1' && next_map_x_b != '1' && next_map_x_c != '1'
		&& next_map_x_d != '1' && next_map_x_a != 'D' && next_map_x_b != 'D'
		&& next_map_x_c != 'D' && next_map_x_d != 'D' && next_map_x_a != 'P'
		&& next_map_x_b != 'P'&& next_map_x_c != 'P' && next_map_x_d != 'P')
        sprite->position.x += dir.x;
    if (next_map_y_a != '1' && next_map_y_b != '1' && next_map_y_c != '1'
		&& next_map_y_d != '1' && next_map_y_a != 'D' && next_map_y_b != 'D'
        && next_map_y_c != 'D' && next_map_y_d != 'D' && next_map_y_a != 'P'
		&& next_map_y_b != 'P' && next_map_y_c != 'P' && next_map_y_d != 'P')
        sprite->position.y += dir.y;
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
		angle = atan2(-sprite_to_player.y,  -sprite_to_player.x);
		angle = normalise_angle(angle);
		enemy_move(get_data()->sprites + i, sprite_to_player);
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
		pixel_y = (((float)(i - sprite.display_start_y)
			/ (float)(sprite.display_end_y - sprite.display_start_y))
			* sprite.texture.height);
		while (j < sprite.display_end_x)
		{
			pixel_x = ((float)(j - sprite.display_start_x)
				/ (float)(sprite.display_end_x - sprite.display_start_x))
				* sprite.texture.width;
			if (ray_hit_sprite(create_ray(get_data()->player_angle
				- (FOV/2) + (j * (FOV/WIN_WIDTH))), sprite))
				put_pixel(&(get_data()->background_img), j , i,
					pull_pixel(sprite.texture, pixel_x, pixel_y));
			j++;
		}
		i++;
	}
}

static void	find_display_postion(t_sprite *sprite, float angle)
{
	int	position;
	float scale;

	position = (angle / FOV) * WIN_WIDTH;
	sprite->dist = ft_max(sprite->dist, 10);
	scale =  ((WIN_WIDTH) / sprite->dist);
	sprite->display_start_x = position + (WIN_WIDTH / 2)
		- (sprite->texture.width * scale) / 2;
	sprite->display_start_y = sprite->z;
	sprite->display_end_x = (sprite->texture.width * scale) / 2
		+ position + (WIN_WIDTH / 2);
	sprite->display_end_y = (sprite->texture.height * scale) + sprite->z;
}

static int	sprite_angle_valide(t_sprite *sprite, float	*angle)
{
	t_vector	vector_to_sprite;
	
	vector_to_sprite.x = sprite->position.x - get_data()->player_pos.x;
	vector_to_sprite.y = sprite->position.y - get_data()->player_pos.y;
	if (dot_product(vector_to_sprite, get_data()->player_dir) < 0)
		return (0);
	*angle = atan2(vector_to_sprite.y,  vector_to_sprite.x)
		- normalise_angle(get_data()->player_angle);
	while (*angle >= (MY_PI) || *angle <= (-MY_PI))
	{
		if (*angle >= (MY_PI))
			*angle -= 2 * MY_PI;
		if (*angle <= (-MY_PI))
			*angle += 2 * MY_PI;
	}
	if (*angle < -(FOV/2) || *angle > (FOV/2))
		return (0);
	return	(1);
}

static int	should_render(t_sprite *sprite, float *angle)
{
	t_vector	vector_to_sprite;
	t_ray_data start_ray;
	t_ray_data end_ray;
	
	if (!sprite_angle_valide(sprite, angle))
		return (0);
	find_display_postion(sprite, *angle);
	start_ray = create_ray(get_data()->player_angle - (FOV/2) + (sprite->display_start_x * (FOV/WIN_WIDTH)));
	if (ray_hit_sprite(start_ray, *sprite))
		return (1);
	end_ray = create_ray(get_data()->player_angle - (FOV/2) + (sprite->display_end_x * (FOV/WIN_WIDTH)));
	if (ray_hit_sprite(end_ray, *sprite))
	return (0);
}

// sorting enemies by there dist from the player
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
	
	update_enemies_data();
	sort_sprites();
	i = 0;
	while (i < get_data()->num_sprites)
	{
		if (get_data()->sprites[i].dist < GRID_DIST)
		{
			printf("sprite ignored\n");// TODO this will replcae dying or taking damage for now
			i++;
			continue ;
		}
		if (should_render(get_data()->sprites + i, &angle))
			render_sprite(get_data()->sprites[i]);
		i++;
	}
}
