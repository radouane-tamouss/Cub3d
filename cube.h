/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/23 15:05:28 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// clang-format off
#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "garbage_collector/heap_controller.h"	//=== garbage collector
# include "lib/get_next_line.h"
# include "lib/libft/libft.h"
# include "mlx-linux/mlx.h"

//== const sizes =========

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define MY_PI 3.14159265358979323846
# define FOV (60 * (MY_PI / 180))
# define GRID_DIST 80
# define ZOOM 100
# define ENEMY_SPEED 0.2
# define SQUARE_SIZE 16
// # define MINIMAP_CENTER (SQUARE_SIZE * 5)

//=== buttons ====
# define TAB 65289
# define CTRL 65507
# define ESC 65307
# define Q 113
# define W 119
# define A 97
# define S 115
# define Z 122
# define X 120
# define E 101
# define R 114
# define D 100
# define F 102
# define C 99
# define V 118
# define F 102
# define R 114
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361
# define SPACE 32
# define ENTER 65293
# define DELETE 65288

//====== mlx img struct =====

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img_data;

//======== colors =========

# define WHITE 0xffffff
# define BLACK 0x000000
# define DARK_BLUE 0x0E1721
# define BLUE 0x0000ff
# define RED 0xff0000
# define GREEN 0x009900
# define BROWN 0xCC6600
# define CYAN 0x00ffff
//-- manipulating colors --
unsigned int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b);
unsigned char	get_t(unsigned int trgb);
unsigned char	get_r(unsigned int trgb);
unsigned char	get_g(unsigned int trgb);
unsigned char	get_b(unsigned int trgb);
// # define create_trgb(t, r, g, b) (t << 24 | r << 16 | g << 8 | b)
// # define get_t(trgb) ((trgb >> 24) & 0xFF)
// # define get_r(trgb) ((trgb >> 16) & 0xFF)
// # define get_g(trgb) ((trgb >> 8) & 0xFF)
// # define get_b(trgb) (trgb & 0xFF)
//=== keys
//
# define W_MAC	13
# define A_MAC	0
# define S_MAC	1
# define D_MAC 2
# define ESC_MAC 53
# define LEFT_MAC 123
# define RIGHT_MAC 124
# define UP_MAC 126
# define DOWN_MAC 125
# define SPACE_MAC 49
# define E_MAC 14
# define T_MAC 17
# define Y_MAC 16
# define Z_MAC 6
# define F_MAC 3
# define CNTRL_MAC 256
# define SHIFT_MAC 257
# define TAB_MAC 48
# define N_MAC 45

# define LIN_1 49
# define LIN_2 50
# define LIN_3 51
# define LIN_4 52
# define W_LIN 119
# define A_LIN 97
# define S_LIN 115
# define D_LIN 100
# define ESC_LIN 65307
# define LEFT_LIN 65361
# define RIGHT_LIN 65363
# define UP_LIN 65362
# define DOWN_LIN 65364
# define E_LIN 101
# define T_LIN 116
# define Y_LIN 121
# define Z_LIN 122
# define F_LIN 102
# define CNTRL_LIN 65507
# define TAB_LIN 65289
# define N_LIN 110
# define H_LIN 104
# define SHIFT_LIN 65505
# define SPACE_LIN 32

// ANSI escape codes for colors
# define CRESET "\033[0m"
# define CBLACK "\033[30m"	/* Black */
# define CRED "\033[31m"		/* Red */
# define CGREEN "\033[32m"	/* Green */
# define CYELLOW "\033[33m"	/* Yellow */
# define CBLUE "\033[34m"	/* Blue */
# define CMAGENTA "\033[35m" /* Magenta */
# define CCYAN "\033[36m"	/* Cyan */
# define CWHITE "\033[37m"	/* White */

//======================================


typedef struct s_gun
{
	void	*reloading_frames[50]; // Array to store gun frame images
	void	*shooting_frames[30];
	void	*walking_frames[13];
	void	*running_frames[23];
	void	*scope_shooting_frames[19];
	void	*first_scope_frames[15];
	void	*last_scope_frames[5];
	void	*shooting_scope_frames[6];

	int		width;// Width of gun image
	int		height;// Height of gun image
	int		current_frame; // Current frame being displayed
	int		frame_delay;// Delay counter for animation
	int		is_shooting;
	int		show_scope;
	int		is_reloading;// Flag for shooting animation
	int		shooted;
	int		is_showing_scope;
}			t_gun;

//======================================

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

typedef struct s_door
{
	void	*img[18];
	int		width;
	int		height;
	int		current_frame;
	int		frame_delay;
	int		is_opening;
	int		is_open;
	int		is_closing;
	int		is_closed;
	int		active_x;
	int		active_y;
}	t_door;

