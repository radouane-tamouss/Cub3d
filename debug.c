// else if (keycode == E_LIN)
//   {
//     if ((get_data()->front_ray.object_hitted == 1 || get_data()->front_ray.object_hitted == 2) && get_data()->front_ray.dist < 2 * GRID_DIST)
//     {
//         get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x] = 'D';
//         get_data()->door.x = get_data()->front_ray.map_x;
//         get_data()->door.y = get_data()->front_ray.map_y;
//         // get_data()->map[get_data()->front_ray.map_y][get_data()->front_ray.map_x] = 'O';
//         if (!get_data()->door.is_open && !get_data()->door.is_opening)
//         {
//             get_data()->door.is_opening = 1;
//             get_data()->door.current_frame = 0;
//             get_data()->door.frame_delay = 2;
//         }
//         else if (get_data()->door.is_open && !get_data()->door.is_closing)
//         {
//             get_data()->door.is_closing = 1;
//             get_data()->door.current_frame = 17;
//             get_data()->door.frame_delay = 0;
//         }

//       get_data()->is_updated = 1;
//     }
// }
// // =========================
// #include "../cube.h"
// // this init the direction (vector) of the ray
// void init_ray_dir(t_ray_data *ray, float ray_angle)
// {
//     ray->angle = ray_angle;
//     ray->ray_dir.x = cos(ray_angle);
//     ray->ray_dir.y = sin(ray_angle);
//     ray->map_x = (int)(get_data()->player_pos.x / GRID_DIST);
//     ray->map_y = (int)(get_data()->player_pos.y / GRID_DIST);
//     // ray->will_render_above = NULL;
// }
// // calc the delta that we need to travel to hit the intersact with the next line of grid
// void calc_delta_dist(t_ray_data *ray)
// {
//     ray->delta_dist.x = ft_abs(1 / ray->ray_dir.x);
//     ray->delta_dist.y = ft_abs(1 / ray->ray_dir.y);
// }
// //calc the distance need to travel from intersection to another x
// void calc_step_and_side_dist_x(t_ray_data *ray)
// {
//     float player_x;

//     player_x = get_data()->player_pos.x / GRID_DIST;

//     if (ray->ray_dir.x < 0)
//     {
//         ray->step_x = -1;
//         ray->side_dist.x = (player_x - ray->map_x) * ray->delta_dist.x;
//     }
//     else
//     {
//         ray->step_x = 1;
//         ray->side_dist.x = (ray->map_x + 1.0 - player_x) * ray->delta_dist.x;
//     }
// }
// //calc the distance need to travel from intersection to another y
// void calc_step_and_side_dist_y(t_ray_data *ray)
// {
//     float player_y;

//     player_y = get_data()->player_pos.y / GRID_DIST;
//     if (ray->ray_dir.y < 0)
//     {
//         ray->step_y = -1;
//         ray->side_dist.y = (player_y - ray->map_y) * ray->delta_dist.y;
//     }
//     else
//     {
//         ray->step_y = 1;
//         ray->side_dist.y = (ray->map_y + 1.0 - player_y) * ray->delta_dist.y;
//     }
// }
// void	calculate_distance(t_ray_data *ray)
// {
//     if (ray->side == 0)
//         ray->dist = (ray->side_dist.x - ray->delta_dist.x) * GRID_DIST;
//     else
//         ray->dist = (ray->side_dist.y - ray->delta_dist.y) * GRID_DIST;
//     // ray->dist *= cos(ray->angle - get_data()->player_angle);
// }

// void draw_col(t_ray_data ray, int col);

// void perform_dda(t_ray_data ray, int data_taken, int col)
// {
//     // int data_taken = 0;
//     while (1)
//     {
//         if (ray.side_dist.x < ray.side_dist.y)
//         {
//             ray.side_dist.x += ray.delta_dist.x;
//             ray.map_x += ray.step_x;
//             ray.side = 0;
//         }
//         else
//         {
//             ray.side_dist.y += ray.delta_dist.y;
//             ray.map_y += ray.step_y;
//             ray.side = 1;
//         }
        
//         char current_tile = get_data()->map[ray.map_y][ray.map_x];
        
