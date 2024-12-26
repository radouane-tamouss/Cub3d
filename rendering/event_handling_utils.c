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
			play_sound("sounds/gun3reloadd.wav");
		}
	}
}

void	sprint(int keycode)
{
	if (keycode == SHIFT_LIN)
		get_data()->speed = 10;
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
