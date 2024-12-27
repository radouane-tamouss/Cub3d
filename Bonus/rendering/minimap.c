/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 03:38:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/23 15:27:55 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	render_grid_map(int x, int y, char grid)
{
	if (grid == '1')
		render_square(x, y, 0x3A4A50);
	else if (grid == '0'
		|| grid == 'M'
		|| check_if_player_direction(grid) == 1)
		render_square(x, y, 0xA55D35);
	else if (grid == 'D')
		render_square(x, y, BLUE);
	else if (grid == 'O')
		render_square(x, y, CYAN);
}

void	render_map(void)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = ft_max((get_data()->player_pos.y / GRID_DIST) - 5, 0);
	while (i < get_data()->height
		&& (i - (get_data()->player_pos.y / GRID_DIST)) < 5)
	{
		j = ft_max((get_data()->player_pos.x / GRID_DIST) - 5, 0);
		y = (i + 5) * SQUARE_SIZE
			- (get_data()->player_pos.y / GRID_DIST) * SQUARE_SIZE;
		while (j < get_data()->width
			&& (j - (get_data()->player_pos.x / GRID_DIST)) < 5)
		{
			x = (j + 5) * SQUARE_SIZE
				- (get_data()->player_pos.x / GRID_DIST) * SQUARE_SIZE;
			render_grid_map(x, y, get_data()->map[i][j]);
			++j;
		}
		++i;
	}
}

void	render_player(void)
{
	float	center;
	int		end_x;
	int		end_y;

	center = 5 * SQUARE_SIZE;
	render_cyrcle(5 * SQUARE_SIZE, 5 * SQUARE_SIZE, 3, RED);
	end_x = center + cos(get_data()->player_angle) * (5 * SQUARE_SIZE);
	end_y = center + sin(get_data()->player_angle) * (5 * SQUARE_SIZE);
	render_line(center, center, end_x, end_y);
}

void	render_minimap(void)
{
	int			i;
	int			j;
	t_vector	center;

	center.x = 5 * SQUARE_SIZE;
	center.y = 5 * SQUARE_SIZE;
	i = 0;
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
