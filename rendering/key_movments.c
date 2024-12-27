/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_movments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:39:16 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:39:18 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_moving(int keycode)
{
	if (keycode == W_LIN || keycode == S_LIN || keycode == D_LIN
		|| keycode == A_LIN)
		return (1);
	else
		return (0);
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
	key_release_helper(keycode);
	if (keycode == SHIFT_LIN)
		get_data()->speed = 5;
	return (0);
}

int	handle_keys(int keycode, void *garbage)
{
	int	door_x;
	int	door_y;

	(void)garbage;
	if (keycode == ESC)
		destroy_window_and_exit();
	handle_moving(keycode);
	toggle_dark_mode(keycode);
	return (0);
}
