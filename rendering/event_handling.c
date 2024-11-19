/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/18 02:43:06by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_close(void)
{
	exiter(0);
	return (0);
}
void render_scope()
{
    void *img;
    int width;
    int height;

    img = mlx_xpm_file_to_image(get_data()->mlx, "textures/scope_sniper.xpm", &width, &height);
    if (get_data()->show_scope)
    {
        mlx_put_image_to_window(get_data()->mlx, get_data()->win, img, (WIN_WIDTH - width) / 2, (WIN_HEIGHT - height) / 2);
    }
}

void render_tab()
{
    void *img[4];
    // void *img[4];
    int width;
    int height;

    img[0] = mlx_xpm_file_to_image(get_data()->mlx, "textures/weapon/weapon1.xpm", &width, &height);
    img[1] = mlx_xpm_file_to_image(get_data()->mlx, "textures/weapon/weapon2.xpm", &width, &height);
    img[2] = mlx_xpm_file_to_image(get_data()->mlx, "textures/weapon/weapon3.xpm", &width, &height);
    img[3] = mlx_xpm_file_to_image(get_data()->mlx, "textures/weapon/weapon3.xpm", &width, &height);


    if (get_data()->gun_id == 0 && get_data()->show_tab)
        mlx_put_image_to_window(get_data()->mlx, get_data()->win, img[0], (WIN_WIDTH - width) / 2, (WIN_HEIGHT - height) / 2);
    else if (get_data()->gun_id == 1 && get_data()->show_tab)
        mlx_put_image_to_window(get_data()->mlx, get_data()->win, img[1], (WIN_WIDTH - width) / 2, (WIN_HEIGHT - height) / 2);

    

}
void update_movement()
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
        rotate_player(-3.  * (MY_PI / (float)180));
    if (get_data()->rotate_right)
        rotate_player(3.  * (MY_PI / (float)180));
    get_data()->is_updated = 1;
}


int	handle_keys(int keycode, void *garbage)
{
	(void)garbage;
	// printf("keycode => %d\n", keycode);
	if (keycode == ESC_MAC)
	{
		mlx_destroy_window(get_data()->mlx, get_data()->win);
		exiter(0);
	}
    if (keycode == CNTRL_MAC)
    {
        get_data()->is_control_pressed = 1;
        get_data()->show_tab = 1;
    }
	// else if (keycode == W_MAC)
	// 	move_forward();
	// else if (keycode == S_MAC)
	// 	move_backward();
	// else if (keycode == D_MAC)
	// 	move_right();
	// else if (keycode == A_MAC)
	// 	move_left();
    if (keycode == W_MAC || keycode == S_MAC || keycode == D_MAC || keycode == A_MAC)
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
    if (keycode == W_MAC)
        get_data()->move_forward = 1;
    else if (keycode == S_MAC)
        get_data()->move_backward = 1;
    else if (keycode == D_MAC)
        get_data()->move_right = 1;
    else if (keycode == A_MAC)
        get_data()->move_left = 1;
	if (keycode == RIGHT_MAC)
		// rotate_player(2.  * (MY_PI / (float)180));
        get_data()->rotate_right = 1;
	else if (keycode == LEFT_MAC)
		// rotate_player(-2.  * (MY_PI / (float)180));
        get_data()->rotate_left = 1;
	else if (keycode == SPACE_MAC)
	{
		if (get_data()->dark_mode == 1)
			get_data()->dark_mode = 0;
		else
			get_data()->dark_mode = 1;
	}
	else if (keycode == E_MAC)
	{
    
        if (get_data()->front_ray.dist < 2 * GRID_DIST)
        {
            int map_x = get_data()->front_ray.map_x;
            int map_y = get_data()->front_ray.map_y;
            char *current_tile = &get_data()->map[map_y][map_x];
        
            if (*current_tile == 'D')
                *current_tile = 'O';
            else if (*current_tile == 'O')
                *current_tile = 'D';
        }
    
        get_data()->is_updated = 1;
	}
    else if (keycode == Z_MAC)
    {
        get_data()->show_scope = 1;
    }
	else  if (keycode == T_MAC)  // Add proper key define if needed
    {
		get_data()->gun.shooted = 1;
        get_data()->gun.is_reloading = 1;
        get_data()->gun.current_frame = 0;
        get_data()->gun.frame_delay = 0;
    }
    else if (keycode == Y_MAC)
    {
        get_data()->gun2.shooted = 1;
        get_data()->gun2.is_reloading = 1;
        get_data()->gun2.current_frame = 0;
        get_data()->gun2.frame_delay = 0;
    }
    else if (keycode == N_MAC)
    {
        printf("n pressed\n");
        get_data()->gun2.is_shooting = 1;
        get_data()->gun2.current_frame = 0;
        get_data()->gun2.frame_delay = 0;
        get_data()->gun2.is_reloading = 0;
        get_data()->is_running = 0;
        get_data()->is_walking = 0;

    }
    else if (keycode == SHIFT_MAC)
    {
        get_data()->speed = 15;
    }
    else if (keycode == TAB_MAC && !get_data()->is_tab_pressed)
    {
        get_data()->gun_id++;
        if (get_data()->gun_id >= 2)
            get_data()->gun_id = 0;
        get_data()->show_tab = 1;
        get_data()->is_tab_pressed = 1;
    }
	get_data()->is_updated = 1;
	return (0);
}

int key_release(int keycode, void *garbage)
{
    (void)garbage;
    if (keycode == CNTRL_MAC)
    {
        get_data()->is_control_pressed = 0;
    }
    if (keycode == W_MAC)
        get_data()->move_forward = 0;
    else if (keycode == S_MAC)
        get_data()->move_backward = 0;
    else if (keycode == D_MAC)
        get_data()->move_right = 0;
    else if (keycode == A_MAC)
        get_data()->move_left = 0;
    if (keycode == RIGHT_MAC)
        get_data()->rotate_right = 0;
    else if (keycode == LEFT_MAC)
        get_data()->rotate_left = 0;
    else if (keycode == Z_MAC)
        get_data()->show_scope = 0;
    else if (keycode == TAB_MAC)
    {
        get_data()->is_tab_pressed = 0;
        get_data()->show_tab = 0;
    }
    else if (keycode == SHIFT_MAC)
        get_data()->speed = 8;
    if (keycode == W_MAC || keycode == S_MAC || keycode == D_MAC || keycode == A_MAC)
    {
        if (get_data()->move_backward == 0 && get_data()->move_forward == 0 && get_data()->move_left == 0 && get_data()->move_right == 0)
        {
            get_data()->is_running = 0;
            get_data()->is_walking = 0;
            get_data()->gun2.current_frame = 0;
            get_data()->gun2.frame_delay = 0;
        }
    }
    return (0);
}

int mouse_event(int x, int y, void *par)
{
	(void)par;
	// if (get_data()->mouse_pos.x > x)
	// 	rotate_player(-.5 * (MY_PI / 180));
	// else
	// 	rotate_player(.5 * (MY_PI / 180));
	rotate_player(-.5 *(get_data()->mouse_pos.x - x) * (MY_PI / 180));
	get_data()->mouse_pos.x = x;
	get_data()->is_updated = 1;
	return (0);
}
