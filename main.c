/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:26 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/09 23:27:28 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// this will be used to store data and share it
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
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

	get_data()->north_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->north_img.width), &(get_data()->north_img.height));
	get_data()->north_img.img_data.addr = mlx_get_data_addr(get_data()->north_img.img_data.img, &(get_data()->north_img.img_data.bits_per_pixel), &(get_data()->north_img.img_data.line_length), &(get_data()->north_img.img_data.endian));

	get_data()->south_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->south_img.width), &(get_data()->south_img.height));
	get_data()->south_img.img_data.addr = mlx_get_data_addr(get_data()->south_img.img_data.img, &(get_data()->south_img.img_data.bits_per_pixel), &(get_data()->south_img.img_data.line_length), &(get_data()->south_img.img_data.endian));

	get_data()->east_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->east_img.width), &(get_data()->east_img.height));
	get_data()->east_img.img_data.addr = mlx_get_data_addr(get_data()->east_img.img_data.img, &(get_data()->east_img.img_data.bits_per_pixel), &(get_data()->east_img.img_data.line_length), &(get_data()->east_img.img_data.endian));
	
	get_data()->west_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/north.xpm", &(get_data()->west_img.width), &(get_data()->west_img.height));
	get_data()->west_img.img_data.addr = mlx_get_data_addr(get_data()->west_img.img_data.img, &(get_data()->west_img.img_data.bits_per_pixel), &(get_data()->west_img.img_data.line_length), &(get_data()->west_img.img_data.endian));
	//===
	get_data()->door_img.img_data.img = mlx_xpm_file_to_image(get_data()->mlx, "textures/gate.xpm", &(get_data()->door_img.width), &(get_data()->door_img.height));
	get_data()->door_img.img_data.addr = mlx_get_data_addr(get_data()->door_img.img_data.img, &(get_data()->door_img.img_data.bits_per_pixel), &(get_data()->door_img.img_data.line_length), &(get_data()->door_img.img_data.endian));
}

// void	draw_circle(t_img_data *img, int cho3a3, t_vector point)
// {
// 	int i = point.y - cho3a3;
// 	int j;

// 	while (i < point.y + cho3a3)
// 	{
// 		j = point.x - cho3a3;
// 		while (j < point.x + cho3a3)
// 		{
// 			if (calc_dist(j, i, point) <= cho3a3)
// 			{
// 				// printf("pixeled the point x ==%d  | y == %d | with dist == %d\n", j, i, calc_dist(j, i, point));
// 				put_pixel(img, j, i, RED);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_player(void)
// {
// 	t_vector player_front;

// 	player_front.x = get_data()->player_pos.x / SQUARE_SIZE + 5 * get_data()->player_dir.x;
// 	player_front.y = get_data()->player_pos.y  / SQUARE_SIZE + 5 * get_data()->player_dir.y;
// 	draw_circle(&(get_data()->background_img), 7, get_data()->player_pos);
// 	line_between_2points(get_data()->player_pos,
// 				player_front, RED);
// }

// check file 
	// check extension
	// check the file if exists or empty 



// int key_press(int keycode, t_game *game)
// {
//    if (keycode == ESC_MAC)
// 	{
// 		exit(0);
// 	}
// 	else if (keycode == UP_MAC) // 	{
// 		printf("UP\n");
// 		game->player.walk_direction = 1;
// 	}
// 	else if (keycode == DOWN_MAC)
// 	{
// 		printf("Down\n");
// 		game->player.walk_direction = -1;
// 	}
// 	else if (keycode == LEFT_MAC)
// 	{
// 		printf("Left\n");
// 		game->player.turn_direction = -1;
// 	}
// 	else if (keycode == RIGHT_MAC)
// 	{
// 		printf("Right\n");
// 		game->player.turn_direction = 1;
// 	} 
// 	return (0);
// }

// int key_release(int keycode, t_game *game)
// {
//     if (keycode == UP_MAC || keycode == DOWN_MAC)
//         game->player.walk_direction = 0;
//     if (keycode == LEFT_MAC || keycode == RIGHT_MAC)
//         game->player.turn_direction = 0;
//     return (0);
// }
// void update_player(t_game *game)
// {
//     // game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
// 	// double move_step = game->player.walk_direction * game->player.move_speed;
// 	// double new_player_x = game->player.pos_x + sin(game->player.rotation_angle) * move_step;
// 	// double new_player_y = game->player.pos_y + cos(game->player.rotation_angle) * move_step;
// 	// if (has_wall_at(game, new_player_x, new_player_y) != 1)
// 	// {
// 	// 	game->player.pos_x = new_player_x;
// 	// 	game->player.pos_y = new_player_y;
// 	// 	printf("%snew_player_x = %.2f, new_player_y = %.2f\n%s",CRED,  new_player_x, new_player_y, CRESET);
// 	// }


// }
// void cast_all_rays(t_game *game)
// {
// 	int column_id = 0;

// 	game->ray_angle = game->player.rotation_angle - (FOV_ANGLE / 2);
// 	game->rays = malloc(sizeof(t_ray) * game->num_rays);
// 	while (column_id < game->num_rays)
// 	{
// 		// game->rays[column_id].ray_angle = normalize_angle(game->ray_angle);
// 		// game->rays[column_id].wall_hit_x = 0;
// 		// game->rays[column_id].wall_hit_y = 0;
// 		// game->rays[column_id].distance = 0;
// 		// game->rays[column_id].was_hit_vertical = 0;
// 		// cast_ray(game, column_id);
// 		game->rays[column_id].ray_angle = game->ray_angle;
// 		game->ray_angle += FOV_ANGLE / game->num_rays;
// 		column_id++;
// 	}

