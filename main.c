/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:26 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/10 21:24:26y rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// this will be used to store data and share it
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void put_xpm_image(t_img_data *dest, t_img_data *src, int start_x, int start_y)
{
    if (!dest || !src || !dest->addr || !src->addr)
        return;

    int *dest_data = (int *)dest->addr;
    int *src_data = (int *)src->addr;
    
    int dest_line_width = dest->line_length / 4;
    int src_line_width = src->line_length / 4;

    for (int y = 0; y < src->height; y++)
    {
        int dest_y = start_y + y;
        
        // Skip if outside vertical bounds
        if (dest_y < 0 || dest_y >= WIN_HEIGHT)
            continue;

        for (int x = 0; x < src->width; x++)
        {
            int dest_x = start_x + x;
            
            // Skip if outside horizontal bounds
            if (dest_x < 0 || dest_x >= WIN_WIDTH)
                continue;

            int src_pixel = src_data[y * src_line_width + x];
            
            // Skip transparent pixels (look for None color or full black/transparent)
            if ((src_pixel & 0x00FFFFFF) == 0)  // near-black from your XPM
                continue;

            // Direct pixel replacement
            dest_data[dest_y * dest_line_width + dest_x] = src_pixel;
        }
    }
}

void render_transparent_frame(void *frame_img, int width, int height)
{
    t_img_data current_frame;
    current_frame.img = frame_img;
    current_frame.width = width;
    current_frame.height = height;
    current_frame.addr = mlx_get_data_addr(current_frame.img, 
        &current_frame.bits_per_pixel, 
        &current_frame.line_length, 
        &current_frame.endian);

    // Flexible positioning
    int pos_x = WIN_WIDTH / 2 - width / 2;
    int pos_y = WIN_HEIGHT - height + 4;

    put_xpm_image(&get_data()->background_img, &current_frame, pos_x, pos_y);
}

// Updated gun rendering
void render_gun_with_transparency(void)
{
    if (get_data()->gun.is_shooting)
    {
        if (get_data()->gun.frame_delay++ >= 2)
        {
            get_data()->gun.frame_delay = 0;
            get_data()->gun.current_frame++;
            if (get_data()->gun.current_frame >= 18)
            {
                get_data()->gun.current_frame = 0;
                get_data()->gun.is_shooting = 0;
            }
        }
    }

    // Use the XPM-specific rendering method
    render_transparent_frame(
        get_data()->gun.img[get_data()->gun.current_frame],
        get_data()->gun.width,
        get_data()->gun.height
    );
}
// void    load_door_frames(void)
// {
//     char    *frame_paths[43];
//     int     i;
//     char    path[50];

