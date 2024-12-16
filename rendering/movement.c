/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:10 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/15 22:52:06 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(void)
{
	int	next_step_x;
	int	next_step_y;

	next_step_x = get_data()->player_pos.x + get_data()->player_dir.x;
	next_step_y = get_data()->player_pos.y + get_data()->player_dir.y;
	if (get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != '1'
		&& get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != 'D')
		get_data()->player_pos.y += get_data()->player_dir.y;
    else
	{
		get_data()->screen_shake_intensity = 4;
		get_data()->screen_shake_timer = 10;
	}
	if (get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != '1'
		&& get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != 'D')
		get_data()->player_pos.x += get_data()->player_dir.x;
	else
	{
		get_data()->screen_shake_intensity = 4;
		get_data()->screen_shake_timer = 10;
	}
}

void	move_backward(void)
{
	int	next_step_x = get_data()->player_pos.x - get_data()->player_dir.x;
	int	next_step_y = get_data()->player_pos.y - get_data()->player_dir.y;

	if (get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != '1'
		&& get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != 'D')
		get_data()->player_pos.y -= get_data()->player_dir.y;
	if (get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != '1'
		&& get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != 'D')
 		get_data()->player_pos.x -= get_data()->player_dir.x;
}

void	move_right(void)
{
	rotate_player(90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(-90 * (MY_PI / (float)180));
}

void	move_left(void)
{
	rotate_player(-90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(90 * (MY_PI / (float)180));
}