//         if (current_tile == '1')
//         {
//             ray.object_hitted = 0; // hit a wall
//             if (!data_taken && ray.angle == get_data()->player_angle)
//             {
//                 get_data()->front_ray = ray;
//                 calculate_distance(&(get_data()->front_ray));
//                 data_taken = 1;
//             }
//             calculate_distance(&ray);
//             draw_col(ray, col);
//             return;
//         }
//         else if (current_tile == 'D') // Closed door
//         {
//             ray.object_hitted = 1; // hit a closed door
//             if (!data_taken && ray.angle == get_data()->player_angle)
//             {
//                 get_data()->front_ray = ray;
//                 calculate_distance(&(get_data()->front_ray));
//                 data_taken = 1;
//             }
//             perform_dda(ray, data_taken, col);///
//             calculate_distance(&ray);
//             draw_col(ray, col);
//             return;
//         }
//         else if (current_tile == 'O') // Open door - we'll use 'O' for open doors
//         {
//                 ray.object_hitted = 2; // hit an open door
//             if (!data_taken && ray.angle == get_data()->player_angle)
//             {
//                 get_data()->front_ray = ray;
//                 calculate_distance(&(get_data()->front_ray));
//                 data_taken = 1;
//             }
//             perform_dda(ray, data_taken, col);///
//             calculate_distance(&ray);//
//             draw_col(ray, col);//
//             return;//
//             // Don't return, continue raycasting through open door
//         }
//     }
// }


// // casting the ray and grab all wanted data (coords of wall, side, ...)
// t_ray_data cast_ray(float ray_angle, int col)
// {
//     t_ray_data ray;


//     init_ray_dir(&ray, ray_angle);
//     calc_delta_dist(&ray);
//     calc_step_and_side_dist_x(&ray);
//     calc_step_and_side_dist_y(&ray);
//     perform_dda(ray, 0, col);
// 	// calculate_distance(&ray);//
//     return ray;
// }

// // this will calculate wich pixel should take from image buffer
// unsigned int get_right_pixel(float i, t_ray_data ray)
// {
//     int pixel_x;
//     float pixel_y;
//     float hit_point;
//     t_texture texture;

		
//     if (ray.side == 0) // if it hits on the vertical side
//     {
//         hit_point = get_data()->player_pos.y + (ray.dist * ray.ray_dir.y);
//         if (ray.object_hitted == 2)
//             texture = get_data()->door_open_img;
// 		else if (ray.object_hitted == 1)
// 			texture = get_data()->door_img;
// 		else if (ray.ray_dir.x > 0)
// 			texture = get_data()->east_img;
// 		else
// 			texture = get_data()->west_img;
//     }
//     else // else if it ray hit on horizontal side
//     {
//         hit_point = get_data()->player_pos.x + (ray.dist * ray.ray_dir.x);
//         if (ray.object_hitted == 2)
//             texture = get_data()->door_open_img;
// 		else if (ray.object_hitted == 1)
// 			texture = get_data()->door_img;
//         else if (ray.ray_dir.y > 0)
// 			texture = get_data()->north_img;
// 		else
// 			texture = get_data()->south_img;
//     }

//     pixel_x = (int)(hit_point * texture.width / GRID_DIST) % texture.width;
//     pixel_y = (int)((i - (WIN_HEIGHT / 2 - ray.wall_height / 2)) / ray.wall_height * texture.height) % texture.height;

//     return (pull_pixel(texture, pixel_x, (int)pixel_y));
// }




// void draw_col(t_ray_data ray, int col)
// {
// 	float wall_height;
// 	int start;
// 	int end;
// 	int i;
 
// 	ray.wall_height = (GRID_DIST / (ray.dist * cos(ray.angle - get_data()->player_angle))) * ((WIN_WIDTH / 2) / tan(FOV / 2));
// 	start = (WIN_HEIGHT - (int)ray.wall_height) / 2;
// 	end = start + (int)ray.wall_height;
// 	if (start < 0)
// 		start = 0;
// 	if (end > WIN_HEIGHT)
// 		end = WIN_HEIGHT;
// 	i = start;
// 	while (i < end)
// 	{
//         put_pixel(&(get_data()->background_img), col, i, calc_color(ray, start, i, end));
// 		i++;
// 	}
//     // if (ray.angle == get_data()->player_angle)
//         // printf("object --> %d  , dist -> %f, wall_height => %f ||| start %d - end %d\n", ray.object_hitted, ray.dist, ray.wall_height, start, end);
// }