//======================================

typedef struct s_color
{
	char	*color;
	int		r;
	int		g;
	int		b;
}			t_color;

//======================================

typedef struct s_player
{
	int		radius;
	float	pos_x;
	float	pos_y;
	int		turn_direction;
	int		walk_direction; // -1 if back, +1 if front
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}			t_player;

//======================================

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		valid;
}			t_map;

//======================================

typedef struct s_texture
{
	char		*path;
	t_img_data	img_data;
	int			width;
	int			height;
}				t_texture;

//======================================

typedef struct s_ray
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}			t_ray;

//======================================

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img_data	img;

	t_texture	north;
	int			win_width;
	int			win_height;
	int			num_rays;
	t_texture	south;
	double		ray_angle;
	t_texture	west;
	t_texture	east;
	t_ray		*rays;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_player	player;
}				t_game;

//==== vector struct ========
typedef struct s_vector
{
    float x;
    float y;
} t_vector;
//==== square box collider ==================================
// typedef struct s_square
// {
//     t_vector    points[4];
// }   t_square;


//======== casted ray data =================
typedef struct s_ray_data
{
	t_vector	ray_dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	float		angle;
	float		dist;
	float		wall_height;
	int			object_hitted; // wall 0  & close door 1 & open door 2
	// struct s_ray_data   *will_render_above;// list of thing that will render
	// above each other (example: door will render above another door that will
	// render above a wall)
}				t_ray_data;

//= Sprites structure============================
typedef struct s_sprite
{
	int			is_dead;
	int			is_dying;
	t_vector	position;
	t_texture	texture;
	float		z;
	float		dist;
	int			display_start_x;
	int			display_start_y;
	int			display_end_x;
	int			display_end_y;
	int			current_frame; // Current frame being displayed
	int			current_dying_frame;
	int			frame_delay; // Delay counter for animation
}				t_sprite;

//==== data =================
typedef struct s_data
{
	t_texture	sprites_frames[19];// Array to store gun frame images
	t_texture	dying_frames[15];// Array to store gun frame images
	t_texture	die_texture;
	void		*mlx;
	void		*win;
	// t_img_data	walls;
	int			move_forward;
	int			move_backward;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
	int			show_scope;
	int			is_tab_pressed;
	int			is_sound_playing;
	t_texture	north_img;
	t_texture	south_img;
	t_texture	east_img;
	int			speed;
	t_texture	west_img;
	t_texture	door_img;
	t_texture	door_open_img;
	t_texture	door_animating_img;

	t_img_data	scope;
	t_img_data	background_img;
	int			ceiling_color;
	int			floor_color;
	char		**map;
	int			height;
	int			width;
	float		player_angle;//
	int			player_is_moving;
	t_vector	player_pos;
	int			is_control_pressed;
	t_vector	player_dir;
	t_vector	mouse_pos;
	t_texture	minimap;
	int			is_walking;
	int			is_running;
	int			is_updated;
	int			dark_mode;
	t_ray_data	front_ray;
	t_gun		gun;
	t_gun		gun2;
	t_gun		gun3;
	int			screen_shake_intensity;
	int			screen_shake_timer;
	int			show_tab;
	int			gun_id;
	t_door		door;
	float		gun_offset_x;

	float		zoom_factor;
	t_sprite	*sprites;
	t_sprite	die_sprite;
	int			num_sprites;
	t_img_data	enemie_on_map;
	int 		number_of_shoots;

}				t_data;

//= Enemie structure============================
// typedef struct s_enemie
// {
//     t_texture   texture;
//     t_vector    position;
//     int         health;
//     char    id;//TODO make a max of enemies
// }   t_enemy;
// //= map_grid data ==============================
// typedef struct s_map_grid
// {
//     t_enemy enemy;
//     char    type;// type of the cube '0' for air | '1' for wall | 'D' for
//     closed door | 'O' for opend DOor
// } t_map_grid;
//     t_vector    position;
//     int         health;
//     t_texture   texture;
// }   t_enemie;

//=================================
t_data			*get_data(void);

//=== parsing ===========================================
// clang-format off
t_game			init_game_struct(void);
char			**init_map(int fd, char *file, t_map *m2);
void			pad_map_with_spaces(t_game *game);
void			pad_map_with_spaces_helper(t_game *game, int j, int i,
					int map_width);
void			check_invalid_map_helper(t_game *game, int i, int j);
int				calc_map_width(char **map);
void			check_invalid_spaces(t_game *game);
void			check_invalid_map(t_game *game);
void			check_map_helper(char **map, t_game *game, t_map m2);
t_game			check_map(int fd, char *file);

