/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:10 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/14 13:43:28 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// void	move_forward()
// {
// 	int	next_step_x = get_data()->player_pos.x + get_data()->player_dir.x;
// 	int	next_step_y = get_data()->player_pos.y + get_data()->player_dir.y;

// 	// if (get_data()->map[next_step_y/GRID_DIST][next_step_x/GRID_DIST] != '1')
// 	// {
// 	// 	get_data()->player_pos.x += get_data()->player_dir.x;
// 	// 	get_data()->player_pos.y += get_data()->player_dir.y;
// 	// }
// 	if (get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != '1'
// 		&&	get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != 'D')
// 		get_data()->player_pos.y += get_data()->player_dir.y;
// 	if (get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != '1'
// 		&& get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != 'D')
// 		get_data()->player_pos.x += get_data()->player_dir.x;
// }

// void	move_backward()
// {
// 	// rotate_player(MY_PI);
// 	// move_forward();
// 	// rotate_player( -MY_PI);
// 	int	next_step_x = get_data()->player_pos.x - get_data()->player_dir.x;
// 	int	next_step_y = get_data()->player_pos.y - get_data()->player_dir.y;
	
// 	if (get_data()->map[next_step_y/GRID_DIST][next_step_x/GRID_DIST] != '1')
// 	{
// 		get_data()->player_pos.x -= get_data()->player_dir.x;
// 		get_data()->player_pos.y -= get_data()->player_dir.y;
// 	}
// }
void	move_forward()
{
    int	next_step_x = get_data()->player_pos.x + get_data()->player_dir.x;
    int	next_step_y = get_data()->player_pos.y + get_data()->player_dir.y;

    if (get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != '1'
        && get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST] != 'D')
        get_data()->player_pos.y += get_data()->player_dir.y;
    if (get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != '1'
        && get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST] != 'D')
        get_data()->player_pos.x += get_data()->player_dir.x;
}

void	move_backward()
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

void	move_right()
{
	rotate_player(90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(-90 * (MY_PI / (float)180));
}

void	move_left()
{
	rotate_player(-90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(90 * (MY_PI / (float)180));
}