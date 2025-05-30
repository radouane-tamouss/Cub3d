/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:52:30 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/15 22:45:05 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// make the angle between 0 and 360 degree
// clang-format off
float	normalise_angle(float angle)
{
	while (angle >= (2 * MY_PI) || angle <= (-2 * MY_PI))
	{
		if (angle >= (2 * MY_PI))
			angle -= 2 * MY_PI;
		if (angle <= (-2 * MY_PI))
			angle += 2 * MY_PI;
	}
	return (angle);
}

// will rotate the player by the angle
void	rotate_player(float angle)
{
	t_vector	new_dir;
	float		new_angle;

	new_angle = normalise_angle(get_data()->player_angle + angle);
	new_dir.x = cos(new_angle) * get_data()->speed;
	new_dir.y = sin(new_angle) * get_data()->speed;
	get_data()->player_angle = new_angle;
	get_data()->player_dir = new_dir;
}
