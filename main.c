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
void    load_door_frames(void)
{
    char    *frame_paths[20];
    int     i;
    char    path[50];

    i = 0;
    while (i < 20)
    {
        sprintf(path, "textures/door%d.xpm", i + 1);
        frame_paths[i] = ft_strdup(path);
        get_data()->door.img[i] = mlx_xpm_file_to_image(get_data()->mlx, 
            frame_paths[i], &get_data()->door.width, &get_data()->door.height);
        if (!get_data()->door.img[i])
        {
            print_err("Failed to load door frame\n");
            exiter(1);
        }
        free(frame_paths[i]);
        i++;
    }
    get_data()->door.current_frame = 0;
    get_data()->door.frame_delay = 0;
    get_data()->door.is_opening = 0;
    get_data()->door.is_open = 0;
}
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
	// mlx_hook(get_data()->win, 3, 1L << 1, handle_realise, NULL);// this to handle when a key released
	mlx_hook(get_data()->win, 17, 1L << 0, ft_close, NULL);// this to handle when red arrow clicked
	mlx_hook(get_data()->win, 6, 1L<<6, mouse_event, NULL);
	get_data()->player_pos.x = game.player.pos_x * GRID_DIST + GRID_DIST/2;//1. * GRID_DIST;// TODO for test only
	get_data()->player_pos.y =  game.player.pos_y * GRID_DIST + GRID_DIST/2;//1. * GRID_DIST;// TODO for test only
	get_data()->player_angle = 0;//MY_PI / 4;
	get_data()->player_dir.x = cos(get_data()->player_angle) * SPEED;
	get_data()->player_dir.y = sin(get_data()->player_angle) * SPEED;

	get_data()->map = game.map.grid;
	get_data()->height = game.map.height;
	get_data()->width = game.map.width;

	get_data()->north_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/wall.xpm", &(get_data()->north_img.width), &(get_data()->north_img.height));
	get_data()->north_img.img_data.addr = mlx_get_data_addr(get_data()->north_img.img_data.img, &(get_data()->north_img.img_data.bits_per_pixel), &(get_data()->north_img.img_data.line_length), &(get_data()->north_img.img_data.endian));

	get_data()->south_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/wall.xpm", &(get_data()->south_img.width), &(get_data()->south_img.height));
	get_data()->south_img.img_data.addr = mlx_get_data_addr(get_data()->south_img.img_data.img, &(get_data()->south_img.img_data.bits_per_pixel), &(get_data()->south_img.img_data.line_length), &(get_data()->south_img.img_data.endian));

	get_data()->east_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/wall.xpm", &(get_data()->east_img.width), &(get_data()->east_img.height));
	get_data()->east_img.img_data.addr = mlx_get_data_addr(get_data()->east_img.img_data.img, &(get_data()->east_img.img_data.bits_per_pixel), &(get_data()->east_img.img_data.line_length), &(get_data()->east_img.img_data.endian));
	
	get_data()->west_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/wall.xpm", &(get_data()->west_img.width), &(get_data()->west_img.height));
	get_data()->west_img.img_data.addr = mlx_get_data_addr(get_data()->west_img.img_data.img, &(get_data()->west_img.img_data.bits_per_pixel), &(get_data()->west_img.img_data.line_length), &(get_data()->west_img.img_data.endian));
	//===
	get_data()->door_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/door1.xpm", &(get_data()->door_img.width), &(get_data()->door_img.height));
	get_data()->door_img.img_data.addr = mlx_get_data_addr(get_data()->door_img.img_data.img, &(get_data()->door_img.img_data.bits_per_pixel), &(get_data()->door_img.img_data.line_length), &(get_data()->door_img.img_data.endian));
    load_door_frames();
}

void update_door_animation(void)
{
    if (get_data()->door.is_opening)
    {
        if (get_data()->door.frame_delay++ >= 3)
        {
            get_data()->door.frame_delay = 0;
            get_data()->door.current_frame++;
            
             if (get_data()->door.current_frame >= 20)
            {
                get_data()->door.current_frame = 19;
                get_data()->door.is_opening = 0;
                get_data()->door.is_open = 1;
            }
            
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
            }
            
            // Update the door texture
            get_data()->door_img.img_data.img = get_data()->door.img[get_data()->door.current_frame];
            get_data()->door_img.img_data.addr = mlx_get_data_addr(
                get_data()->door_img.img_data.img,
                &get_data()->door_img.img_data.bits_per_pixel,
                &get_data()->door_img.img_data.line_length,
                &get_data()->door_img.img_data.endian
            );
        }
    }
}

// Implementation of gun loading and animation functions
void    load_frames(void)
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
    get_data()->gun.is_shooting = 0;
    get_data()->gun.shooted = 0;
}

void    render_gun(void)
{
    int         gun_pos_x;
    int         gun_pos_y;

    // Calculate gun position
    gun_pos_x = WIN_WIDTH / 2 - get_data()->gun.width / 2;
    gun_pos_y = WIN_HEIGHT - get_data()->gun.height + 4;

    // Handle shooting animation
    if (get_data()->gun.is_shooting)
    {
        if (get_data()->gun.frame_delay++ >= 3)  // Adjust delay value as needed
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
    // Render the current frame
    mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
        get_data()->gun.img[get_data()->gun.current_frame], 
        gun_pos_x, gun_pos_y);
}

int loop_hook(t_game *game)
{
	if (get_data()->is_updated)
	{
		init_background();
		render_walls();
		render_minimap();
        update_door_animation();  
		render_background();
		render_gun();
    	if (get_data()->front_ray.object_hitted == 1 && 
        	get_data()->front_ray.dist < 2 * GRID_DIST)
        {

            /**
             * mlx_xpm_file_to_image - Converts an XPM file to an image.
             * @mlx_ptr: Pointer to the MLX instance.
             * @filename: Path to the XPM file.
             * @width: Pointer to an integer where the width of the image will be stored.
             * @height: Pointer to an integer where the height of the image will be stored.
             *
             * This function loads an XPM (X PixMap) file and converts it into an image
             * that can be used with the MLX library. The width and height of the image
             * are stored in the provided pointers.
             *
             * Returns: A pointer to the created image, or NULL if the operation fails.
             */

        }
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
        if (get_data()->gun.shooted == 0)
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
	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);

    mlx_loop(get_data()->mlx);

    return (0);
}