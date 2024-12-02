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
t_data *get_data(void)
{
    static t_data data;

    return (&data);
}

void put_xpm_image(t_img_data *dest, t_img_data *src, int start_x, int start_y)
{
    if (!dest || !src || !dest->addr || !src->addr) return;

    int *dest_data = (int *)dest->addr;
    int *src_data = (int *)src->addr;

    int dest_line_width = dest->line_length / 4;
    int src_line_width = src->line_length / 4;

    for (int y = 0; y < src->height; y++)
    {
        int dest_y = start_y + y;

        // Skip if outside vertical bounds
        if (dest_y < 0 || dest_y >= WIN_HEIGHT) continue;

        for (int x = 0; x < src->width; x++)
        {
            int dest_x = start_x + x;

            // Skip if outside horizontal bounds
            if (dest_x < 0 || dest_x >= WIN_WIDTH) continue;

            int src_pixel = src_data[y * src_line_width + x];

            // Skip transparent pixels (look for None color or full
            // black/transparent)
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
    current_frame.addr =
        safer_get_data_addr(current_frame.img, &current_frame.bits_per_pixel,
                            &current_frame.line_length, &current_frame.endian);

    // Flexible positioning
    // int pos_x = WIN_WIDTH / 2 - width / 2;
    int pos_x = (WIN_WIDTH / 2 - width / 2) + (int)get_data()->gun_offset_x;
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
    render_transparent_frame(get_data()->gun.img[get_data()->gun.current_frame],
                             get_data()->gun.width, get_data()->gun.height);
}

void load_door_frames(void)
{
    char *frame_paths[18] = {
        "textures/door_frames/1.xpm",  "textures/door_frames/2.xpm",
        "textures/door_frames/3.xpm",  "textures/door_frames/4.xpm",
        "textures/door_frames/5.xpm",  "textures/door_frames/6.xpm",
        "textures/door_frames/7.xpm",  "textures/door_frames/8.xpm",
        "textures/door_frames/9.xpm",  "textures/door_frames/10.xpm",
        "textures/door_frames/11.xpm", "textures/door_frames/12.xpm",
        "textures/door_frames/13.xpm", "textures/door_frames/14.xpm",
        "textures/door_frames/15.xpm", "textures/door_frames/16.xpm",
        "textures/door_frames/17.xpm"};

    int i;

    i = 0;
    while (i < 17)
    {
        get_data()->door.img[i] = mlx_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->door.width,
            &get_data()->door.height);
        if (!get_data()->door.img[i])
        {
            printf("%d ", i);
            print_err("Failed to load door frame\n");
            exiter(1);
        }
        i++;
    }
    get_data()->door.current_frame = 0;
    get_data()->door.frame_delay = 0;
    get_data()->door.is_opening = 0;
    get_data()->door.is_open = 0;
    get_data()->door.is_closed = 1;
    get_data()->door.active_x = 0;
    get_data()->door.active_y = 0;
}

void init_data(t_game game)
{
    get_data()->mlx = mlx_init();
    if (get_data()->mlx != NULL)
        get_data()->win =
            mlx_new_window(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");
    if (get_data()->mlx == NULL || get_data()->win == NULL)
    {
        print_err("CUB3D: mlx failed\n");
        exiter(1);
    }
    get_data()->background_img.img = mlx_new_image(
        get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);  // TODO protect failing
    get_data()->background_img.addr = safer_get_data_addr(
        get_data()->background_img.img,
        &(get_data()->background_img.bits_per_pixel),
        &(get_data()->background_img.line_length),
        &(get_data()->background_img.endian));  // TODO protect failing

    get_data()->floor_color =
        CREATE_TRGB(0, game.floor.r, game.floor.g,
                    game.floor.b);  // BROWN;// TODO this just for startin
                                    // befroe parsing is complete
    get_data()->ceiling_color =
        CREATE_TRGB(0, game.ceiling.r, game.ceiling.g,
                    game.ceiling.b);  // CYAN;// TODO this just for startin
                                      // befroe parsing is complete
    // init_background();
    mlx_hook(get_data()->win, 2, 1L << 0, handle_keys,
             NULL);  // this to handle when a key pressed
    mlx_hook(get_data()->win, 3, 1L << 1, key_release,
             NULL);  // this to handle when a key released
    mlx_hook(get_data()->win, 17, 1L << 0, ft_close,
             NULL);  // this to handle when red arrow clicked
    mlx_hook(get_data()->win, 6, 1L << 6, mouse_event, NULL);
    get_data()->speed = 4;
    get_data()->player_pos.x =
        game.player.pos_x * GRID_DIST +
        GRID_DIST / 2;  // 1. * GRID_DIST;// TODO for test only
    get_data()->player_pos.y =
        game.player.pos_y * GRID_DIST +
        GRID_DIST / 2;             // 1. * GRID_DIST;// TODO for test only
    get_data()->player_angle = 0;  // MY_PI / 4;
    get_data()->player_dir.x =
        cos(get_data()->player_angle) * get_data()->speed;
    get_data()->player_dir.y =
        sin(get_data()->player_angle) * get_data()->speed;
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
    get_data()->gun_id = 1;
    get_data()->show_tab = 0;

    get_data()->gun_offset_x = 0.0;

    get_data()->north_img.img_data.img = safer_xpm_file_to_image(
        get_data()->mlx, "textures/future_wall.xpm",
        &(get_data()->north_img.width), &(get_data()->north_img.height));
    get_data()->north_img.img_data.addr =
        safer_get_data_addr(get_data()->north_img.img_data.img,
                            &(get_data()->north_img.img_data.bits_per_pixel),
                            &(get_data()->north_img.img_data.line_length),
                            &(get_data()->north_img.img_data.endian));

    get_data()->south_img.img_data.img = safer_xpm_file_to_image(
        get_data()->mlx, "textures/future_wall.xpm",
        &(get_data()->south_img.width), &(get_data()->south_img.height));
    get_data()->south_img.img_data.addr =
        safer_get_data_addr(get_data()->south_img.img_data.img,
                            &(get_data()->south_img.img_data.bits_per_pixel),
                            &(get_data()->south_img.img_data.line_length),
                            &(get_data()->south_img.img_data.endian));

    get_data()->east_img.img_data.img = safer_xpm_file_to_image(
        get_data()->mlx, "textures/future_wall.xpm",
        &(get_data()->east_img.width), &(get_data()->east_img.height));
    get_data()->east_img.img_data.addr =
        safer_get_data_addr(get_data()->east_img.img_data.img,
                            &(get_data()->east_img.img_data.bits_per_pixel),
                            &(get_data()->east_img.img_data.line_length),
                            &(get_data()->east_img.img_data.endian));

    get_data()->west_img.img_data.img = mlx_xpm_file_to_image(
        get_data()->mlx, "textures/future_wall.xpm",
        &(get_data()->west_img.width), &(get_data()->west_img.height));
    get_data()->west_img.img_data.addr =
        mlx_get_data_addr(get_data()->west_img.img_data.img,
                          &(get_data()->west_img.img_data.bits_per_pixel),
                          &(get_data()->west_img.img_data.line_length),
                          &(get_data()->west_img.img_data.endian));
    //===k
    get_data()->door_img.img_data.img = mlx_xpm_file_to_image(
        get_data()->mlx, "textures/door_frames/1.xpm",
        &(get_data()->door_img.width), &(get_data()->door_img.height));
    get_data()->door_img.img_data.addr =
        mlx_get_data_addr(get_data()->door_img.img_data.img,
                          &(get_data()->door_img.img_data.bits_per_pixel),
                          &(get_data()->door_img.img_data.line_length),
                          &(get_data()->door_img.img_data.endian));

    get_data()->door_open_img.img_data.img =
        mlx_xpm_file_to_image(get_data()->mlx, "textures/door_frames/17.xpm",
                              &(get_data()->door_open_img.width),
                              &(get_data()->door_open_img.height));
    get_data()->door_open_img.img_data.addr =
        mlx_get_data_addr(get_data()->door_open_img.img_data.img,
                          &(get_data()->door_open_img.img_data.bits_per_pixel),
                          &(get_data()->door_open_img.img_data.line_length),
                          &(get_data()->door_open_img.img_data.endian));
    printf("data addr = %p\n", get_data()->door_open_img.img_data.addr);

    get_data()->door_animating_img.img_data.img =
        mlx_xpm_file_to_image(get_data()->mlx, "textures/door_frames/13.xpm",
                              &(get_data()->door_animating_img.width),
                              &(get_data()->door_animating_img.height));
    get_data()->door_animating_img.img_data.addr = mlx_get_data_addr(
        get_data()->door_animating_img.img_data.img,
        &(get_data()->door_animating_img.img_data.bits_per_pixel),
        &(get_data()->door_animating_img.img_data.line_length),
        &(get_data()->door_animating_img.img_data.endian));
    printf("data addr 2 = %p\n", get_data()->door_animating_img.img_data.addr);
}

void render_frame()
{
    int shake_x = 0;
    int shake_y = 0;

    if (get_data()->screen_shake_timer > 0)
    {
        shake_x = (rand() % (2 * get_data()->screen_shake_intensity)) -
                  get_data()->screen_shake_intensity;
        shake_y = (rand() % (2 * get_data()->screen_shake_intensity)) -
                  get_data()->screen_shake_intensity;
        get_data()->screen_shake_timer--;
    }

    mlx_clear_window(get_data()->mlx, get_data()->win);
    mlx_put_image_to_window(get_data()->mlx, get_data()->win,
                            get_data()->background_img.img, shake_x, shake_y);
}

void load_shooting_gun3_frames(void)
{
    char *frame_paths[15] = {
        "textures/gun3shoot/1.xpm",  "textures/gun3shoot/2.xpm",
        "textures/gun3shoot/3.xpm",  "textures/gun3shoot/4.xpm",
        "textures/gun3shoot/5.xpm",  "textures/gun3shoot/6.xpm",
        "textures/gun3shoot/7.xpm",  "textures/gun3shoot/8.xpm",
        "textures/gun3shoot/9.xpm",  "textures/gun3shoot/10.xpm",
        "textures/gun3shoot/11.xpm", "textures/gun3shoot/12.xpm",
        "textures/gun3shoot/13.xpm", "textures/gun3shoot/14.xpm",
        "textures/gun3shoot/15.xpm"};
    int i;

    i = 0;

    while (i < 15)
    {
        get_data()->gun3.shooting_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        i++;
    }
    get_data()->gun3.current_frame = 0;
    get_data()->gun3.frame_delay = 0;
    get_data()->gun3.is_reloading = 0;
    get_data()->gun3.is_shooting = 0;
    get_data()->gun3.shooted = 0;
    get_data()->gun3.show_scope = 0;
}

void load_shooting_gun2_frames(void)
{
    char *frame_paths[27] = {"textures/gun2shoot/1gun2shoot.xpm",
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
                             "textures/gun2shoot/27gun2shoot.xpm"};
    int i;

    i = 0;
    while (i < 27)
    {
        get_data()->gun2.shooting_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun2.width,
            &get_data()->gun2.height);
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
    char *frame_paths[23] = {"textures/running_gun2/1running_gun2.xpm",
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
                             "textures/running_gun2/23running_gun2.xpm"};

    int i;
    i = 0;

    while (i < 23)
    {
        get_data()->gun2.running_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun2.width,
            &get_data()->gun2.height);
        i++;
    }
    get_data()->gun2.current_frame = 0;
    get_data()->gun2.frame_delay = 0;
}

void load_reloading_gun3_frames(void)
{
    char *frame_paths[12] = {
        "textures/reloading_gun3/1.xpm",  "textures/reloading_gun3/2.xpm",
        "textures/reloading_gun3/3.xpm",  "textures/reloading_gun3/4.xpm",
        "textures/reloading_gun3/5.xpm",  "textures/reloading_gun3/6.xpm",
        "textures/reloading_gun3/7.xpm",  "textures/reloading_gun3/8.xpm",
        "textures/reloading_gun3/9.xpm",  "textures/reloading_gun3/10.xpm",
        "textures/reloading_gun3/11.xpm", "textures/reloading_gun3/12.xpm"};

    printf("here\n");
    int i;
    i = 0;
    while (i < 12)
    {
        get_data()->gun3.img[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        i++;
    }
    get_data()->gun3.current_frame = 0;
    get_data()->gun3.frame_delay = 0;
    get_data()->gun3.is_reloading = 0;
    get_data()->gun3.is_shooting = 0;
    get_data()->gun3.shooted = 0;
}

void load_first_scope_frames(void)
{
    char *frame_paths[5] = {
        "textures/zoom_shoot_gun3/1.xpm", "textures/zoom_shoot_gun3/2.xpm",
        "textures/zoom_shoot_gun3/3.xpm", "textures/zoom_shoot_gun3/4.xpm",
        "textures/zoom_shoot_gun3/5.xpm"};

    int i;
    i = 0;
    while (i < 5)
    {
        get_data()->gun3.first_scope_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        i++;
    }
    get_data()->gun3.current_frame = 0;
    get_data()->gun3.frame_delay = 0;
    get_data()->gun3.is_reloading = 0;
    get_data()->gun3.is_shooting = 0;
    get_data()->gun3.shooted = 0;
    get_data()->gun3.is_showing_scope = 0;
}

void load_last_scope_frames(void)
{
    char *frame_paths[5] = {
        "textures/zoom_shoot_gun3/12.xpm", "textures/zoom_shoot_gun3/13.xpm",
        "textures/zoom_shoot_gun3/14.xpm", "textures/zoom_shoot_gun3/15.xpm",
        "textures/zoom_shoot_gun3/16.xpm"};

    int i = 0;
    i = 0;
    while (i < 5)
    {
        get_data()->gun3.last_scope_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        i++;
    }
    get_data()->gun3.current_frame = 0;
    get_data()->gun3.frame_delay = 0;
    get_data()->gun3.is_reloading = 0;
    get_data()->gun3.is_shooting = 0;
    get_data()->gun3.shooted = 0;
    get_data()->gun3.is_showing_scope = 0;
}

void load_walking_gun2_frames(void)
{
    char *frame_paths[13] = {"textures/moving_gun2_slow/1walk.xpm",
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
                             "textures/moving_gun2_slow/13walk.xpm"};

    int i;
    i = 0;

    while (i < 13)
    {
        get_data()->gun2.walking_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun2.width,
            &get_data()->gun2.height);
        i++;
    }
    get_data()->gun2.current_frame = 0;
    get_data()->gun2.frame_delay = 0;
}

void load_first_gun_frames(void)
{
    char *frame_paths[18] = {
        "textures/1.xpm",  "textures/2.xpm",  "textures/3.xpm",
        "textures/4.xpm",  "textures/5.xpm",  "textures/6.xpm",
        "textures/7.xpm",  "textures/8.xpm",  "textures/9.xpm",
        "textures/10.xpm", "textures/11.xpm", "textures/12.xpm",
        "textures/13.xpm", "textures/14.xpm", "textures/15.xpm",
        "textures/16.xpm", "textures/17.xpm", "textures/18.xpm",
    };
    int i;

    i = 0;
    while (i < 18)
    {
        get_data()->gun.img[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun.width,
            &get_data()->gun.height);
        i++;
    }
    get_data()->gun.current_frame = 0;
    get_data()->gun.frame_delay = 0;
    get_data()->gun.is_reloading = 0;
    get_data()->gun.shooted = 0;
}

// void update_door_animation(void)
// {
//     if (get_data()->door.is_opening)
//     {
//         if (get_data()->door.frame_delay++ >= 0)  // Adjust delay value as
//         needed
//         {
//             get_data()->door.frame_delay = 0;
//             get_data()->door.current_frame++;
//             if (get_data()->door.current_frame > 16)
//             {
//                 get_data()->door.current_frame = 16;  // Keep at last frame
//                 get_data()->door.is_opening = 0;
//                 get_data()->door.is_open = 1;
//                 get_data()->map[get_data()->door.y][get_data()->door.x] =
//                 'O';
//                 // get_data()->front_ray.map_y]

//             }

//             // Update the door texture
//             get_data()->door_img.img_data.img =
//             get_data()->door.img[get_data()->door.current_frame];
//             get_data()->door_img.img_data.addr = mlx_get_data_addr(
//                 get_data()->door_img.img_data.img,
//                 &get_data()->door_img.img_data.bits_per_pixel,
//                 &get_data()->door_img.img_data.line_length,
//                 &get_data()->door_img.img_data.endian
//             );
//             get_data()->is_updated = 1;
//         }
//     }
//     else if (get_data()->door.is_closing)
//     {
//         if (get_data()->door.frame_delay++ >= 0)  // Adjust delay value as
//         needed
//         {
//             get_data()->door.frame_delay = 0;
//             get_data()->door.current_frame--;

//             if (get_data()->door.current_frame <= 0)
//             {
//                 get_data()->door.current_frame = 0;  // Keep at first frame
//                 get_data()->door.is_closing = 0;
//                 get_data()->door.is_open = 0;
//                 get_data()->door.is_closed = 1;
//                 get_data()->map[get_data()->door.y][get_data()->door.x] =
//                 'D';
//             }

//             // Update the door texture
//             get_data()->door_img.img_data.img =
//             get_data()->door.img[get_data()->door.current_frame];
//             get_data()->door_img.img_data.addr = mlx_get_data_addr(
//                 get_data()->door_img.img_data.img,
//                 &get_data()->door_img.img_data.bits_per_pixel,
//                 &get_data()->door_img.img_data.line_length,
//                 &get_data()->door_img.img_data.endian
//             );
//             get_data()->is_updated = 1;
//         }
//     }
// }
void update_door_animation(void)
{
    // Find the animating door (marked with 'P')
    int found = 0;
    int door_x = 0, door_y = 0;

    // Search for the door marked with 'P'
    for (int y = 0; y < get_data()->height && !found; y++)
    {
        for (int x = 0; x < get_data()->width && !found; x++)
        {
            if (get_data()->map[y][x] == 'P')
            {
                door_x = x;
                door_y = y;
                found = 1;
                break;
            }
        }
    }

    // If no animating door found, return
    if (!found) return;

    if (get_data()->door.is_opening)
    {
        if (get_data()->door.frame_delay++ >= 3)
        {
            get_data()->door.frame_delay = 0;
            get_data()->door.current_frame++;

            if (get_data()->door.current_frame > 16)
            {
                get_data()->door.current_frame = 16;
                get_data()->door.is_opening = 0;
                get_data()->door.is_open = 1;
                // Animation complete, change 'P' to 'O'
                get_data()->map[door_y][door_x] = 'O';
            }

            // Update the door texture
            // get_data()->door_img.img_data.img =
            // get_data()->door.img[get_data()->door.current_frame];
            // get_data()->door_img.img_data.addr = mlx_get_data_addr(
            //     get_data()->door_img.img_data.img,
            //     &get_data()->door_img.img_data.bits_per_pixel,
            //     &get_data()->door_img.img_data.line_length,
            //     &get_data()->door_img.img_data.endian
            // );
            get_data()->door_animating_img.img_data.img =
                get_data()->door.img[get_data()->door.current_frame];
            get_data()->door_animating_img.img_data.addr = mlx_get_data_addr(
                get_data()->door_animating_img.img_data.img,
                &get_data()->door_animating_img.img_data.bits_per_pixel,
                &get_data()->door_animating_img.img_data.line_length,
                &get_data()->door_animating_img.img_data.endian);
            get_data()->is_updated = 1;
        }
    }
    else if (get_data()->door.is_closing)
    {
        if (get_data()->door.frame_delay++ >= 3)
        {
            get_data()->door.frame_delay = 0;
            get_data()->door.current_frame--;

            if (get_data()->door.current_frame <= 0)
            {
                get_data()->door.current_frame = 0;
                get_data()->door.is_closing = 0;
                get_data()->door.is_open = 0;
                get_data()->door.is_closed = 1;
                // Animation complete, change 'P' to 'D'
                get_data()->map[door_y][door_x] = 'D';
            }

            // Update the door texture
            // get_data()->door_img.img_data.img =
            // get_data()->door.img[get_data()->door.current_frame];
            // get_data()->door_img.img_data.addr = mlx_get_data_addr(
            //     get_data()->door_img.img_data.img,
            //     &get_data()->door_img.img_data.bits_per_pixel,
            //     &get_data()->door_img.img_data.line_length,
            //     &get_data()->door_img.img_data.endian
            // );

            get_data()->door_animating_img.img_data.img =
                get_data()->door.img[get_data()->door.current_frame];
            get_data()->door_animating_img.img_data.addr = mlx_get_data_addr(
                get_data()->door_animating_img.img_data.img,
                &get_data()->door_animating_img.img_data.bits_per_pixel,
                &get_data()->door_animating_img.img_data.line_length,
                &get_data()->door_animating_img.img_data.endian);
            get_data()->is_updated = 1;
        }
    }
}

// Implementation of gun loading and animation functions
void load_frames(void)
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
    int i;

    i = 0;
    while (i < 20)
    {
        get_data()->gun2.img[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun2.width,
            &get_data()->gun2.height);
        i++;
    }
    get_data()->gun2.current_frame = 0;
    get_data()->gun2.frame_delay = 0;
    get_data()->gun2.is_reloading = 0;
    get_data()->gun2.shooted = 0;
}

