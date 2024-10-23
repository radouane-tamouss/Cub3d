/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/22 02:45:42 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_close(void)
{
	exiter(0);
	return (0);
}



int	handle_keys(int keycode, void *garbage)
{
	(void)garbage;
	// printf("keycode => %d\n", keycode);
	if (keycode == ESC_MAC)
	{
		mlx_destroy_window(get_data()->mlx, get_data()->win);
		exiter(0);
	}
	else if (keycode == W_MAC)
		move_forward();
	else if (keycode == S_MAC)
		move_backward();
	else if (keycode == D_MAC)
		move_right();
	else if (keycode == A_MAC)
		move_left();
	else if (keycode == RIGHT_MAC)
		rotate_player(2.  * (MY_PI / (float)180));
	else if (keycode == LEFT_MAC)
		rotate_player(-2.  * (MY_PI / (float)180));
	else if (keycode == SPACE_MAC)
	{
		if (get_data()->dark_mode == 1)
			get_data()->dark_mode = 0;
		else
			get_data()->dark_mode = 1;
	}
	else if (keycode == E_MAC)
	{
		if (get_data()->front_ray.object_hitted == 1 &&  get_data()->front_ray.dist < 2 * GRID_DIST)
			get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x] = 'D';
		else if (get_data()->front_ray.object_hitted == 2 &&  get_data()->front_ray.dist < 2 * GRID_DIST)
			get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x] = 'S';
		// fprintf(stderr, "the next grid %c\n", get_data()->map[(int)next_step_y/GRID_DIST][next_step_x/GRID_DIST]);
	}
	else  if (keycode == T_MAC)  // Add proper key define if needed
    {
        get_data()->gun.is_shooting = 1;
        get_data()->gun.current_frame = 0;
        get_data()->gun.frame_delay = 0;
    }
	else
		return (0);
	get_data()->is_updated = 1;
	// init_background();
	// // draw_player();
	// render_walls();
	// render_background();
	// printf("\n\n\n");
	// printf("===== coords (%f, %f)\n", get_data()->player_pos.x / GRID_DIST, get_data()->player_pos.y/ GRID_DIST);
	// printf("===== directoin vector (%f, %f)\n", get_data()->player_dir.x, get_data()->player_dir.y);
	// printf("===== angle %f degree\n", get_data()->player_angle * (180 / MY_PI));
	return (0);
}

// int	handle_realise(int keycode, void *garbage)
// {
// 	// if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == )
// 		get_data()->is_updated = 0;

// }

int mouse_event(int x, int y, void *par)
{
	(void)par;
	// if (get_data()->mouse_pos.x > x)
	// 	rotate_player(-.5 * (MY_PI / 180));
	// else
	// 	rotate_player(.5 * (MY_PI / 180));
	rotate_player(-.5 *(get_data()->mouse_pos.x - x) * (MY_PI / 180));
	get_data()->mouse_pos.x = x;
	get_data()->is_updated = 1;

	// init_background();
	// render_walls();
	// render_background();
	// fprintf(stderr,"mouse moved x = %d, y = %d\n", x, y);
	// exit(0);
	return (0);
	// mlx_mouse_get_pos
}