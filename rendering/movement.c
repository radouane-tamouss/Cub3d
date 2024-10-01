/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:10 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/30 20:11:32 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward()
{
	get_data()->player_pos.x += get_data()->player_dir.x;
	get_data()->player_pos.y += get_data()->player_dir.y;
	// get_data()->player_dir.x = cos(get_data()->player_angle);
	// get_data()->player_dir.y = sin(get_data()->player_angle);
}

void	move_backward()
{
	// rotate_player(MY_PI);
	// move_forward();
	// rotate_player( -MY_PI);
	get_data()->player_pos.x -= get_data()->player_dir.x;
	get_data()->player_pos.y -= get_data()->player_dir.y;
}

void	move_right()
{
	rotate_player(-90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(90 * (MY_PI / (float)180));
}

void	move_left()
{
	rotate_player(90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(-90 * (MY_PI / (float)180));
}