void render_gun_frames(int num_frames, t_gun *gun, int frame_delay)
{
    if (gun->frame_delay++ >= frame_delay)  // Adjust delay value as needed
    {
        gun->frame_delay = 1;
        gun->current_frame++;
        if (gun->current_frame >= num_frames)
        {
            gun->current_frame = 0;
            gun->is_shooting = 0;
            gun->is_reloading = 0;
            // gun->is_zooming = 0;
        }
    }
}

void render_reloading(int gun_id)
{
    if (gun_id == 1)
    {
        render_gun_frames(20, &get_data()->gun2, 10);
        render_transparent_frame(
            get_data()->gun2.img[get_data()->gun2.current_frame],
            get_data()->gun2.width, get_data()->gun2.height);
    }
    else if (gun_id == 0)
    {
        render_gun_frames(18, &get_data()->gun, 10);
    }
    else if (gun_id == 2)
    {
        render_gun_frames(12, &get_data()->gun3, 25);
    }
}

void render_shooting(int gun_id)
{
    if (gun_id == 0)
    {
    }
    if (gun_id == 1)
        render_gun_frames(27, &get_data()->gun2, 1);
    else if (gun_id == 2)
        render_gun_frames(15, &get_data()->gun3, 5);
}

void render_showing_scope(int gun_id)
{
    if (gun_id == 2)
    {
        if (get_data()->gun3.frame_delay++ >=
            13)  // Adjust delay value as needed
        {
            get_data()->gun3.frame_delay = 1;
            get_data()->gun3.current_frame++;
            if (get_data()->gun3.current_frame >= 5)
            {
                get_data()->gun3.current_frame = 5;
                get_data()->gun3.is_showing_scope = 0;
            }
        }
    }
}