// // will calc the angle of the ray then cast to the wall and calc the dist
// void render_col(int col)
// {
//     float ray_angle;
// 	t_ray_data	ray;
// 	int color;

// 	ray_angle = normalise_angle(get_data()->player_angle - (FOV/2) + (col * (FOV/WIN_WIDTH)));
//     cast_ray(ray_angle, col);
// }

// // this will draw the the walls on the background img (it will not put it to window)
// void	render_walls(void)
// {
// 	int i;

// 	i = 0;
//     render_background();
// 	while (i < WIN_WIDTH)
// 	{
// 		render_col(i++);// render each column of the window
// 	}
// }
// // ============
// void    load_door_frames(void)
// {
//     char *frame_paths[18] = {
//       "textures/door_frames/1.xpm",
//       ....
//     };

//     frame_paths[18] = NULL;
//     int     i;

//     i = 0;
//     while (i < 17)
//     {
//         get_data()->door.img[i] = mlx_xpm_file_to_image(get_data()->mlx, 
//             frame_paths[i], &get_data()->door.width, &get_data()->door.height);
//         if (!get_data()->door.img[i])
//         {
//             printf("%d ", i);
//             print_err("Failed to load door frame\n");
//             exiter(1);
//         }
//         i++;
//     }
//     get_data()->door.current_frame = 0;
//     get_data()->door.frame_delay = 0;
//     get_data()->door.is_opening = 0;
//     get_data()->door.is_open = 0;
//     get_data()->door.is_closed = 1;
// }

// void update_door_animation(void)
// {
//     if (get_data()->door.is_opening)
//     {
//         if (get_data()->door.frame_delay++ >= 0)  // Adjust delay value as needed
//         {
//             get_data()->door.frame_delay = 0;
//             get_data()->door.current_frame++;
//             if (get_data()->door.current_frame > 16)
//             {
//                 get_data()->door.current_frame = 16;  // Keep at last frame
//                 get_data()->door.is_opening = 0;
//                 get_data()->door.is_open = 1;
//                 get_data()->map[get_data()->door.y][get_data()->door.x] = 'O';
//                 // get_data()->front_ray.map_y]
                
//             }
            
//             // Update the door texture
//             get_data()->door_img.img_data.img = get_data()->door.img[get_data()->door.current_frame];
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
//         if (get_data()->door.frame_delay++ >= 0)  // Adjust delay value as needed
//         {
//             get_data()->door.frame_delay = 0;
//             get_data()->door.current_frame--;
            
//             if (get_data()->door.current_frame <= 0)
//             {
//                 get_data()->door.current_frame = 0;  // Keep at first frame
//                 get_data()->door.is_closing = 0;
//                 get_data()->door.is_open = 0;
//                 get_data()->door.is_closed = 1;
//                 get_data()->map[get_data()->door.y][get_data()->door.x] = 'D';
//             }
            
//             // Update the door texture
//             get_data()->door_img.img_data.img = get_data()->door.img[get_data()->door.current_frame];
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

// int loop_hook(t_game *game)
// {
//     if (get_data()->is_tab_pressed)
//     {
//         render_tab();
//         return (0);
//     }
// 	if (get_data()->is_updated)
// 	{
//         update_movement();
// 	    init_background();
// 	    render_walls();
// 	    render_minimap();
//         update_door_animation();
// 	    render_background();
// 	    // render_gun();
// 	}
//     return (0);
// }


// int main(int ac, char **av)
// {
//     int fd;
//     t_game game;

