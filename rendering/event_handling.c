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

int ft_close(void)
{
    exiter(0);
    return (0);
}

// void render_scope()
// {
//     void *img;
//     int width;
//     int height;

//     img = safer_xpm_file_to_image(get_data()->mlx,
//     "textures/scope_sniper.xpm", &width, &height); if
//     (get_data()->show_scope)
//     {
//         mlx_put_image_to_window(get_data()->mlx, get_data()->win, img,
//         (WIN_WIDTH - width) / 2, (WIN_HEIGHT - height) / 2);
//     }
// }
#include <stdio.h>
#include <stdlib.h>

void play_sound(const char *file)
{
    char command[256];
    char *temp = ft_strjoin("paplay ", file);
    char *command_str = ft_strjoin(temp, " &");
    ft_strlcpy(command, command_str, sizeof(command));

    int result = system(command);
    if (result == -1)
    {
        perror("system");
    }
}

void render_tab()
{
    void *img[5];
    // void *img[4];
    int width;
    int height;

    img[0] = safer_xpm_file_to_image(
        get_data()->mlx, "textures/weapon/weapon1.xpm", &width, &height);
    img[1] = safer_xpm_file_to_image(
        get_data()->mlx, "textures/weapon/weapon2.xpm", &width, &height);
    img[2] = safer_xpm_file_to_image(
        get_data()->mlx, "textures/weapon/weapon3.xpm", &width, &height);
    img[3] = safer_xpm_file_to_image(
        get_data()->mlx, "textures/weapon/weapon3.xpm", &width, &height);
    img[4] = safer_xpm_file_to_image(
        get_data()->mlx, "textures/weapon/weapon3.xpm", &width, &height);

    if (get_data()->gun_id == 0 && get_data()->show_tab)
        mlx_put_image_to_window(get_data()->mlx, get_data()->win, img[0],
                                (WIN_WIDTH - width) / 2,
                                (WIN_HEIGHT - height) / 2);
    else if (get_data()->gun_id == 1 && get_data()->show_tab)
        mlx_put_image_to_window(get_data()->mlx, get_data()->win, img[1],
                                (WIN_WIDTH - width) / 2,
                                (WIN_HEIGHT - height) / 2);
}

void update_movement()
{
    // the parallax effecy achieved by moving the gun in the opposite direction
    // of the player the gun_offset_x is used to move the gun in the opposite
    // direction of the player the gun_offset_x is then multiplied by 0.9 to
    // slow down the movement of the gun

    float move_speed = 0.7;

    if (get_data()->move_forward) move_forward();
    if (get_data()->move_backward) move_backward();
    if (get_data()->move_left)
    {
        move_left();
        get_data()->gun_offset_x -= move_speed;
    }
    if (get_data()->move_right)
    {
        move_right();
        get_data()->gun_offset_x += move_speed;
    }
    // if (get_data()->rotate_left)
    //     rotate_player(-3.  * (MY_PI / (float)180));
    // if (get_data()->rotate_right)
    //     rotate_player(3.  * (MY_PI / (float)180));
    if (get_data()->rotate_left)
    {
        rotate_player(-3.0f * (MY_PI / 180.0f));
        get_data()->gun_offset_x -= move_speed;
    }
    if (get_data()->rotate_right)
    {
        rotate_player(3.0f * (MY_PI / 180.0f));
        get_data()->gun_offset_x += move_speed;
    }

    get_data()->gun_offset_x *= 0.9;
    get_data()->is_updated = 1;
}

