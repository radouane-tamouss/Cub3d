/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 01:41:00 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 01:41:00 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_close(void)
{
	mlx_destroy_window(get_data()->mlx, get_data()->win);
	exiter(0);
	return (0);
}

void	play_sound(const char *file)
{
	char	command[256];
	char	*temp;
	char	*command_str;
	int		result;

	temp = ft_strjoin("paplay ", file);
	command_str = ft_strjoin(temp, " &");
	ft_strlcpy(command, command_str, sizeof(command));
	result = system(command);
	if (result == -1)
	{
		perror("system");
	}
}

void	update_movement(void)
{
	float	move_speed;

	move_speed = 0.7;
	if (get_data()->move_forward)
		move_forward();
	if (get_data()->move_backward)
		move_backward();
	if (get_data()->move_left)
		move_left();
	if (get_data()->move_right)
		move_right();
	if (get_data()->rotate_left)
		rotate_player(-3.0f * (MY_PI / 180.0f));
	if (get_data()->rotate_right)
		rotate_player(3.0f * (MY_PI / 180.0f));
}

int	is_enemy_in_middle_of_screen(t_sprite *sprite)
{
	t_data	*data;
	int		screen_middle_x;
	int		display_start_x;
	int		display_end_x;

	data = get_data();
	screen_middle_x = WIN_WIDTH / 2;
	if (sprite != NULL && sprite->is_dead == 0)
	{
		display_start_x = sprite->display_start_x;
		display_end_x = sprite->display_end_x;
		if (screen_middle_x >= display_start_x
			&& screen_middle_x <= display_end_x)
		{
			return (1);
		}
	}
	return (0);
}

void	destroy_window_and_exit(void)
{
	mlx_destroy_window(get_data()->mlx, get_data()->win);
	exiter(0);
}

int	is_moving(int keycode)
{
	if (keycode == W_LIN || keycode == S_LIN || keycode == D_LIN
		|| keycode == A_LIN)
		return (1);
	else
		return (0);
}

void	toggle_dark_mode(int keycode)
{
	if (keycode == SPACE_LIN)
	{
		if (get_data()->dark_mode == 1)
			get_data()->dark_mode = 0;
		else
			get_data()->dark_mode = 1;
	}
}

void	handle_moving(int keycode)
{
	if (keycode == W_LIN)
		get_data()->move_forward = 1;
	if (keycode == S_LIN)
		get_data()->move_backward = 1;
	if (keycode == D_LIN)
		get_data()->move_right = 1;
	if (keycode == A_LIN)
		get_data()->move_left = 1;
	if (keycode == RIGHT_LIN)
		get_data()->rotate_right = 1;
	if (keycode == LEFT_LIN)
		get_data()->rotate_left = 1;
}

void	control_speed(void)
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

void	handle_door_helper(int door_x, int door_y)
{
	door_x = get_data()->front_ray.map_x;
	door_y = get_data()->front_ray.map_y;
	if (get_data()->map[door_y][door_x] == 'D')
	{
		get_data()->map[door_y][door_x] = 'P';
		get_data()->door.is_opening = 1;
		get_data()->door.current_frame = 0;
		get_data()->door.frame_delay = 2;
	}
	else if (get_data()->map[door_y][door_x] == 'O')
	{
		get_data()->map[door_y][door_x] = 'P';
		get_data()->door.is_closing = 1;
		get_data()->door.current_frame = 16;
		get_data()->door.frame_delay = 0;
	}
}

void	handle_door(int keycode)
{
	int	door_x;
	int	door_y;

	if (keycode == E_LIN)
	{
		if ((get_data()->front_ray.object_hitted == 'D'
				|| get_data()->front_ray.object_hitted == 'O')
			&& get_data()->front_ray.dist < 2 * GRID_DIST
			&& !get_data()->door.is_opening && !get_data()->door.is_closing)
		{
			handle_door_helper(door_x, door_y);
			play_sound("sounds/door.wav");
		}
	}
}

