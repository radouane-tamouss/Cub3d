/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:52:30 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/01 02:24:34 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

//make the angle between 0 and 360 degree
float	normalise_angle(float angle)
{
	while (angle >= (2 * MY_PI) || angle <= (-2 * MY_PI))
	{
		if (angle >= (2 * MY_PI))
			angle -= 2 * MY_PI;
		if (angle <= (-2 * MY_PI))
			angle += 2 * MY_PI;
	}
	return	(angle);
}

// will rotate the player by the angle
void	rotate_player(float angle)
{
	t_vector	new_dir;
	// t_vector	old_dir;
	float			new_angle;

	new_angle = normalise_angle(get_data()->player_angle + angle);
	// old_dir = get_data()->player_dir;
	new_dir.x = cos(new_angle) * SPEED;
	new_dir.y = sin(new_angle) * SPEED;

	get_data()->player_angle = new_angle;
	get_data()->player_dir = new_dir;
}
