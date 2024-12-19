/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 03:38:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/17 18:15:30 by eouhrich         ###   ########.fr       */
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

void render_square(int x, int y, int color)
{
	int i = 0;
	int j = 0;
	t_vector center; // TODO put it in the get_data and inital once

	center.x = 5 * SQUARE_SIZE; // TODO put it in the get_data and inital once
	center.y = 5 * SQUARE_SIZE; // TODO put it in the get_data and inital once

	while (i < SQUARE_SIZE)
	{
		j = 0;
		while (j < SQUARE_SIZE)
		{
			if (calc_dist(j + x, i + y, center) <= (5 * SQUARE_SIZE - 3))
				put_pixel(&(get_data()->background_img), j + x, i + y, color);
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
				render_square(x, y, 0x3A4A50);
			else if (get_data()->map[i][j] == '0'
				|| get_data()->map[i][j] == 'M'
				|| check_if_player_direction(get_data()->map[i][j]) == 1)
				render_square(x, y, 0xA55D35);
			else if (get_data()->map[i][j] == 'D')
				render_square(x, y, BLUE);
			else if (get_data()->map[i][j] == 'O')
				render_square(x, y, CYAN);
			++j;
		}
		++i;
	}
}

void render_player()
{
	int x, y;
	int radius = 3;
	// int radius = game->player.radius;
	int center_x = 5 * SQUARE_SIZE;//(get_data()->player_pos.x / GRID_DIST) * SQUARE_SIZE;
	int center_y = 5 * SQUARE_SIZE;//(get_data()->player_pos.y / GRID_DIST) * SQUARE_SIZE;
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
}
void render_minimap(void)
{
	int	i = 0;
	int	j;
	t_vector center; // TODO put it in the get_data and initial it once for performance porpose

	center.x = 5 * SQUARE_SIZE;
	center.y = 5 * SQUARE_SIZE;
	while (i < SQUARE_SIZE * 11)
	{
		j = 0;
		while (j < SQUARE_SIZE * 11)
		{
			if (calc_dist(j, i, center) <= (5 * SQUARE_SIZE))
				put_pixel(&(get_data()->background_img), i, j, BLACK);
			++j;
		}
		++i;
	}
	render_map();
	render_player();
}