// 	// printf("%s========RAYS========%s\n", CRED, CRESET);
// 	// int i = 0;
// 	// while (i < game->num_rays)
// 	// {
// 	// 	printf("ray_angle = %f\n", game->rays[i].ray_angle);
// 	// 	i++;
// 	// }
// 	// printf("%s====================%s\n", CRED, CRESET);
// }
// -------------

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
}

void    render_gun(void)
{
    // static int  idle_delay = 0;
    int         gun_pos_x;
    int         gun_pos_y;

    // Calculate gun position
    gun_pos_x = WIN_WIDTH / 2 - get_data()->gun.width / 2;
    gun_pos_y = WIN_HEIGHT - get_data()->gun.height + 4;

    // Handle shooting animation
    if (get_data()->gun.is_shooting)
    {
        if (get_data()->gun.frame_delay++ >= 5)  // Adjust delay value as needed
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
    // Handle idle animation (only frames 1 and 2)
    // else
    // {
    //     if (idle_delay++ >= 20)  // Slower animation for idle state
    //     {
    //         idle_delay = 0;
    //         get_data()->gun.current_frame = (get_data()->gun.current_frame == 0) ? 1 : 0;
    //     }
    // }

    // Render the current frame
    mlx_put_image_to_window(get_data()->mlx, get_data()->win, 
        get_data()->gun.img[get_data()->gun.current_frame], 
        gun_pos_x, gun_pos_y);
}

int loop_hook(t_game *game)
{
    // Update player position based on key presses
    // if (game->player.walk_direction != 0)
    // {
    //     game->player.pos_x += game->player.walk_direction * game->player.move_speed * sin(game->player.rotation_angle);
    //     game->player.pos_y += game->player.walk_direction * game->player.move_speed * cos(game->player.rotation_angle);
    // }
    // if (game->player.turn_direction != 0)
    // {
    //     game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
    // }

		// game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
		// double move_step = game->player.walk_direction * game->player.move_speed;
		// double new_player_x = game->player.pos_x + sin(game->player.rotation_angle) * move_step;
		// double new_player_y = game->player.pos_y + cos(game->player.rotation_angle) * move_step;
		// if (has_wall_at(game, new_player_x, new_player_y) != 1)
		// {
		// 	game->player.pos_x = new_player_x;
		// 	game->player.pos_y = new_player_y;
		// 	// printf("%snew_player_x = %.2f, new_player_y = %.2f\n%s",CRED,  new_player_x, new_player_y, CRESET);
		// }
		// cast_all_rays(game);

	// render_rays(game);
	if (get_data()->is_updated)
	{
		init_background();
		render_walls();
		// Render the frame
		// render_player(game);
		render_minimap();
		render_background();
		render_gun();
		// draw_player();
		// mlx_put_image_to_window(get_data()->mlx, get_data()->win, get_data()->minimap.img_data.img, 0, 0);
		// get_data()->is_updated = 0;
	}

    return (0);
}
// cast all rays
// table of rays
// render the rays


int main(int ac, char **av)
{
    int fd;
    t_game game;

    if (ac != 2 || check_file(av[1], &fd) == 0)
        return (printf("Error\nUsage: ./Cube3d map.cub\n"), 0);
    game = check_map(fd, av[1]);
    close(fd);
    printf("width = %d\n", game.map.width * 32);
    printf("height = %d\n", game.map.height * 32);
    // game.mlx = mlx_init();
    // game.win = mlx_new_window(game.mlx, game.map.width * SQUARE_SIZE, game.map.height * SQUARE_SIZE, "cube3d");
    // game.img.img = mlx_new_image(get_data()->mlx, game.map.width * SQUARE_SIZE, game.map.height * SQUARE_SIZE);
    // game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);

    // game.player.radius = 3;
    // game.player.pos_x = game.map.height / 2;
    // game.player.pos_y = game.map.width / 2;
    // game.player.move_speed = MOVE_SPEED;
    // game.player.rotation_speed = ROTATION_SPEED;
    // game.player.turn_direction = 0;
    // game.player.walk_direction = 0;
	// game.win_width = game.map.width * SQUARE_SIZE;
	// game.win_height= game.map.height * SQUARE_SIZE;
	// game.num_rays = game.win_width / WALL_STRIP_WIDTH;
	// printf("num_rays = %d\n", game.num_rays);
	// render_background(&game);
	// cast_all_rays(&game);
    // mlx_hook(game.win, 2, 1L << 0, key_press, &game); // Register key press hook
    // mlx_hook(game.win, 3, 1L << 1, key_release, &game); // Register key release hook
    // mlx_loop_hook(game.mlx, loop_hook, &game);

    // mlx_loop_hook(game.mlx, loop_hook, &game);
	
	init_data(game);
	init_background();
	render_walls();
	render_background();
	load_frames();
	// get_data()->minimap.img_data.img = mlx_new_image(get_data()->mlx, get_data()->width * SQUARE_SIZE, get_data()->height * SQUARE_SIZE);
    // get_data()->minimap.img_data.addr = mlx_get_data_addr(get_data()->minimap.img_data.img, &get_data()->minimap.img_data.bits_per_pixel, &get_data()->minimap.img_data.line_length, &get_data()->minimap.img_data.endian);
	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);

    mlx_loop(get_data()->mlx);

    return (0);
}