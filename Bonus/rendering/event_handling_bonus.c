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

#include "../cub_bonus.h"

// clang-format off
int	ft_close(void)
{
	mlx_destroy_window(get_data()->mlx, get_data()->win);
	exiter(0);
	return (0);
}

void	update_movement(void)
{
	if (get_data()->move_forward)
		move_forward();
	if (get_data()->move_backward)
		move_backward();
	if (get_data()->move_left)
		move_left();
	if (get_data()->move_right)
		move_right();
	if (get_data()->rotate_left)
		rotate_player(-0.5f * (MY_PI / 180.0f));
	if (get_data()->rotate_right)
		rotate_player(0.5f * (MY_PI / 180.0f));
}

int	is_enemy_in_middle_of_screen(t_sprite *sprite)
{
	int		screen_middle_x;
	int		display_start_x;
	int		display_end_x;

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