void render_gun3(void)
{
    if (get_data()->gun3.is_shooting)
    {
        render_shooting(2);
        render_transparent_frame(
            get_data()->gun3.shooting_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
        render_frame();
    }
    // else if (get_data()->gun3.is_showing_scope &&
    // !get_data()->gun3.show_scope)
    // {
    //     render_showing_scope(2);
    //     if (get_data()->gun3.show_scope)
    //         render_transparent_frame(
    //             get_data()
    //                 ->gun3.first_scope_frames[get_data()->gun3.current_frame],
    //             get_data()->gun3.width, get_data()->gun3.height);
    // }
    else if (get_data()->gun3.is_showing_scope && get_data()->gun3.show_scope)
    {
        render_showing_scope(2);
        render_transparent_frame(
            get_data()->gun3.last_scope_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    }
    else if (get_data()->gun3.is_reloading)
    {
        render_reloading(2);
        render_transparent_frame(
            get_data()->gun3.img[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    }
    if (!get_data()->gun3.is_reloading && !get_data()->gun3.show_scope)
        render_transparent_frame(
            get_data()->gun3.shooting_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    else if (!get_data()->gun3.is_reloading && get_data()->gun3.show_scope)
        render_transparent_frame(
            get_data()->gun3.first_scope_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
}

void render_gun1(void)
{
    if (get_data()->gun.is_reloading) render_reloading(0);
    render_transparent_frame(get_data()->gun.img[get_data()->gun.current_frame],
                             get_data()->gun.width, get_data()->gun.height);
}

void render_gun2(void)
{
    if (get_data()->gun2.is_reloading)
        render_reloading(1);
    else if (get_data()->gun2.is_shooting)
        render_shooting(1);
    else if (get_data()->is_walking)
    {
        render_gun_frames(13, &get_data()->gun2, 4);
        render_transparent_frame(
            get_data()->gun2.walking_frames[get_data()->gun2.current_frame],
            get_data()->gun2.width, get_data()->gun2.height);
    }
    else if (get_data()->is_running)
    {
        render_gun_frames(19, &get_data()->gun2, 4);
        render_transparent_frame(
            get_data()->gun2.running_frames[get_data()->gun2.current_frame],
            get_data()->gun2.width, get_data()->gun2.height);
    }

    if (get_data()->gun2.is_reloading == 0 && get_data()->is_walking == 0 &&
        get_data()->is_running == 0)
        render_transparent_frame(
            get_data()->gun2.shooting_frames[get_data()->gun2.current_frame],
            get_data()->gun2.width, get_data()->gun2.height);
}

void render_gun(void)
{
    if (get_data()->gun_id == 0) render_gun1();
    if (get_data()->gun_id == 1) render_gun2();
    if (get_data()->gun_id == 2) render_gun3();
    render_frame();
}

int player_is_close_to_door(void)
{
    return (get_data()->front_ray.dist < 2 * GRID_DIST);
}

int loop_hook(void)
{
    if (get_data()->is_tab_pressed)
    {
        render_tab();
        return (0);
    }
    if (get_data()->is_updated)
    {
        update_movement();
        init_background();
        render_walls();
        render_minimap();
        update_door_animation();
        render_background();
        render_gun();
        // printf("is walking = %d\n", get_data()->is_walking);
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
    render_minimap();
    render_background();
    load_frames();
    load_first_gun_frames();
    load_shooting_gun3_frames();
    load_shooting_gun2_frames();
    load_running_gun2_frames();
    load_walking_gun2_frames();
    load_reloading_gun3_frames();
    load_first_scope_frames();
    load_last_scope_frames();
    load_door_frames();
    mlx_loop_hook(get_data()->mlx, loop_hook, NULL);

    mlx_loop(get_data()->mlx);

    return (0);
}
