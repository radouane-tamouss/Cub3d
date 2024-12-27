/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:31:48 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:50:19 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	initialize_first_scope_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/zoom_shoot_gun3/1.xpm";
	frame_paths[1] = "textures/zoom_shoot_gun3/2.xpm";
	frame_paths[2] = "textures/zoom_shoot_gun3/3.xpm";
	frame_paths[3] = "textures/zoom_shoot_gun3/4.xpm";
	frame_paths[4] = "textures/zoom_shoot_gun3/5.xpm";
	frame_paths[5] = "textures/zoom_shoot_gun3/6.xpm";
}

void	initialize_last_scope_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/zoom_shoot_gun3/12.xpm";
	frame_paths[1] = "textures/zoom_shoot_gun3/13.xpm";
	frame_paths[2] = "textures/zoom_shoot_gun3/14.xpm";
	frame_paths[3] = "textures/zoom_shoot_gun3/15.xpm";
	frame_paths[4] = "textures/zoom_shoot_gun3/16.xpm";
}

void	initialize_zoom_shoot_frames_paths(char *frame_paths[])
{
	frame_paths[0] = "textures/zoom_shoot_gun3/6.xpm";
	frame_paths[1] = "textures/zoom_shoot_gun3/7.xpm";
	frame_paths[2] = "textures/zoom_shoot_gun3/8.xpm";
	frame_paths[3] = "textures/zoom_shoot_gun3/9.xpm";
	frame_paths[4] = "textures/zoom_shoot_gun3/10.xpm";
	frame_paths[5] = "textures/zoom_shoot_gun3/10.xpm";
}
