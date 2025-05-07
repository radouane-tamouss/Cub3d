/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:58:16 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:58:20 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off
void	sprint(int keycode)
{
	if (keycode == SHIFT_LIN)
		get_data()->speed = 10;
}

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
