/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:52:30 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/18 04:39:21 by rtamouss         ###   ########.fr       */
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
	new_dir.x = cos(new_angle) * get_data()->speed;
	new_dir.y = sin(new_angle) * get_data()->speed;

	get_data()->player_angle = new_angle;
	get_data()->player_dir = new_dir;
}