int handle_keys(int keycode, void *garbage)
{
    (void)garbage;
    // printf("keycode => %d\n", keycode);
    if (keycode == ESC)
    {
        // fprintf(stderr , "==========heeeereeeeee\n");//
        mlx_destroy_window(get_data()->mlx, get_data()->win);

        exiter(0);
    }
    if (keycode == CNTRL_LIN)
    {
        get_data()->is_control_pressed = 1;
        get_data()->show_tab = 1;
    }
    if (keycode == W_LIN || keycode == S_LIN || keycode == D_LIN ||
        keycode == A_LIN)
    {
        printf("moving\n");
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
    if (keycode == W_LIN) get_data()->move_forward = 1;
    if (keycode == S_LIN) get_data()->move_backward = 1;
    if (keycode == D_LIN) get_data()->move_right = 1;
    if (keycode == A_LIN)
    {
        get_data()->move_left = 1;
    }
    if (keycode == RIGHT_LIN) get_data()->rotate_right = 1;
    if (keycode == LEFT_LIN) get_data()->rotate_left = 1;
    if (keycode == SPACE_LIN)
    {
        if (get_data()->dark_mode == 1)
            get_data()->dark_mode = 0;
        else
            get_data()->dark_mode = 1;
    }
    if (keycode == E_LIN)
    {
        if ((get_data()->front_ray.object_hitted == 1 ||
             get_data()->front_ray.object_hitted == 2) &&
            get_data()->front_ray.dist < 2 * GRID_DIST)
        {
            int door_x = get_data()->front_ray.map_x;
            int door_y = get_data()->front_ray.map_y;

            // Check if it's a door and not already animating
            if (get_data()->map[door_y][door_x] == 'D')
            {
                // Mark this door as animating with 'P'
                get_data()->map[door_y][door_x] = 'P';
                get_data()->door.is_opening = 1;
                get_data()->door.current_frame = 0;
                get_data()->door.frame_delay = 2;
                get_data()->is_updated = 1;
            }
            else if (get_data()->map[door_y][door_x] == 'O')
            {
                // Mark this door as animating closed with 'P'
                get_data()->map[door_y][door_x] = 'P';
                get_data()->door.is_closing = 1;
                get_data()->door.current_frame = 17;
                get_data()->door.frame_delay = 0;
                get_data()->is_updated = 1;
            }
            play_sound("sounds/door.wav");
        }
    }

    // 	{

    // 	       if (get_data()->front_ray.dist < 2 * GRID_DIST)
    // 	       {
    // 	           int map_x = get_data()->front_ray.map_x;
    // 	           int map_y = get_data()->front_ray.map_y;
    // 	           char *current_tile = &get_data()->map[map_y][map_x];

    // 	           if (*current_tile == 'D')
    // 	               *current_tile = 'O';
    // 	           else if (*current_tile == 'O')
    // 	               *current_tile = 'D';
    // 	       }

    // 	       get_data()->is_updated = 1;
    // 	}
    //   {
    //     if ((get_data()->front_ray.object_hitted == 1 ||
    //     get_data()->front_ray.object_hitted == 2) &&
    //     get_data()->front_ray.dist < 2 * GRID_DIST)
    //     {
    //         get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x]
    //         = 'D'; get_data()->door.x = get_data()->front_ray.map_x;
    //         get_data()->door.y = get_data()->front_ray.map_y;
    //         //
    //         get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x]
    //         = 'O'; if (!get_data()->door.is_open &&
    //         !get_data()->door.is_opening)
    //         {
    //             get_data()->door.is_opening = 1;
    //             get_data()->door.current_frame = 0;
    //             get_data()->door.frame_delay = 0;
    //         }
    //         else if (get_data()->door.is_open &&
    //         !get_data()->door.is_closing)
    //         {
    //             get_data()->door.is_closing = 1;
    //             get_data()->door.current_frame = 17;
    //             get_data()->door.frame_delay = 0;
    //         }

    //       get_data()->is_updated = 1;
    //     }
    // }
    if (keycode == T_LIN)  // Add proper key define if needed
    {
        printf("gun_id == %d\n", get_data()->gun_id);
        if (get_data()->gun_id == 0)
        {
            get_data()->gun.shooted = 1;
            get_data()->gun.is_reloading = 1;
            get_data()->gun.current_frame = 0;
            get_data()->gun.frame_delay = 0;
        }
        else if (get_data()->gun_id == 2)
        {
            printf("here it should be reloading\n");
            get_data()->gun3.is_reloading = 1;
            get_data()->gun3.current_frame = 0;
            get_data()->gun3.frame_delay = 0;
            play_sound("sounds/gun3reloadd.wav");
        }
    }
    if (keycode == Y_LIN)
    {
        get_data()->gun2.shooted = 1;
        get_data()->gun2.is_reloading = 1;
        get_data()->gun2.current_frame = 0;
        get_data()->gun2.frame_delay = 0;
    }
    if (keycode == Z_LIN)
    {
        printf("here z pressed\n");
        if (!get_data()->gun3.is_showing_scope)
        {
            get_data()->gun3.current_frame = 0;
            get_data()->gun3.frame_delay = 0;
            get_data()->gun3.show_scope = 1;
            get_data()->gun3.is_showing_scope = 1;
            get_data()->gun3.show_scope = !get_data()->gun3.show_scope;
        }
    }
    if (keycode == N_LIN)
    {
        printf("n pressed\n");
        if (!get_data()->gun3.is_shooting)
        {
            get_data()->gun_id = 2;
            get_data()->gun3.is_shooting = 1;
            get_data()->gun3.current_frame = 0;
            get_data()->gun3.frame_delay = 0;
            get_data()->gun3.is_reloading = 0;
            get_data()->is_running = 0;
            get_data()->is_walking = 0;
            get_data()->screen_shake_intensity =
                5;                                // Adjust intensity as needed
            get_data()->screen_shake_timer = 10;  // Adjust duration as needed
            play_sound("sounds/one_shot_firstgun.wav");
        }
    }
    if (keycode == N_LIN)
    {
        printf("n pressed gun_id = %d\n", get_data()->gun_id);
        if (!get_data()->gun3.is_shooting && !get_data()->gun2.is_shooting)
        {
            if (get_data()->gun_id == 2)
            {
                get_data()->gun3.is_shooting = 1;
                get_data()->gun3.current_frame = 0;
                get_data()->gun3.frame_delay = 0;
                get_data()->gun3.is_reloading = 0;
                get_data()->is_running = 0;
                get_data()->is_walking = 0;
                get_data()->screen_shake_intensity =
                    5;  // Adjust intensity as needed
                get_data()->screen_shake_timer =
                    10;  // Adjust duration as needed
                play_sound("sounds/one_shot_firstgun.wav");
            }
            else if (get_data()->gun_id == 1)
            {
                get_data()->gun2.is_shooting = 1;
                get_data()->gun2.current_frame = 0;
                get_data()->gun2.frame_delay = 0;
                get_data()->gun2.is_reloading = 0;
                get_data()->is_running = 0;
                get_data()->is_walking = 0;
                get_data()->screen_shake_intensity =
                    5;  // Adjust intensity as needed
                get_data()->screen_shake_timer =
                    10;  // Adjust duration as needed
                play_sound("sounds/one_shot_firstgun.wav");
            }
        }
        get_data()->is_updated = 1;
    }
    if (keycode == LIN_1)
        get_data()->gun_id = 0;
    else if (keycode == LIN_2)
        get_data()->gun_id = 1;
    else if (keycode == LIN_3)
        get_data()->gun_id = 2;
    if (keycode == SHIFT_LIN)
    {
        get_data()->speed = 10;
    }
    if (keycode == TAB_LIN && !get_data()->is_tab_pressed)
    {
        get_data()->gun_id++;
        if (get_data()->gun_id >= 3) get_data()->gun_id = 0;
        get_data()->show_tab = 1;
        get_data()->is_tab_pressed = 1;
    }
    get_data()->is_updated = 1;
    return (0);
}

int key_release(int keycode, void *garbage)
{
    (void)garbage;
    if (keycode == CNTRL_LIN)
    {
        get_data()->is_control_pressed = 0;
    }
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
    else if (keycode == Z_LIN)
        get_data()->show_scope = 0;
    else if (keycode == TAB_LIN)
    {
        get_data()->is_tab_pressed = 0;
        get_data()->show_tab = 0;
    }
    else if (keycode == SHIFT_LIN)
        get_data()->speed = 8;
    if (keycode == W_LIN || keycode == S_LIN || keycode == D_LIN ||
        keycode == A_LIN)
    {
        if (get_data()->move_backward == 0 && get_data()->move_forward == 0 &&
            get_data()->move_left == 0 && get_data()->move_right == 0)
        {
            printf("not moving\n");
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
    if (get_data()->is_tab_pressed)
    {
        // printf("x=>%d  , y => %d\n", x, y);
        if (y < 488 || y > 680 || x < 270 ||
            y > 1327)  // the y cors should be =---=> 400 to 700 and x shold be
                       // betwen 150 and 1460
            return (0);
        // if (x < 460)// X from 150 to ---------------> 470
        //     get_data()->gun_id = 1;
        // // else
        //     get_data()->gun_id = 1;
        // else if (x < 670)// X from 470 to ---------------> 800
        // else if (x < 870)
        //     get_data()->gun_id = 2;
        // else if (x < 1125)
        //     get_data()->gun_id = 3;
        // else
        //     get_data()->gun_id = 0;
        // X from 800 to ---------------> 1130
        // X from 1130 to ---------------> 1460
    }
    else
    {
        rotate_player(-.5 * (get_data()->mouse_pos.x - x) * (MY_PI / 180));
        get_data()->mouse_pos.x = x;
    }
    get_data()->is_updated = 1;
    return (0);
}
