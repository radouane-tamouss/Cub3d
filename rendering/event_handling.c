/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/09 18:47:23 by eouhrich         ###   ########.fr       */
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
	if (keycode == ESC)
	{
		mlx_destroy_window(get_data()->mlx, get_data()->win);
		exiter(0);
	}
	else if (keycode == W)
		move_forward();
	else if (keycode == S)
		move_backward();
	else if (keycode == D)
		move_right();
	else if (keycode == A)
		move_left();
	else if (keycode == RIGHT_ARROW)
		rotate_player(2.  * (MY_PI / (float)180));
	else if (keycode == LEFT_ARROW)
		rotate_player(-2.  * (MY_PI / (float)180));
	else if (keycode == SPACE)
	{
		if (get_data()->dark_mode == 1)
			get_data()->dark_mode = 0;
		else
			get_data()->dark_mode = 1;
	}
	else if (keycode == E)
	{
		if (get_data()->front_ray.object_hitted == 1 &&  get_data()->front_ray.dist < 2 * GRID_DIST)
			get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x] = 'D';
		else if (get_data()->front_ray.object_hitted == 2 &&  get_data()->front_ray.dist < 2 * GRID_DIST)
			get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x] = 'S';
		// fprintf(stderr, "the next grid %c\n", get_data()->map[(int)next_step_y/GRID_DIST][next_step_x/GRID_DIST]);
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