//     if (ac != 2 || check_file(av[1], &fd) == 0)
//         return (printf("Error\nUsage: ./Cube3d map.cub\n"), 0);
//     game = check_map(fd, av[1]);
//     close(fd);
// 	init_data(game);
// 	init_background();
// 	render_walls();
// 	render_minimap();
// 	render_background();
// 	load_frames();
//     load_first_gun_frames();
//     load_shooting_gun2_frames();
//     load_running_gun2_frames();
//     load_walking_gun2_frames();
//     load_door_frames();
// 	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);

//     mlx_loop(get_data()->mlx);

//     return (0);
// }

// // this will put backgrouind image to the window
// void	render_background(void)
// {
// 	mlx_put_image_to_window(get_data()->mlx,
// 		get_data()->win,
// 		get_data()->background_img.img, 0, 0);
// }

// //this will create the background img by putting colors of cieling and floor to it
// void	init_background()
// {
// 	int	x;
// 	int	y;
// 	int	color;

// 	y = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			if (y < (WIN_HEIGHT / 2))
// 			{
// 				color = get_data()->ceiling_color;
// 				// color = CREATE_TRGB(0,
// 					// (GET_R(color) - (int)(GET_R(color) * ((float)y / (float)(WIN_HEIGHT/2)))),
// 					// (GET_G(color) - (int)(GET_G(color) * ((float)y / (float)(WIN_HEIGHT/2)))),
// 					// (GET_B(color) - (int)(GET_B(color) * ((float)y / (float)(WIN_HEIGHT/2)))));
// 			}
// 			else
// 			{
// 				color = get_data()->floor_color;
// 				if (get_data()->dark_mode)
// 					color = CREATE_TRGB(0,
// 						((int)(GET_R(color) * ((float)(y - (WIN_HEIGHT/2)) / (float)(WIN_HEIGHT/2)))),
// 						((int)(GET_G(color) * ((float)(y - (WIN_HEIGHT/2)) / (float)(WIN_HEIGHT/2)))),
// 						((int)(GET_B(color) * ((float)(y - (WIN_HEIGHT/2)) / (float)(WIN_HEIGHT/2)))));
// 			}
// 			put_pixel(&(get_data()->background_img), x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }
// void check_invalid_map(t_game *game)
// {
// 	int i = 0;
// 	int j = 0;
// 	while (game->map.grid[i] != NULL)
// 	{
// 		j = 0;
// 		while (game->map.grid[i][j])
// 		{ 
// 			if (game->map.grid[i][j] == '0' || game->map.grid[i][j] == 'D' || game->map.grid[i][j] == 'O' || check_if_player_direction(game->map.grid[i][j]) == 1)
// 			{
// 				if ((i > 0 && (game->map.grid[i - 1][j] != '0' && game->map.grid[i - 1][j] != '1' && game->map.grid[i - 1][j] != 'D' && game->map.grid[i - 1][j] != 'O' && !check_if_player_direction(game->map.grid[i - 1][j]))) ||  // above
// 					(i < game->map.height - 1 && (game->map.grid[i + 1][j] != '0' && game->map.grid[i + 1][j] != '1' && game->map.grid[i + 1][j] != 'D' && game->map.grid[i + 1][j] != 'O' && !check_if_player_direction(game->map.grid[i + 1][j]))) ||  // below
// 					(j > 0 && (game->map.grid[i][j - 1] != '0' && game->map.grid[i][j - 1] != '1' && game->map.grid[i][j - 1] != 'D' && game->map.grid[i][j - 1] != 'O' && !check_if_player_direction(game->map.grid[i][j - 1]))) ||  // left
// 					(j < ft_strlen(game->map.grid[i]) - 1 && (game->map.grid[i][j + 1] != '0' && game->map.grid[i][j + 1] != '1' && game->map.grid[i][j + 1] != 'D' && game->map.grid[i][j + 1] != 'O' && !check_if_player_direction(game->map.grid[i][j + 1]))))  // right
// 				{
// 					if (check_if_player_direction(game->map.grid[i][j]) == 1)
// 						printf("invalid player direction at (%d, %d)\n", i, j);
// 					else if (game->map.grid[i][j] == 'D')
// 						printf("invalid door at (%d, %d)\n", i, j);
// 					else if (game->map.grid[i][j] == 'O')
// 						printf("invalid object at (%d, %d)\n", i, j);
// 					else 
// 						printf("invalid zero at (%d, %d)\n", i, j);

