/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/18 02:43:06by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int ft_close(void)
{
	exiter(0);
	return (0);
}

void play_sound(const char *file)
{
	char command[256];
	char *temp = ft_strjoin("paplay ", file);
	char *command_str = ft_strjoin(temp, " &");
	ft_strlcpy(command, command_str, sizeof(command));

	int result = system(command);
	if (result == -1)
	{
		perror("system");
	}
}

void update_movement()
{
	// the parallax effecy achieved by moving the gun in the opposite direction
	// of the player the gun_offset_x is used to move the gun in the opposite
	// direction of the player the gun_offset_x is then multiplied by 0.9 to
	// slow down the movement of the gun

	float move_speed = 0.7;

	if (get_data()->move_forward) move_forward();
	if (get_data()->move_backward) move_backward();
	if (get_data()->move_left)
	{
		move_left();
		get_data()->gun_offset_x -= move_speed;
	}
	if (get_data()->move_right)
	{
		move_right();
		get_data()->gun_offset_x += move_speed;
	}
	if (get_data()->rotate_left)
	{
		rotate_player(-3.0f * (MY_PI / 180.0f));
		get_data()->gun_offset_x -= move_speed;
	}
	if (get_data()->rotate_right)
	{
		rotate_player(3.0f * (MY_PI / 180.0f));
		get_data()->gun_offset_x += move_speed;
	}

	get_data()->gun_offset_x *= 0.9;
}

int is_enemy_in_middle_of_screen(t_sprite *sprite)
{
	t_data *data = get_data();
	int screen_middle_x = WIN_WIDTH / 2;

	if (sprite != NULL && sprite->is_dead == 0)
	{
		int display_start_x = sprite->display_start_x;
		int display_end_x = sprite->display_end_x;

		if (screen_middle_x >= display_start_x &&
			screen_middle_x <= display_end_x)
		{
			return 1;
		}
	}
	return 0;
}

int handle_keys(int keycode, void *garbage)
{
	(void)garbage;
	if (keycode == ESC)
	{
		mlx_destroy_window(get_data()->mlx, get_data()->win);
		exiter(0);
	}
	if (keycode == CNTRL_LIN)
		get_data()->is_control_pressed = 1;
	if (keycode == W_LIN || keycode == S_LIN || keycode == D_LIN ||
		keycode == A_LIN)
	{
		if (get_data()->speed >= 10)
		{
			get_data()->is_running = 1;
			get_data()->is_walking = 0;
		}
		else
		{
			get_data()->is_running = 0;
			get_data()->is_walking = 1;
		}
	}
	if (keycode == W_LIN) get_data()->move_forward = 1;
	if (keycode == S_LIN) get_data()->move_backward = 1;
	if (keycode == D_LIN) get_data()->move_right = 1;
	if (keycode == A_LIN)
	{
		get_data()->move_left = 1;
	}
	if (keycode == RIGHT_LIN) get_data()->rotate_right = 1;
	if (keycode == LEFT_LIN) get_data()->rotate_left = 1;
	if (keycode == SPACE_LIN)
	{
		if (get_data()->dark_mode == 1)
			get_data()->dark_mode = 0;
		else
			get_data()->dark_mode = 1;
	}
	if (keycode == E_LIN)
	{
		if ((get_data()->front_ray.object_hitted == 'D' ||
			 get_data()->front_ray.object_hitted == 'O') &&
			get_data()->front_ray.dist < 2 * GRID_DIST)
		{
			int door_x = get_data()->front_ray.map_x;
			int door_y = get_data()->front_ray.map_y;

			// Check if it's a door and not already animating
			if (get_data()->map[door_y][door_x] == 'D')
			{
				// Mark this door as animating with 'P'
				get_data()->map[door_y][door_x] = 'P';
				get_data()->door.is_opening = 1;
				get_data()->door.current_frame = 0;
				get_data()->door.frame_delay = 2;
				// get_data()->is_updated = 1;
			}
			else if (get_data()->map[door_y][door_x] == 'O')
			{
				// Mark this door as animating closed with 'P'
				get_data()->map[door_y][door_x] = 'P';
				get_data()->door.is_closing = 1;
				get_data()->door.current_frame = 16;
				get_data()->door.frame_delay = 0;
			}
			play_sound("sounds/door.wav");
		}
	}
	if (keycode == T_LIN)  // Add proper key define if needed
	{
			get_data()->gun.is_reloading = 1;
			get_data()->gun.current_frame = 0;
			get_data()->gun.frame_delay = 0;
			play_sound("sounds/gun3reloadd.wav");
		// }
	}
	if (keycode == Z_LIN)
	{
			get_data()->gun.current_frame = 0;
			get_data()->gun.frame_delay = 0;
			get_data()->gun.is_showing_scope = 1;
			if (get_data()->gun.show_scope)
			{
				get_data()->gun.show_scope = 0;
				printf("setted to 0\n");
			}
			else if (!get_data()->gun.show_scope)
			{
				get_data()->gun.show_scope = 1;
				printf("setted to 1\n");
			}
	}
	if (keycode == SHIFT_LIN)
	{
		get_data()->speed = 10;
	}
	return (0);
}

