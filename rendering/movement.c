/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:10 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/27 13:06:38 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward()
{
    // float	next_step_x = get_data()->player_pos.x + get_data()->player_dir.x;
    // float	next_step_y = get_data()->player_pos.y + get_data()->player_dir.y;
    
    // int next_map_x = get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][(int)next_step_x/GRID_DIST]; 
    // int next_map_y = get_data()->map[(int)next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST]; 

    // if (next_map_x != '1'
    //     && next_map_x != 'D'
    //     && next_map_x != 'P')
    //     get_data()->player_pos.x = next_step_x;
    // if (next_map_y != '1'
    //     && next_map_y != 'D'
    //     && next_map_y != 'P')
    //     get_data()->player_pos.y = next_step_y;

    t_vector dir = get_data()->player_dir;
    	float	d_square = (GRID_DIST/8) ;//
	t_vector a;
	a.x = get_data()->player_pos.x - d_square;
	a.y = get_data()->player_pos.y - d_square;
	t_vector b;
	b.x = get_data()->player_pos.x + d_square;
	b.y = get_data()->player_pos.y - d_square;
	t_vector c;
	c.x = get_data()->player_pos.x - d_square;
	c.y = get_data()->player_pos.y + d_square;
	t_vector d;
	d.x = get_data()->player_pos.x + d_square;
	d.y = get_data()->player_pos.y + d_square;
	////////////////////////////////////////
	int next_map_x_a = get_data()->map[(int)a.y/GRID_DIST][(int)(a.x  + dir.x)/GRID_DIST];
    int next_map_y_a = get_data()->map[(int)(a.y + dir.y)/GRID_DIST][(int)(a.x)/GRID_DIST];

	int next_map_x_b = get_data()->map[(int)b.y/GRID_DIST][(int)(b.x + dir.x)/GRID_DIST];
    int next_map_y_b = get_data()->map[(int)(b.y + dir.y)/GRID_DIST][(int)(b.x)/GRID_DIST]; 

	int next_map_x_c = get_data()->map[(int)c.y/GRID_DIST][(int)(c.x + dir.x)/GRID_DIST]; 
    int next_map_y_c = get_data()->map[(int)(c.y + dir.y)/GRID_DIST][(int)(c.x)/GRID_DIST]; 

	int next_map_x_d = get_data()->map[(int)d.y/GRID_DIST][(int)(d.x + dir.x)/GRID_DIST]; 
    int next_map_y_d = get_data()->map[(int)(d.y + dir.y)/GRID_DIST][(int)(d.x)/GRID_DIST]; 
    ///
    if (next_map_x_a != '1'
    	&& next_map_x_b != '1'
    	&& next_map_x_c != '1'
    	&& next_map_x_d != '1'
        && next_map_x_a != 'D'
        && next_map_x_b != 'D'
        && next_map_x_c != 'D'
        && next_map_x_d != 'D'
        && next_map_x_a != 'P'
        && next_map_x_b != 'P'
        && next_map_x_c != 'P'
        && next_map_x_d != 'P')
         get_data()->player_pos.x += dir.x;
    if (next_map_y_a != '1'
    	&& next_map_y_b != '1'
    	&& next_map_y_c != '1'
    	&& next_map_y_d != '1'
        && next_map_y_a != 'D'
        && next_map_y_b != 'D'
        && next_map_y_c != 'D'
        && next_map_y_d != 'D'
        && next_map_y_a != 'P'
        && next_map_y_b != 'P'
        && next_map_y_c != 'P'
        && next_map_y_d != 'P')
         get_data()->player_pos.y += dir.y;

}

void	move_backward()
{
    // int	next_step_x = get_data()->player_pos.x - get_data()->player_dir.x;
    // int	next_step_y = get_data()->player_pos.y - get_data()->player_dir.y;

    // int next_map_x = get_data()->map[(int)get_data()->player_pos.y/GRID_DIST][next_step_x/GRID_DIST]; 
    // int next_map_y = get_data()->map[next_step_y/GRID_DIST][(int)(get_data()->player_pos.x)/GRID_DIST]; 

    // if (next_map_x != '1'
    //     && next_map_x != 'D'
    //     && next_map_x != 'P')
    //     get_data()->player_pos.x = next_step_x;
    // if (next_map_y != '1'
    //     && next_map_y != 'D'
    //     && next_map_y != 'P')
    //     get_data()->player_pos.y = next_step_y;

        t_vector dir = get_data()->player_dir;
    	float	d_square = (GRID_DIST/8) ;//
	t_vector a;
	a.x = get_data()->player_pos.x - d_square;
	a.y = get_data()->player_pos.y - d_square;
	t_vector b;
	b.x = get_data()->player_pos.x + d_square;
	b.y = get_data()->player_pos.y - d_square;
	t_vector c;
	c.x = get_data()->player_pos.x - d_square;
	c.y = get_data()->player_pos.y + d_square;
	t_vector d;
	d.x = get_data()->player_pos.x + d_square;
	d.y = get_data()->player_pos.y + d_square;
	////////////////////////////////////////
	int next_map_x_a = get_data()->map[(int)a.y/GRID_DIST][(int)(a.x  - dir.x)/GRID_DIST];
    int next_map_y_a = get_data()->map[(int)(a.y - dir.y)/GRID_DIST][(int)(a.x)/GRID_DIST];

	int next_map_x_b = get_data()->map[(int)b.y/GRID_DIST][(int)(b.x - dir.x)/GRID_DIST];
    int next_map_y_b = get_data()->map[(int)(b.y - dir.y)/GRID_DIST][(int)(b.x)/GRID_DIST]; 

	int next_map_x_c = get_data()->map[(int)c.y/GRID_DIST][(int)(c.x - dir.x)/GRID_DIST]; 
    int next_map_y_c = get_data()->map[(int)(c.y - dir.y)/GRID_DIST][(int)(c.x)/GRID_DIST]; 

	int next_map_x_d = get_data()->map[(int)d.y/GRID_DIST][(int)(d.x - dir.x)/GRID_DIST]; 
    int next_map_y_d = get_data()->map[(int)(d.y - dir.y)/GRID_DIST][(int)(d.x)/GRID_DIST]; 
    ///
    if (next_map_x_a != '1'
    	&& next_map_x_b != '1'
    	&& next_map_x_c != '1'
    	&& next_map_x_d != '1'
        && next_map_x_a != 'D'
        && next_map_x_b != 'D'
        && next_map_x_c != 'D'
        && next_map_x_d != 'D'
        && next_map_x_a != 'P'
        && next_map_x_b != 'P'
        && next_map_x_c != 'P'
        && next_map_x_d != 'P')
         get_data()->player_pos.x -= dir.x;
    if (next_map_y_a != '1'
    	&& next_map_y_b != '1'
    	&& next_map_y_c != '1'
    	&& next_map_y_d != '1'
        && next_map_y_a != 'D'
        && next_map_y_b != 'D'
        && next_map_y_c != 'D'
        && next_map_y_d != 'D'
        && next_map_y_a != 'P'
        && next_map_y_b != 'P'
        && next_map_y_c != 'P'
        && next_map_y_d != 'P')
         get_data()->player_pos.y -= dir.y;
}

void	move_right()
{
	rotate_player(90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(-90 * (MY_PI / (float)180));
}

void	move_left()
{
	rotate_player(-90 * (MY_PI / (float)180));
	move_forward();
	rotate_player(90 * (MY_PI / (float)180));
}