void	handle_reload_gun(int keycode)
{
	if (keycode == R_LIN)
	{
		if (!get_data()->gun.is_showing_scope && !get_data()->gun.is_shooting)
		{
			get_data()->gun.is_reloading = 1;
			get_data()->gun.current_frame = 0;
			get_data()->gun.frame_delay = 0;
			play_sound("sounds/gun3reloadd.wav");
		}
	}
}

void	sprint(int keycode)
{
	if (keycode == SHIFT_LIN)
		get_data()->speed = 10;
}

int	handle_keys(int keycode, void *garbage)
{
	int	door_x;
	int	door_y;

	(void)garbage;
	if (keycode == ESC)
		destroy_window_and_exit();
	if (is_moving(keycode))
		control_speed();
	handle_moving(keycode);
	toggle_dark_mode(keycode);
	handle_door(keycode);
	handle_reload_gun(keycode);
	sprint(keycode);
	return (0);
}

void	key_release_helper(int keycode)
{
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
}

int	key_release(int keycode, void *garbage)
{
	(void)garbage;
	if (keycode == CNTRL_LIN)
	{
		get_data()->is_control_pressed = 0;
	}
	key_release_helper(keycode);
	if (keycode == SHIFT_LIN)
		get_data()->speed = 5;
	if (is_moving(keycode))
	{
		if (get_data()->move_backward == 0 && get_data()->move_forward == 0
			&& get_data()->move_left == 0 && get_data()->move_right == 0)
		{
			get_data()->is_running = 0;
			get_data()->is_walking = 0;
		}
	}
	return (0);
}

void	kill_enemies(void)
{
	int		i;
	float	angle;

	i = get_data()->num_sprites - 1;
	while (i >= 0)
	{
		if (is_enemy_in_middle_of_screen(&get_data()->sprites[i])
			&& should_render(&get_data()->sprites[i], &angle))
		{
			get_data()->sprites[i].is_dying = 1;
			get_data()->sprites[i].current_frame = 0;
			get_data()->screen_shake_timer = 10;
			break ;
		}
		i--;
	}
}

void	handle_left_mouse_click(void)
{
	if (!get_data()->gun.is_reloading
		&& !get_data()->gun.is_showing_scope)
	{
		get_data()->gun.is_shooting = 1;
		get_data()->gun.current_frame = 0;
		get_data()->gun.frame_delay = 0;
		get_data()->gun.is_reloading = 0;
		get_data()->is_running = 0;
		get_data()->is_walking = 0;
		get_data()->gun.is_showing_scope = 0;
		get_data()->screen_shake_intensity = 5;
		kill_enemies();
		get_data()->screen_shake_timer = 10;
		play_sound("sounds/one_shot_firstgun.wav");
		get_data()->number_of_shoots++;
	}
}

void	decrease_zoom_factor(void)
{
	get_data()->zoom_factor -= 0.04;
	if (get_data()->zoom_factor < 0.7)
		get_data()->zoom_factor = 0.7;
}

void	increase_zoom_factor(void)
{
	get_data()->zoom_factor += 0.04;
	if (get_data()->zoom_factor > 1)
		get_data()->zoom_factor = 1;
}

void	handle_right_mouse_click(void)
{
	if (!get_data()->gun.is_reloading
		&& !get_data()->gun.is_shooting && !get_data()->gun.is_showing_scope)
	{
		get_data()->gun.current_frame = 0;
		get_data()->gun.frame_delay = 0;
		get_data()->gun.is_showing_scope = 1;
		if (get_data()->gun.show_scope)
			get_data()->gun.show_scope = 0;
		else if (!get_data()->gun.show_scope)
			get_data()->gun.show_scope = 1;
	}
}

int	handle_mouse_event(int button, int x, int y, void *param)
{
	if (button == 1)
		handle_left_mouse_click();
	else if (button != 1 && button == 3)
		handle_right_mouse_click();
	else if (button == 4)
		decrease_zoom_factor();
	else if (button == 5)
		increase_zoom_factor();
	return (0);
}

int	mouse_event(int x, int y, void *par)
{
	(void)par;
	rotate_player(-.5 * (get_data()->mouse_pos.x - x) * (MY_PI / 180));
	get_data()->mouse_pos.x = x;
	return (0);
}
