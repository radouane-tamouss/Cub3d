/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:37:26 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:37:30 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// clang-format off
void	handle_left_mouse_click(void)
{
	if (!get_data()->gun.is_reloading && !get_data()->gun.is_showing_scope)
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
	}
}

void	handle_right_mouse_click(void)
{
	if (!get_data()->gun.is_reloading && !get_data()->gun.is_shooting
		&& !get_data()->gun.is_showing_scope)
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
	(void) x;
	(void) y;
	(void) param;
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
	(void)y;
	rotate_player(-.5 * (get_data()->mouse_pos.x - x) * (MY_PI / 180));
	get_data()->mouse_pos.x = x;
	return (0);
}
