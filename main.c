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
#include "garbage_collector/heap_controller.h"

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
    if (!frame_img)
    {
        printf("frame_img is null\n");
        return;
    }
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
        if (get_data()->gun.frame_delay++ >= 14)
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
        get_data()->gun.reloading_frames[get_data()->gun.current_frame],
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
            // printf("%d ", i);
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
    mlx_mouse_hook(get_data()->win, handle_mouse_event, NULL);
    get_data()->speed = 4;
    get_data()->player_pos.x =
        game.player.pos_x * GRID_DIST +
        (float)GRID_DIST / 2;  // 1. * GRID_DIST;// TODO for test only
    get_data()->player_pos.y =
        game.player.pos_y * GRID_DIST +
        (float)GRID_DIST / 2;      // 1. * GRID_DIST;// TODO for test only
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
    get_data()->zoom_factor = 1;
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
    // printf("data addr = %p\n", get_data()->door_open_img.img_data.addr);

    get_data()->door_animating_img.img_data.img =
        mlx_xpm_file_to_image(get_data()->mlx, "textures/door_frames/13.xpm",
                              &(get_data()->door_animating_img.width),
                              &(get_data()->door_animating_img.height));
    get_data()->door_animating_img.img_data.addr = mlx_get_data_addr(
        get_data()->door_animating_img.img_data.img,
        &(get_data()->door_animating_img.img_data.bits_per_pixel),
        &(get_data()->door_animating_img.img_data.line_length),
        &(get_data()->door_animating_img.img_data.endian));

    // get_data()->enemie_on_map.img = safer_xpm_file_to_image(get_data()->mlx,
    // "skull.xpm", &(get_data()->enemie_on_map.width),
    // &(get_data()->enemie_on_map.height)); get_data()->enemie_on_map.addr =
    // safer_get_data_addr(
    //     get_data()->enemie_on_map.img,
    //     &(get_data()->enemie_on_map.bits_per_pixel),
    //     &(get_data()->enemie_on_map.line_length),
    //     &(get_data()->enemie_on_map.endian));

    // printf("data addr 2 = %p\n",
    // get_data()->door_animating_img.img_data.addr);
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

void update_enemy_frames(void)
{
    int i;

    for (i = 0; i < get_data()->num_sprites; i++)
    {
        if (get_data()->sprites[i].frame_delay >= 8)
        {
            get_data()->sprites[i].current_frame++;
            if (get_data()->sprites[i].current_frame >= 21)
                get_data()->sprites[i].current_frame = 0;
            // get_data()->sprites[i].texture.img_data.img =
            //     get_data()
            //         ->sprites_frames[get_data()->sprites[i].current_frame];
            // printf("sprite frame that is being displayed is %p\n",
            //        get_data()->sprites[i].texture.img_data.img);
            get_data()->sprites[i].frame_delay = 0;
        }
        else
        {
            get_data()->sprites[i].frame_delay++;
        }
    }
}

void load_load_sprite_frames(void)
{
    // char *frame_paths[7] = {"textures/spider/1.xpm", "textures/spider/2.xpm",
    //                         "textures/spider/3.xpm", "textures/spider/4.xpm",
    //                         "textures/spider/5.xpm", "textures/spider/6.xpm",
    //                         "textures/spider/7.xpm"};
    char *frame_paths[21] = {"textures/zombie/1.xpm",  "textures/zombie/2.xpm",
                             "textures/zombie/3.xpm",  "textures/zombie/4.xpm",
                             "textures/zombie/5.xpm",  "textures/zombie/6.xpm",
                             "textures/zombie/7.xpm",  "textures/zombie/8.xpm",
                             "textures/zombie/9.xpm",  "textures/zombie/10.xpm",
                             "textures/zombie/11.xpm", "textures/zombie/12.xpm",
                             "textures/zombie/13.xpm", "textures/zombie/14.xpm",
                             "textures/zombie/15.xpm", "textures/zombie/16.xpm",
                             "textures/zombie/17.xpm", "textures/zombie/18.xpm",
                             "textures/zombie/19.xpm", "textures/zombie/20.xpm",
                             "textures/zombie/21.xpm"};

    int i;
    i = 0;
    while (i < 21)
    {
        printf("frame_paths[%d], %p\n", i, frame_paths[i]);
        get_data()->sprites_frames[i].img_data.img =
            safer_xpm_file_to_image(get_data()->mlx, frame_paths[i],
                                    &get_data()->sprites_frames[i].width,
                                    &get_data()->sprites_frames[i].height);
        get_data()->sprites_frames[i].img_data.addr = safer_get_data_addr(
            get_data()->sprites_frames[i].img_data.img,
            &get_data()->sprites_frames[i].img_data.bits_per_pixel,
            &get_data()->sprites_frames[i].img_data.line_length,
            &get_data()->sprites_frames[i].img_data.endian);
        i++;
    }
    get_data()->sprites[0].current_frame = 0;
    get_data()->sprites[0].frame_delay = 0;
}

