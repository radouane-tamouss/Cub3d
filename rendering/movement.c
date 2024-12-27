/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:10 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/20 00:28:30 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(void)
{
	t_vector	square[4];

	next_step_square(square, get_data()->player_pos,
		((float)GRID_DIST / 10), get_data()->player_dir);
	if (square[0].x != '1' && square[1].x != '1' && square[2].x != '1'
		&& square[3].x != '1'
		&& square[2].x != 'D' && square[3].x != 'D' && square[0].x != 'P'
		&& square[1].x != 'P' && square[2].x != 'P' && square[3].x != 'P')
		get_data()->player_pos.x += get_data()->player_dir.x;
	if (square[0].y != '1' && square[1].y != '1' && square[2].y != '1'
		&& square[3].y != '1' && square[0].y != 'D' && square[1].y != 'D'
		&& square[2].y != 'D' && square[3].y != 'D' && square[0].y != 'P'
		&& square[1].y != 'P' && square[2].y != 'P' && square[3].y != 'P')
		get_data()->player_pos.y += get_data()->player_dir.y;
}

void	move_backward(void)
{
	rotate_player(180 * (MY_PI / (float)180));
	move_forward();
	rotate_player(-180 * (MY_PI / (float)180));
}

void	move_right(void)
{
	rotate_player(90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(-90 * (MY_PI / (float)180));
}

void	move_left(void)
{
	rotate_player(-90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(90 * (MY_PI / (float)180));
}