//     i = 0;
//     while (i < 43)
//     {
//         sprintf(path, "textures/%ddoor.xpm", i + 1);
//         frame_paths[i] = ft_strdup(path);
//         get_data()->door.img[i] = mlx_xpm_file_to_image(get_data()->mlx, 
//             frame_paths[i], &get_data()->door.width, &get_data()->door.height);
//         if (!get_data()->door.img[i])
//         {
//             print_err("Failed to load door frame\n");
//             exiter(1);
//         }
//         free(frame_paths[i]);
//         i++;
//     }
//     get_data()->door.current_frame = 0;
//     get_data()->door.frame_delay = 0;
//     get_data()->door.is_opening = 0;
//     get_data()->door.is_open = 0;
// }
void	init_data(t_game game)
{
	get_data()->mlx = mlx_init();
	if (get_data()->mlx != NULL)
		get_data()->win = mlx_new_window(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");
	if (get_data()->mlx == NULL || get_data()->win == NULL)
	{
		print_err("CUB3D: mlx failed\n");
		exiter(1);
	}
	get_data()->background_img.img = mlx_new_image(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);// TODO protect failing
	get_data()->background_img.addr = mlx_get_data_addr(get_data()->background_img.img,
		&(get_data()->background_img.bits_per_pixel), &(get_data()->background_img.line_length),
		&(get_data()->background_img.endian)); // TODO protect failing

	get_data()->floor_color = CREATE_TRGB(0, game.floor.r, game.floor.g, game.floor.b);//BROWN;// TODO this just for startin befroe parsing is complete
	get_data()->ceiling_color = CREATE_TRGB(0, game.ceiling.r, game.ceiling.g, game.ceiling.b);//CYAN;// TODO this just for startin befroe parsing is complete
	// init_background();
	mlx_hook(get_data()->win, 2, 1L << 0, handle_keys, NULL);// this to handle when a key pressed
	mlx_hook(get_data()->win, 3, 1L << 1, key_release, NULL);// this to handle when a key released
	mlx_hook(get_data()->win, 17, 1L << 0, ft_close, NULL);// this to handle when red arrow clicked
	mlx_hook(get_data()->win, 6, 1L<<6, mouse_event, NULL);
    get_data()->speed = 7;
	get_data()->player_pos.x = game.player.pos_x * GRID_DIST + GRID_DIST/2;//1. * GRID_DIST;// TODO for test only
	get_data()->player_pos.y =  game.player.pos_y * GRID_DIST + GRID_DIST/2;//1. * GRID_DIST;// TODO for test only
	get_data()->player_angle = 0;//MY_PI / 4;
	get_data()->player_dir.x = cos(get_data()->player_angle) * get_data()->speed;
	get_data()->player_dir.y = sin(get_data()->player_angle) * get_data()->speed;

	get_data()->map = game.map.grid;
	get_data()->height = game.map.height;
	get_data()->width = game.map.width;

    get_data()->move_forward = 0;
    get_data()->move_backward = 0;
    get_data()->move_left = 0;
    get_data()->move_right = 0;
    get_data()->rotate_left = 0;
    get_data()->rotate_right = 0;
    get_data()->show_scope = 0;
    get_data()->gun_id = 0;
    get_data()->show_tab = 0;

	get_data()->north_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/future_wall.xpm", &(get_data()->north_img.width), &(get_data()->north_img.height));
	get_data()->north_img.img_data.addr = mlx_get_data_addr(get_data()->north_img.img_data.img, &(get_data()->north_img.img_data.bits_per_pixel), &(get_data()->north_img.img_data.line_length), &(get_data()->north_img.img_data.endian));

	get_data()->south_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/future_wall.xpm", &(get_data()->south_img.width), &(get_data()->south_img.height));
	get_data()->south_img.img_data.addr = mlx_get_data_addr(get_data()->south_img.img_data.img, &(get_data()->south_img.img_data.bits_per_pixel), &(get_data()->south_img.img_data.line_length), &(get_data()->south_img.img_data.endian));

	get_data()->east_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/future_wall.xpm", &(get_data()->east_img.width), &(get_data()->east_img.height));
	get_data()->east_img.img_data.addr = mlx_get_data_addr(get_data()->east_img.img_data.img, &(get_data()->east_img.img_data.bits_per_pixel), &(get_data()->east_img.img_data.line_length), &(get_data()->east_img.img_data.endian));
	
	get_data()->west_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/west.xpm", &(get_data()->west_img.width), &(get_data()->west_img.height));
	get_data()->west_img.img_data.addr = mlx_get_data_addr(get_data()->west_img.img_data.img, &(get_data()->west_img.img_data.bits_per_pixel), &(get_data()->west_img.img_data.line_length), &(get_data()->west_img.img_data.endian));
	//===
	get_data()->door_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/1door.xpm", &(get_data()->door_img.width), &(get_data()->door_img.height));
	get_data()->door_img.img_data.addr = mlx_get_data_addr(get_data()->door_img.img_data.img, &(get_data()->door_img.img_data.bits_per_pixel), &(get_data()->door_img.img_data.line_length), &(get_data()->door_img.img_data.endian));



    



}
void    load_shooting_gun2_frames(void)
{
    char    *frame_paths[27] = {
        "textures/gun2shoot/1gun2shoot.xpm",
        "textures/gun2shoot/2gun2shoot.xpm",
        "textures/gun2shoot/3gun2shoot.xpm",
        "textures/gun2shoot/4gun2shoot.xpm",
        "textures/gun2shoot/5gun2shoot.xpm",
        "textures/gun2shoot/6gun2shoot.xpm",
        "textures/gun2shoot/7gun2shoot.xpm",
        "textures/gun2shoot/8gun2shoot.xpm",
        "textures/gun2shoot/9gun2shoot.xpm",
        "textures/gun2shoot/10gun2shoot.xpm",
        "textures/gun2shoot/11gun2shoot.xpm",
        "textures/gun2shoot/12gun2shoot.xpm",
        "textures/gun2shoot/13gun2shoot.xpm",
        "textures/gun2shoot/14gun2shoot.xpm",
        "textures/gun2shoot/15gun2shoot.xpm",
        "textures/gun2shoot/16gun2shoot.xpm",
        "textures/gun2shoot/17gun2shoot.xpm",
        "textures/gun2shoot/18gun2shoot.xpm",
        "textures/gun2shoot/19gun2shoot.xpm",
        "textures/gun2shoot/20gun2shoot.xpm",
        "textures/gun2shoot/21gun2shoot.xpm",
        "textures/gun2shoot/22gun2shoot.xpm",
        "textures/gun2shoot/23gun2shoot.xpm",
        "textures/gun2shoot/24gun2shoot.xpm",
        "textures/gun2shoot/25gun2shoot.xpm",
        "textures/gun2shoot/26gun2shoot.xpm",
        "textures/gun2shoot/27gun2shoot.xpm"
    };
    int     i;

    i = 0;
    while (i < 27)
    {
        get_data()->gun2.shooting_frames[i] = mlx_xpm_file_to_image(get_data()->mlx, 
            frame_paths[i], &get_data()->gun2.width, &get_data()->gun2.height);
        if (!get_data()->gun2.shooting_frames[i])
        {
            print_err("Failed to load gun frame\n");
            exiter(1);
        }
        i++;
    }
    get_data()->gun2.current_frame = 0;
    get_data()->gun2.frame_delay = 0;
    get_data()->gun2.is_reloading = 0;
    get_data()->gun2.is_shooting = 0;
    get_data()->gun2.shooted = 0;
}
void load_running_gun2_frames(void)
{
    char *frame_paths[23] = {
        "textures/running_gun2/1running_gun2.xpm",
        "textures/running_gun2/2running_gun2.xpm",
        "textures/running_gun2/3running_gun2.xpm",
        "textures/running_gun2/4running_gun2.xpm",
        "textures/running_gun2/5running_gun2.xpm",
        "textures/running_gun2/6running_gun2.xpm",
        "textures/running_gun2/7running_gun2.xpm",
        "textures/running_gun2/8running_gun2.xpm",
        "textures/running_gun2/9running_gun2.xpm",
        "textures/running_gun2/10running_gun2.xpm",
        "textures/running_gun2/11running_gun2.xpm",
        "textures/running_gun2/12running_gun2.xpm",
        "textures/running_gun2/13running_gun2.xpm",
        "textures/running_gun2/14running_gun2.xpm",
        "textures/running_gun2/15running_gun2.xpm",
        "textures/running_gun2/16running_gun2.xpm",
        "textures/running_gun2/17running_gun2.xpm",
        "textures/running_gun2/18running_gun2.xpm",
        "textures/running_gun2/19running_gun2.xpm",
        "textures/running_gun2/20running_gun2.xpm",
        "textures/running_gun2/21running_gun2.xpm",
        "textures/running_gun2/22running_gun2.xpm",
        "textures/running_gun2/23running_gun2.xpm"
    };

    int i;
    i = 0;

    while(i < 23)
    {
        get_data()->gun2.running_frames[i] = mlx_xpm_file_to_image(get_data()->mlx, 
            frame_paths[i], &get_data()->gun2.width, &get_data()->gun2.height);
        if (!get_data()->gun2.running_frames[i])
        {
            print_err("Failed to load gun frame\n");
            exiter(1);
        }
        i++;
    }
    get_data()->gun2.current_frame = 0;
    get_data()->gun2.frame_delay = 0;
}
void load_walking_gun2_frames(void)
{
    char *frame_paths[13] = {
        "textures/moving_gun2_slow/1walk.xpm",
        "textures/moving_gun2_slow/2walk.xpm",
        "textures/moving_gun2_slow/3walk.xpm",
        "textures/moving_gun2_slow/4walk.xpm",
        "textures/moving_gun2_slow/5walk.xpm",
        "textures/moving_gun2_slow/6walk.xpm",
        "textures/moving_gun2_slow/7walk.xpm",
        "textures/moving_gun2_slow/8walk.xpm",
        "textures/moving_gun2_slow/9walk.xpm",
        "textures/moving_gun2_slow/10walk.xpm",
        "textures/moving_gun2_slow/11walk.xpm",
        "textures/moving_gun2_slow/12walk.xpm",
        "textures/moving_gun2_slow/13walk.xpm"
    };

    int i;
    i = 0;

    while(i < 13)
    {
        get_data()->gun2.walking_frames[i] = mlx_xpm_file_to_image(get_data()->mlx, 
            frame_paths[i], &get_data()->gun2.width, &get_data()->gun2.height);
        if (!get_data()->gun2.walking_frames[i])
        {
            print_err("Failed to load gun frame\n");
            exiter(1);
        }
        i++;
    }
    get_data()->gun2.current_frame = 0;
    get_data()->gun2.frame_delay = 0;
}
void    load_first_gun_frames(void)
{
    char    *frame_paths[18] = {
        "textures/1.xpm",
        "textures/2.xpm",
        "textures/3.xpm",
        "textures/4.xpm",
        "textures/5.xpm",
        "textures/6.xpm",
        "textures/7.xpm",
        "textures/8.xpm",
        "textures/9.xpm",
        "textures/10.xpm",
        "textures/11.xpm",
        "textures/12.xpm",
        "textures/13.xpm",
        "textures/14.xpm",
        "textures/15.xpm",
        "textures/16.xpm",
        "textures/17.xpm",
        "textures/18.xpm",
    };
    int     i;

    i = 0;
    while (i < 18)
    {
        get_data()->gun.img[i] = mlx_xpm_file_to_image(get_data()->mlx, 
            frame_paths[i], &get_data()->gun.width, &get_data()->gun.height);
        if (!get_data()->gun.img[i])
        {
            print_err("Failed to load gun frame\n");
            exiter(1);
        }
        i++;
    }
    get_data()->gun.current_frame = 0;
    get_data()->gun.frame_delay = 0;
    get_data()->gun.is_reloading = 0;
    get_data()->gun.shooted = 0;
}



// Implementation of gun loading and animation functions
void    load_frames(void)
{
    // char    *frame_paths[18] = {
    //     "textures/1.xpm",
    //     "textures/2.xpm",
    //     "textures/3.xpm",
    //     "textures/4.xpm",
    //     "textures/5.xpm",
    //     "textures/6.xpm",
    //     "textures/7.xpm",
    //     "textures/8.xpm",
    //     "textures/9.xpm",
    //     "textures/10.xpm",
    //     "textures/11.xpm",
    //     "textures/12.xpm",
    //     "textures/13.xpm",
    //     "textures/14.xpm",
    //     "textures/15.xpm",
    //     "textures/16.xpm",
    //     "textures/17.xpm",
    //     "textures/18.xpm",
    // };
    char *frame_paths[20] = {
        "textures/reload_gun/reload_gun1.xpm",
        "textures/reload_gun/reload_gun2.xpm",
        "textures/reload_gun/reload_gun3.xpm",
        "textures/reload_gun/reload_gun4.xpm",
        "textures/reload_gun/reload_gun5.xpm",
        "textures/reload_gun/reload_gun6.xpm",
        "textures/reload_gun/reload_gun7.xpm",
        "textures/reload_gun/reload_gun8.xpm",
        "textures/reload_gun/reload_gun9.xpm",
        "textures/reload_gun/reload_gun10.xpm",
        "textures/reload_gun/reload_gun11.xpm",
        "textures/reload_gun/reload_gun12.xpm",
        "textures/reload_gun/reload_gun13.xpm",
        "textures/reload_gun/reload_gun14.xpm",
        "textures/reload_gun/reload_gun15.xpm",
        "textures/reload_gun/reload_gun16.xpm",
        "textures/reload_gun/reload_gun17.xpm",
        "textures/reload_gun/reload_gun18.xpm",
        "textures/reload_gun/reload_gun19.xpm",
        "textures/reload_gun/reload_gun20.xpm",
    };
    int     i;

    i = 0;
    while (i < 20)
    {
        get_data()->gun2.img[i] = mlx_xpm_file_to_image(get_data()->mlx, 
            frame_paths[i], &get_data()->gun2.width, &get_data()->gun2.height);
        if (!get_data()->gun2.img[i])
        {
            print_err("Failed to load gun frame\n");
            exiter(1);
        }
        i++;
    }
    get_data()->gun2.current_frame = 0;
    get_data()->gun2.frame_delay = 0;
    get_data()->gun2.is_reloading = 0;
    get_data()->gun2.shooted = 0;
}

void    render_gun(void)
{
    int         gun_pos_x;
    int         gun_pos_y;

    // Calculate gun position
    gun_pos_x = WIN_WIDTH / 2 - get_data()->gun.width / 2;
    gun_pos_y = WIN_HEIGHT - get_data()->gun.height + 4;

    if (get_data()->gun_id == 0)
    {
        if (get_data()->gun.is_reloading)
        {
            if (get_data()->gun.frame_delay++ >= 2)  // Adjust delay value as needed
            {
                get_data()->gun.frame_delay = 1;
                get_data()->gun.current_frame++;
                if (get_data()->gun.current_frame >= 18) 
                {
                    get_data()->gun.current_frame = 0;
                    get_data()->gun.is_reloading = 0;
                }
            }
        }
        // Render the current frame
        // mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
        //     get_data()->gun.img[get_data()->gun.current_frame], 
        //     gun_pos_x, gun_pos_y);
        render_transparent_frame(
            get_data()->gun.img[get_data()->gun.current_frame],
            get_data()->gun.width,
            get_data()->gun.height
        );
    }

    if (get_data()->gun_id == 1)
    {
        if (get_data()->gun2.is_reloading)
        {
            if (get_data()->gun2.frame_delay++ >= 2)  // Adjust delay value as needed
            {
                get_data()->gun2.frame_delay = 1;
                get_data()->gun2.current_frame++;
                if (get_data()->gun2.current_frame >= 20) 
                {
                    get_data()->gun2.current_frame = 0;
                    get_data()->gun2.is_reloading = 0;
                }
            }
            // mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
            //     get_data()->gun2.img[get_data()->gun2.current_frame], 
            //     gun_pos_x, gun_pos_y);
            render_transparent_frame(
                get_data()->gun2.img[get_data()->gun2.current_frame],
                get_data()->gun2.width,
                get_data()->gun2.height
            );
        }
        else if (get_data()->gun2.is_shooting)
        {
            if (get_data()->gun2.frame_delay++ >= 1)  // Adjust delay value as needed
            {
                get_data()->gun2.frame_delay = 1;
                get_data()->gun2.current_frame++;
                if (get_data()->gun2.current_frame >= 27) 
                {
                    get_data()->gun2.current_frame = 0;
                    get_data()->gun2.is_shooting = 0;
                }
            }
            // mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
            //     get_data()->gun2.shooting_frames[get_data()->gun2.current_frame], 
            //     WIN_WIDTH / 2 - get_data()->gun2.width / 2, WIN_HEIGHT - get_data()->gun2.height + 4);
        }
        else if (get_data()->is_walking)
        {
            if (get_data()->gun2.frame_delay++ >= 4)  // Adjust delay value as needed
            {
                get_data()->gun2.frame_delay = 1;
                get_data()->gun2.current_frame++;
                if (get_data()->gun2.current_frame >= 10) 
                {
                    get_data()->gun2.current_frame = 0;
                }
            }
            // mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
            //     get_data()->gun2.walking_frames[get_data()->gun2.current_frame], 
            //     WIN_WIDTH / 2 - get_data()->gun2.width / 2, WIN_HEIGHT - get_data()->gun2.height + 4);
            render_transparent_frame(get_data()->gun2.walking_frames[get_data()->gun2.current_frame], get_data()->gun2.width, get_data()->gun2.height);
        }
        else if (get_data()->is_running)
        {
            if (get_data()->gun2.frame_delay++ >= 4)  // Adjust delay value as needed
            {
                get_data()->gun2.frame_delay = 1;
                get_data()->gun2.current_frame++;
                if (get_data()->gun2.current_frame >= 19) 
                {
                    get_data()->gun2.current_frame = 3;
                }
            }
            // mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
            //     get_data()->gun2.running_frames[get_data()->gun2.current_frame], 
            //     WIN_WIDTH / 2 - get_data()->gun2.width / 2, WIN_HEIGHT - get_data()->gun2.height + 4);
            render_transparent_frame(get_data()->gun2.running_frames[get_data()->gun2.current_frame]
            , get_data()->gun2.width, get_data()->gun2.height);
        }

        if (get_data()->gun2.is_reloading == 0  && get_data()->is_walking == 0 && get_data()->is_running == 0)
                // mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
                // get_data()->gun2.shooting_frames[get_data()->gun2.current_frame], 
                // WIN_WIDTH / 2 - get_data()->gun2.width / 2, WIN_HEIGHT - get_data()->gun2.height + 4);
                render_transparent_frame(get_data()->gun2.shooting_frames[get_data()->gun2.current_frame], get_data()->gun2.width, get_data()->gun2.height);
                
        // Render the current frame
    }
    // Handle shooting animation
}

int player_is_close_to_door(void)
{
    return (get_data()->front_ray.dist < 2 * GRID_DIST);
}

int loop_hook(t_game *game)
{
    if (get_data()->is_tab_pressed)
    {
        render_tab();
        return (0);
    }
	if (get_data()->is_updated)
	{
		init_background();
        update_movement();
		render_walls();
        // render_scope();
		render_minimap();
		render_background();
        // mlx_mouse_hide();
        if (!get_data()->show_scope)
		        render_gun();
            // render_gun_with_transparency();
        // render_scope();
    	if (get_data()->front_ray.object_hitted == 2 && 
        	get_data()->front_ray.dist < 2 * GRID_DIST)
        {
            int text_width = 200;
            int text_height = 20;
            int text_x = (WIN_WIDTH - text_width) / 2;
            int text_y = WIN_HEIGHT - text_height - 10;

            // Draw white text
            mlx_string_put(get_data()->mlx, get_data()->win, text_x + 10, text_y + 5, 0xFFFFFF, "[Press E to close the door]");
        }
        if (get_data()->front_ray.object_hitted == 1 && get_data()->front_ray.dist < 2 * GRID_DIST)
        {
            int text_width = 200;
            int text_height = 20;
            int text_x = (WIN_WIDTH - text_width) / 2;
            int text_y = WIN_HEIGHT - text_height - 10;

            // Draw white text
            mlx_string_put(get_data()->mlx, get_data()->win, text_x + 10, text_y + 5, 0xFFFFFF, "[Press E to open the door]");
        }
        if (get_data()->gun.shooted == 0 && !player_is_close_to_door())
        {
            int text_x = (WIN_WIDTH - 200) / 2;
            int text_y = WIN_HEIGHT - 20 - 10;
            // Draw white text
            mlx_string_put(get_data()->mlx, get_data()->win, text_x + 10, text_y + 5, 0xFFFFFF, "[Press T to reload the gun]");
        }

	}
    return (0);
}

int main(int ac, char **av)
{
    int fd;
    t_game game;

    if (ac != 2 || check_file(av[1], &fd) == 0)
        return (printf("Error\nUsage: ./Cube3d map.cub\n"), 0);
    game = check_map(fd, av[1]);
    close(fd);
	init_data(game);
	init_background();
	render_walls();
	render_background();
	load_frames();
    load_first_gun_frames();
    load_shooting_gun2_frames();
    load_walking_gun2_frames();
    load_first_gun_frames();
    load_shooting_gun2_frames();
    load_running_gun2_frames();
	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);

    mlx_loop(get_data()->mlx);

    return (0);
}