void load_running_gun3_frames(void)
{
    char *frame_paths[11] = {
        "textures/running_gun3/1.xpm", "textures/running_gun3/2.xpm",
        "textures/running_gun3/3.xpm", "textures/running_gun3/4.xpm",
        "textures/running_gun3/5.xpm", "textures/running_gun3/6.xpm",
        "textures/running_gun3/7.xpm", "textures/running_gun3/8.xpm",
        "textures/running_gun3/9.xpm", "textures/running_gun3/10.xpm",
        "textures/running_gun3/11.xpm"};

    int i;
    i = 0;

    while (i < 11)
    {
        get_data()->gun3.running_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        i++;
    }
    get_data()->gun3.current_frame = 0;
    get_data()->gun3.frame_delay = 0;
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

    // printf("here\n");
    int i;
    i = 0;
    while (i < 12)
    {
        get_data()->gun3.reloading_frames[i] = safer_xpm_file_to_image(
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
    char *frame_paths[6] = {
        "textures/zoom_shoot_gun3/1.xpm", "textures/zoom_shoot_gun3/2.xpm",
        "textures/zoom_shoot_gun3/3.xpm", "textures/zoom_shoot_gun3/4.xpm",
        "textures/zoom_shoot_gun3/5.xpm", "textures/zoom_shoot_gun3/6.xpm"};

    int i;
    i = 0;
    while (i < 6)
    {
        get_data()->gun3.first_scope_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        // printf("gun3 scope frame %d: %p\n", i,
        //        get_data()->gun3.first_scope_frames[i]);
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
        // printf("gun3 last scope frame %d: %p\n", i,
        //        get_data()->gun3.last_scope_frames[i]);
        i++;
    }
    get_data()->gun3.current_frame = 4;
    get_data()->gun3.frame_delay = 0;
    get_data()->gun3.is_reloading = 0;
    get_data()->gun3.is_shooting = 0;
    get_data()->gun3.shooted = 0;
    get_data()->gun3.is_showing_scope = 0;
}

void load_shooting_scope_frames(void)
{
    char *frame_paths[6] = {
        "textures/zoom_shoot_gun3/6.xpm",  "textures/zoom_shoot_gun3/7.xpm",
        "textures/zoom_shoot_gun3/8.xpm",  "textures/zoom_shoot_gun3/9.xpm",
        "textures/zoom_shoot_gun3/10.xpm", "textures/zoom_shoot_gun3/10.xpm"};

    int i = 0;
    i = 0;
    while (i < 6)
    {
        get_data()->gun3.scope_shooting_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        // printf("frame %p\n", get_data()->gun3.scope_shooting_frames[i]);
        i++;
    }
    get_data()->gun3.current_frame = 4;
    get_data()->gun3.frame_delay = 0;
    get_data()->gun3.is_reloading = 0;
    get_data()->gun3.is_shooting = 0;
    get_data()->gun3.shooted = 0;
    get_data()->gun3.is_showing_scope = 0;
    get_data()->gun3.is_showing_scope = 0;
}

void load_walking_gun3_frames(void)
{
    char *frame_paths[11] = {"textures/movin_walk_gun3_slow/1.xpm",
                             "textures/movin_walk_gun3_slow/2.xpm",
                             "textures/movin_walk_gun3_slow/3.xpm",
                             "textures/movin_walk_gun3_slow/4.xpm",
                             "textures/movin_walk_gun3_slow/5.xpm",
                             "textures/movin_walk_gun3_slow/6.xpm",
                             "textures/movin_walk_gun3_slow/7.xpm",
                             "textures/movin_walk_gun3_slow/8.xpm",
                             "textures/movin_walk_gun3_slow/9.xpm",
                             "textures/movin_walk_gun3_slow/10.xpm",
                             "textures/movin_walk_gun3_slow/11.xpm"};

    int i;
    i = 0;

    while (i < 11)
    {
        get_data()->gun3.walking_frames[i] = safer_xpm_file_to_image(
            get_data()->mlx, frame_paths[i], &get_data()->gun3.width,
            &get_data()->gun3.height);
        i++;
    }
    get_data()->gun3.current_frame = 0;
    get_data()->gun3.frame_delay = 0;
}

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

void render_scope_frames(int num_frames, t_gun *gun, int frame_delay)
{
    if (gun->frame_delay++ >= frame_delay)  // Adjust delay value as needed
    {
        gun->frame_delay = 1;
        gun->current_frame++;
        if (gun->current_frame >= num_frames)
        {
            gun->current_frame = 0;
            gun->is_shooting = num_frames;
            gun->is_reloading = 0;
            // gun->is_zooming = 0;
        }
    }
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
    if (gun_id == 2)
    {
        render_gun_frames(15, &get_data()->gun3, 25);
    }
}

void render_shooting(int gun_id)
{
    if (gun_id == 2) render_gun_frames(15, &get_data()->gun3, 5);
}

void render_gun3(void)
{
    // printf("show scope = %d\n", get_data()->gun3.show_scope);
    if (get_data()->gun3.is_showing_scope)
    {
        // printf("show scope = %d\n", get_data()->gun3.show_scope);
        if (get_data()->gun3.show_scope)
        {
            if (get_data()->gun3.frame_delay++ >=
                5)  // Adjust delay value as needed
            {
                get_data()->gun3.frame_delay = 1;
                get_data()->gun3.current_frame++;
                // printf("zoom factor : %f\n", get_data()->zoom_factor);
                get_data()->zoom_factor -= 0.06;
                if (get_data()->gun3.current_frame >= 5)
                {
                    get_data()->gun3.current_frame = 5;
                    get_data()->gun3.is_showing_scope = 0;
                    get_data()->zoom_factor += 0.06;
                }
            }
        }
        else
        {
            if (get_data()->gun3.frame_delay++ >=
                5)  // Adjust delay value as needed
            {
                get_data()->gun3.frame_delay = 1;
                get_data()->gun3.current_frame++;
                get_data()->zoom_factor += 0.06;
                // printf("zoom factor : %f\n", get_data()->zoom_factor);
                if (get_data()->gun3.current_frame >= 4)
                {
                    get_data()->gun3.current_frame = 4;
                    get_data()->gun3.is_showing_scope = 0;
                }
            }
        }
    }
    else if (get_data()->gun3.is_shooting)
    {
        // printf("%s show scope = %d\n%s", CGREEN, get_data()->gun3.show_scope,
        // CWHITE);
        if (get_data()->gun3.show_scope == 1)
        {
            if (get_data()->gun3.frame_delay++ >=
                5)  // Adjust delay value as needed
            {
                get_data()->gun3.frame_delay = 1;
                get_data()->gun3.current_frame++;
                if (get_data()->gun3.current_frame >= 6)
                {
                    get_data()->gun3.current_frame = 5;
                    get_data()->gun3.is_shooting = 0;
                    get_data()->gun3.is_reloading = 0;
                    // get_data()->gun3.is_zooming = 0;
                }
            }
            render_transparent_frame(
                get_data()
                    ->gun3
                    .scope_shooting_frames[get_data()->gun3.current_frame],
                get_data()->gun3.width, get_data()->gun3.height);
            render_frame();
        }
        else if (get_data()->gun3.show_scope == 0)
        {
            // printf("shooting normal\n");
            render_shooting(2);
            // printf("data = %p, frame = %d\n",
            //        get_data()
            //            ->gun3.shooting_frames[get_data()->gun3.current_frame],
            //        get_data()->gun3.current_frame);

            if (get_data()->gun3.frame_delay++ >=
                5)  // Adjust delay value as needed
            {
                get_data()->gun3.frame_delay = 1;
                get_data()->gun3.current_frame++;
                if (get_data()->gun3.current_frame >= 12)
                {
                    get_data()->gun3.current_frame = 4;
                    get_data()->gun3.is_shooting = 0;
                    get_data()->gun3.is_reloading = 0;
                    // get_data()->gun3.is_zooming = 0;
                }
            }
            render_transparent_frame(
                get_data()
                    ->gun3.shooting_frames[get_data()->gun3.current_frame],
                get_data()->gun3.width, get_data()->gun3.height);
            render_frame();
        }
    }
    else if (get_data()->gun3.is_reloading)
    {
        render_reloading(2);
        render_transparent_frame(
            get_data()->gun3.reloading_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    }
    else if (get_data()->is_walking && !get_data()->gun3.show_scope)
    {
        render_gun_frames(11, &get_data()->gun3, 14);
        render_transparent_frame(
            get_data()->gun3.walking_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    }
    else if (get_data()->is_running && !get_data()->gun3.show_scope &&
             !get_data()->is_walking)
    {
        render_gun_frames(11, &get_data()->gun3, 20);
        render_transparent_frame(
            get_data()->gun3.running_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    }
    if (!get_data()->gun3.show_scope && !get_data()->gun3.is_reloading &&
        !get_data()->gun3.is_shooting && !get_data()->is_running)
    {
        // printf("%sframe in last scope loaded is %d\n%s", CGREEN,
        // get_data()->gun3.current_frame, CWHITE);
        // render_transparent_frame(
        //     get_data()->gun3.last_scope_frames[get_data()->gun3.current_frame],
        //     get_data()->gun3.width, get_data()->gun3.height);
        render_transparent_frame(
            get_data()->gun3.walking_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    }
    if (get_data()->gun3.show_scope && !get_data()->gun3.is_reloading &&
        !get_data()->gun3.is_shooting)
    {
        // printf("%sframe in first scope loaded is %d\n%s", CRED,
        //        get_data()->gun3.current_frame, CWHITE);
        render_transparent_frame(
            get_data()->gun3.first_scope_frames[get_data()->gun3.current_frame],
            get_data()->gun3.width, get_data()->gun3.height);
    }
}

void render_gun1(void)
{
    if (get_data()->gun.is_reloading) render_reloading(0);
    render_transparent_frame(
        get_data()->gun.reloading_frames[get_data()->gun.current_frame],
        get_data()->gun.width, get_data()->gun.height);
}

void render_gun(void)
{
    if (get_data()->gun_id == 2) render_gun3();
    render_frame();
}

int player_is_close_to_door(void)
{
    return (get_data()->front_ray.dist < 2 * GRID_DIST);
}

void render_cercle()
{
    int x, y;
    int radius = 7;
    // int radius = game->player.radius;
    int center_x = WIN_WIDTH / 2;
    int center_y = WIN_HEIGHT / 2;
    // fprintf(stderr, "x== %d,  y==%d\n", center_x, center_y);

    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                put_pixel(&(get_data()->background_img), center_x + x,
                          center_y + y, BLACK);
            }
        }
    }
}

int loop_hook(void)
{
    if (get_data()->is_tab_pressed)
    {
        // render_tab();
        return (0);
    }
    if (get_data()->is_updated)
    {
        update_movement();
        init_background();
        render_walls();
        render_minimap();
        update_enemy_frames();
        render_sprites();
        update_door_animation();
        render_background();
        render_gun();
        render_cercle();
        // erintf("is walking = %d\n", get_data()->is_walking);
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
    init_sprites(&game);
    init_background();
    render_walls();
    render_minimap();

    update_enemy_frames();  //
    render_sprites();       //
    render_background();
    // load_frames();
    load_shooting_gun3_frames();
    load_running_gun3_frames();
    load_reloading_gun3_frames();
    load_first_scope_frames();
    load_last_scope_frames();
    // load_last_scope_frames2();
    load_shooting_scope_frames();
    load_load_sprite_frames();
    load_walking_gun3_frames();
    load_door_frames();
    // render_gun3();
    mlx_loop_hook(get_data()->mlx, loop_hook, NULL);

    mlx_loop(get_data()->mlx);

    return (0);
}