int key_release(int keycode, void *garbage)
{
	(void)garbage;
	if (keycode == CNTRL_LIN)
	{
		get_data()->is_control_pressed = 0;
	}
	if (keycode == W_LIN)
		get_data()->move_forward = 0;
	else if (keycode == S_LIN)
		get_data()->move_backward = 0;
	else if (keycode == D_LIN)
		get_data()->move_right = 0;
	else if (keycode == A_LIN)
		get_data()->move_left = 0;
	if (keycode == RIGHT_LIN)
		get_data()->rotate_right = 0;
	else if (keycode == LEFT_LIN)
		get_data()->rotate_left = 0;
	else if (keycode == Z_LIN)
		get_data()->show_scope = 0;
	else if (keycode == SHIFT_LIN)
		get_data()->speed = 8;
	if (keycode == W_LIN || keycode == S_LIN || keycode == D_LIN ||
		keycode == A_LIN)
	{
		if (get_data()->move_backward == 0 && get_data()->move_forward == 0 &&
			get_data()->move_left == 0 && get_data()->move_right == 0)
		{
			get_data()->is_running = 0;
			get_data()->is_walking = 0;
		}
	}
	return (0);
}

int handle_mouse_event(int button, int x, int y, void *param)
{
	if (button == 1)
	{
		if (!get_data()->gun.is_reloading)
		{
			get_data()->gun.is_shooting = 1;
			get_data()->gun.current_frame = 0;
			get_data()->gun.frame_delay = 0;
			get_data()->gun.is_reloading = 0;
			get_data()->is_running = 0;
			get_data()->is_walking = 0;
			get_data()->gun.is_showing_scope = 0;
			get_data()->screen_shake_intensity =
				5;	// Adjust intensity as needed
			// printf("num sprites: %d\n", get_data()->num_sprites);
			for (int i = get_data()->num_sprites - 1; i >= 0; --i)
			{
				float angle;
				if (is_enemy_in_middle_of_screen(&get_data()->sprites[i]) &&
					should_render(&get_data()->sprites[i], &angle))
				{
					get_data()->sprites[i].is_dying = 1;
					get_data()->sprites[i].current_frame = 0;
					// get_data()->is_updated = 1;
					get_data()->screen_shake_timer =
						10;	 // Adjust duration as needed
					break;
				}
			}
			get_data()->screen_shake_timer = 10;  // Adjust duration as needed
			play_sound("sounds/one_shot_firstgun.wav");
			get_data()->number_of_shoots++;
		}
	}
	return (0);
}

int mouse_event(int x, int y, void *par)
{
	(void)par;
	rotate_player(-.5 * (get_data()->mouse_pos.x - x) * (MY_PI / 180));
	get_data()->mouse_pos.x = x;
	// get_data()->is_updated = 1;
	return (0);
}
