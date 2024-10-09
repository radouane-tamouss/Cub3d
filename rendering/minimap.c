/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 03:38:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/09 03:43:28 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void render_line(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double max = fmax(fabs(dx), fabs(dy));

    double x_step = dx / max;
    double y_step = dy / max;

    double x = x1;
    double y = y1;

    for (int i = 0; i <= max; i++)
    {
        put_pixel(&(get_data()->background_img), x, y, RED);
        x += x_step;
        y += y_step;
    }
}

void render_wall(int x, int y)
{
	int i = 0;
	int j = 0;

	while (i < SQUARE_SIZE - 1)
	{
		j = 0;
		while (j < SQUARE_SIZE - 1)
		{
			// mlx_pixel_put(game->mlx, game->win, j + x, i + y, RED);
			put_pixel(&(get_data()->background_img), j + x, i + y, CYAN);
			j++;
		}
		i++;
	}
}

void render_floor(int x, int y)
{
	int i = 0;
	int j = 0;
	while(i < SQUARE_SIZE - 1)
	{
		j = 0;
		while(j < SQUARE_SIZE - 1)
		{
			// mlx_pixel_put(game->mlx, game->win, j + x, i + y, game->floor.r << 16 | game->floor.g << 8 | game->floor.b);
			put_pixel(&(get_data()->background_img), j + x, i + y, get_data()->floor_color);
			j++;
		}
		i++;
	}
}
void render_map(void)
{
	int i,j;
	int x,y;
	i = ft_max((get_data()->player_pos.y / GRID_DIST) - 5, 0);
	while(i < get_data()->height && (i - (get_data()->player_pos.y / GRID_DIST)) < 5)
	{
		j = ft_max((get_data()->player_pos.x / GRID_DIST) - 5, 0);
		y = (i + 5) * SQUARE_SIZE - (get_data()->player_pos.y / GRID_DIST) * SQUARE_SIZE;
		while (j < get_data()->width && (j - (get_data()->player_pos.x / GRID_DIST)) < 5)
		{
			x = (j +  5) * SQUARE_SIZE - (get_data()->player_pos.x / GRID_DIST) * SQUARE_SIZE;
			if (get_data()->map[i][j] == '1')
			{
				render_wall(x, y);
			}
			else
			{
				render_floor(x, y);
			}
			// else if (check_if_player_direction(get_data()->map[i][j]) == 1)
			// {
			// 	render_floor(x, y);
			// }
			j++;
		}
		i++;
	}
}

// void render_ray(t_game *game, t_ray ray)
// {
// 	// Calculate the end point of the ray
// 	int center_x = game->player.pos_y * SQUARE_SIZE + SQUARE_SIZE / 2;
// 	int center_y = game->player.pos_x * SQUARE_SIZE + SQUARE_SIZE / 2;
// 	int end_x = center_x + cos(ray.ray_angle) * 80;
// 	int end_y = center_y + sin(ray.ray_angle) * 80;

// 	// Render the ray
// 	render_line(center_x, center_y, end_x, end_y);
// }
// void render_rays(t_game *game)
// {
// 	int i = 0;
// 	while (i < game->num_rays)
// 	{
// 		render_ray(game, game->rays[i]);
// 		i++;
// 	}
// }
void render_player()
{
	int x, y;
	int radius = 3;
	// int radius = game->player.radius;
	int center_x = 5 * SQUARE_SIZE;//(get_data()->player_pos.x / GRID_DIST) * SQUARE_SIZE;
	int center_y = 5 * SQUARE_SIZE;//(get_data()->player_pos.y / GRID_DIST) * SQUARE_SIZE;

	// fprintf(stderr, "x== %d,  y==%d\n", center_x, center_y);

	for (y = -radius; y <= radius; y++)
	{
		for (x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				put_pixel(&(get_data()->background_img), center_x + x, center_y + y, RED);
			}
		}
	}
	// Calculate the end point of the direction line
    int end_x = center_x + cos(get_data()->player_angle) * 80;
    int end_y = center_y + sin(get_data()->player_angle) * 80;
	render_line(center_x, center_y, end_x, end_y);
	// render_rays(game);
}
void render_minimap(void)
{
	
	int	i = 0;
	int	j;
	while (i < SQUARE_SIZE * 11)
	{
		j = 0;
		while (j < SQUARE_SIZE * 11)
		{
			put_pixel(&(get_data()->background_img), i, j, BLACK);
			j++;
		}
		i++;
	}
	render_map();
	render_player();
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