int				has_wall_at(t_game *game, double x, double y);
int				calc_map_width(char **map);
void			get_player_position(t_game *game);
void			check_invalid_map(t_game *game);
void			check_invalid_map_helper(t_game *game, int i, int j);
int				check_if_player_direction(char c);
void			check_invalid_spaces(t_game *game);
void			check_invalid_spaces_helper(t_game *game, int i, int j);
void			verify_player_starting_position(t_game *game);
int				calc_map_width(char **map);
char			*ft_strtrim_last(char *s1, char *set);
int				calc_map_height(char **map);
void			check_map_sourrounded_by_walls(t_game *game);
void			check_door_left_and_right_should_be_wall(t_game *game);
void			check_if_map_contains_only_valid_characters(t_game *game);
int				check_if_file_empty(char *file);
void			parse_texture_and_colors_info(char *line, t_game *game,
					t_map *map);
void			validate_split(char **split);
void			check_floor_color(t_game *game, char **split);
void			check_ceiling_color(t_game *game, char **split);
void			parse_color(char *color, t_color *color_struct);
void			split_and_trime_whitespaces(char **rgb, char *color);
void			check_for_null_pointers(char *color, t_color *color_struct);
int				ft_isspace(char c);
void			count_commas_and_validate_basic_format(char *color,
					t_color *color_struct);
int				ft_count_commas(char *str);
int				check_file_extension(char *str);
void			parse_east_texture(t_game *game, char **split);
void			parse_west_texture(t_game *game, char **split);
void			parse_south_texture(t_game *game, char **split);
void			parse_north_texture(t_game *game, char **split);
void			check_file_exists_or_empty(char *file);
void			print_map(char **map);
void			fill_map(char **map, char *file, char *line);
void			fill_map_helper(int fd, char *line, char **map, int *i);
int				check_line_empty(char *line);
size_t			calc_height(int fd, char *file, t_map *m2, char *line);
int				check_file(char *str, int *fd);
int				ft_strcmp(const char *s1, const char *s2);

void			calc_num_sprites(t_game *game);
void			init_sprites_helper(t_game *game, int i, int j, int n);
void			init_sprites(t_game *game);
// split by charset

void			update_enemy_frames(void);
int				should_render(t_sprite *sprite, float *angle);
char			**ft_split2(char const *s, char *charset);
int				check_charset(char *charset, char c);
t_game			check_map(int fd, char *file);
int				check_file(char *str, int *fd);
int				check_if_player_direction(char c);
void			render_tab(void);
void			render_transparent_frame(void *frame_img, int width,
			int height);
void			play_sound(const char *file);

int				handle_mouse_event(int button, int x, int y, void *param);
//=======================================================
//=== rendering =========================================
int				ray_hit_sprite(t_ray_data ray, t_sprite sprite);

void			load_dying_sprite_frames(void);
void			load_load_sprite_frames(void);
void			put_pixel(t_img_data *img, int x, int y, int color);
unsigned int	pull_pixel(t_texture img, int x, int y);
void			init_background(void);
void			render_background(void);
void			start_walk_sound(void);
int				handle_keys(int keycode, void *garbage);
int				ft_close(void);
int				mouse_event(int x, int y, void *par);
void			line_between_2points(t_vector point1, t_vector point2,
			int color);
float			ft_max(float nbr1, float nbr2);
float			ft_min(float nbr1, float nbr2);
void			init_sprites(t_game *game);
double			ft_abs(double nbr);
void	render_cyrcle(int x, int y, int radius, int color);
void			update_door_animation(void);
void			open_door(void);
void			close_door(void);
int				calc_dist(int x, int y, t_vector point);
float			calc_dist_f(float x, float y, t_vector point);
float			dot_product(t_vector v1, t_vector v2);
float			vector_magnitude(t_vector vector);
// t_vector	normalise_vector(t_vector vector);
void			rotate_player(float angle);

void			animate_sprites(void);
void			move_backward(void);
void			move_forward(void);
void			move_left(void);
void			move_right(void);
void			draw_player(void);
float			normalise_angle(float angle);
int				key_release(int keycode, void *garbage);
void			update_movement(void);
void			render_scope(void);
//
t_ray_data		create_ray(float angle);
void			calculate_ray_distance(t_ray_data *ray);

//
int	calc_color(t_ray_data ray, int start, int i, int end);
void render_walls(void);
void render_minimap(void);
//
t_ray_data create_ray(float angle);
void render_sprites(void);
void	next_step_square(t_vector *next_step_square, t_vector center, float square_lenght, t_vector dir);
void	render_square(int x, int y, int color);
void	render_line(float x1, float y1, float x2, float y2);
//=== utils =============================================

void			print_err(char *str);
void			exiter(int code);
//=======================================================

#endif