// 					exit(1);
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// typedef struct s_door {
//     void    *img[18];       // Array to store door frame images
//     int     width;          // Width of door image
//     int     height;         // Height of door image
//     int     current_frame;  // Current frame being displayed
//     int     frame_delay;    // Delay counter for animation
//     int     is_opening;     // Flag for opening animation
//     int     is_open;        // Flag to indicate if door is fully open
//     int     is_closing;     // Flag for closing animation
//     int    is_closed;      // Flag to indicate if door is fully closed
//     int    x;
//     int    y;
// } t_door;
// //======================================

// typedef struct s_color
// {
//     char *color;
//     int r;
//     int g;
//     int b;
// } t_color;
// //======================================


// typedef struct s_player
// {
//     int radius;
//     float pos_x;// double pos_x;
//     float pos_y;// double 
//     int turn_direction; // -1 if left, +1 if right
//     int walk_direction; // -1 if back, +1 if front
//     double rotation_angle;
//     double move_speed;
//     double rotation_speed;
// } t_player;
// //======================================

// typedef struct s_map
// {
//     char **grid;
//     int width;
//     int height;
//     int valid;
// } t_map;
// //======================================

// typedef struct s_texture
// {
//     char *path;
//     t_img_data img_data;
//     int width;
//     int height;
// } t_texture;
// //======================================

// typedef struct s_ray
// {
//     double ray_angle;
//     double wall_hit_x;
//     double wall_hit_y;
//     double distance;
//     int was_hit_vertical;
//     int is_ray_facing_up;
//     int is_ray_facing_down;
//     int is_ray_facing_left;
//     int is_ray_facing_right;
//     int wall_hit_content;
// } t_ray;
// //======================================

// typedef struct s_game
// {
//     void *mlx;
//     void *win;
//     t_img_data img;

    
//     t_texture north;
//     int win_width;
//     int win_height;
//     int num_rays;
//     t_texture south;
//     double ray_angle;
//     t_texture west;
//     t_texture east;
//     t_ray *rays;
//     t_color floor;
//     t_color ceiling;
//     t_map map;
//     t_player player;
// } t_game;



// //==== vector struct ========
// typedef struct s_vector
// {
// 	float	x;
// 	float	y;
// }	t_vector;


// //======== casted ray data =================
// typedef struct s_ray_data {
//     t_vector ray_dir;
//     t_vector delta_dist;
//     t_vector side_dist;
//     int map_x;
//     int map_y;
//     int step_x;
//     int step_y;
//     int side;
// 	float	angle;
// 	float	dist;
// 	float	wall_height;
// 	int		object_hitted;// wall 0     &     close door 1      &     open door 2
//     // struct s_ray_data   *will_render_above;// list of thing that will render above each other (example: door will render above another door that will render above a wall)
// } t_ray_data;
// //==== data =================

// typedef struct s_data
// {
// 	void		*mlx;
// 	void		*win;
// 	// t_img_data	walls;
//     int move_forward;
//     int move_backward;
//     int move_left;
//     int move_right;
//     int rotate_left;
//     int rotate_right;
//     int show_scope;
//     int is_tab_pressed;
// 	t_texture	north_img;
// 	t_texture	south_img;
// 	t_texture	east_img;
//     int speed;
// 	t_texture	west_img;
// 	t_texture	door_img;
//     t_texture   door_open_img;

//     t_img_data scope; 
// 	t_img_data	background_img;
// 	int			ceiling_color;
// 	int			floor_color;
// 	char		**map;
// 	int			height;
// 	int			width;
// 	float		player_angle;//
//     int player_is_moving;
// 	t_vector	player_pos;
//     int is_control_pressed;
// 	t_vector	player_dir;
// 	t_vector	mouse_pos;
// 	t_texture	minimap;
//     int is_walking;
//     int is_running;
// 	int			is_updated;
// 	int			dark_mode;
// 	t_ray_data		front_ray;
//     t_gun          gun;
//     t_gun         gun2;
//     int show_tab;
//     int gun_id;
//     t_door          door;

// } t_data;// =========================// =========================