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

void	handle_reload_gun(int keycode)
{
	if (keycode == R_LIN)
	{
		if (!get_data()->gun.is_showing_scope && !get_data()->gun.is_shooting)
		{
			get_data()->gun.is_reloading = 1;
			get_data()->gun.current_frame = 0;
			get_data()->gun.frame_delay = 0;
		}
	}
}

void	sprint(int keycode)
{
	if (keycode == SHIFT_LIN)
		get_data()->speed = 10;
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
			get_data()->screen_shake_timer = 9;
			break ;
		}
		i--;
	}
}
