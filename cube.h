/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/28 11:49:22 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "garbage_collector/heap_controller.h"
#include "lib/get_next_line.h"
#include "lib/libft/libft.h"
#include "mlx-linux/mlx.h"


#define WIN_HEIGHT 720
#define WIN_WIDTH 1280
#define MY_PI 3.14159265358979323846
#define FOV (60 * (MY_PI / 180))
#define GRID_DIST 80
#define ZOOM 100

#define SQUARE_SIZE 16
#define PI 3.14159265359
#define ROTATION_SPEED 0.2
#define MOVE_SPEED 0.05
#define WALL_STRIP_WIDTH 100
#define FOV_ANGLE 60 * (PI / 180)
//=== buttons ====
#define TAB 65289
#define CTRL 65507
#define ESC 65307
#define Q 113
#define W 119
#define A 97
#define S 115
#define Z 122
#define X 120
#define E 101
#define R 114
#define D 100
#define F 102
#define C 99
#define V 118
#define F 102
#define R 114
#define UP_ARROW 65362
#define DOWN_ARROW 65364
#define RIGHT_ARROW 65363
#define LEFT_ARROW 65361
#define SPACE 32
#define ENTER 65293
#define DELETE 65288

//====== mlx img struct =====

typedef struct s_img_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
} t_img_data;

//======== colors =========

#define WHITE 0xffffff
#define BLACK 0x000000
#define DARK_BLUE 0x0E1721
#define BLUE 0x0000ff
#define RED 0xff0000
#define GREEN 0x009900
#define BROWN 0xCC6600
#define CYAN 0x00ffff
//-- manipulating colors --

#define CREATE_TRGB(t, r, g, b) (t << 24 | r << 16 | g << 8 | b)
#define GET_T(trgb) ((trgb >> 24) & 0xFF)
#define GET_R(trgb) ((trgb >> 16) & 0xFF)
#define GET_G(trgb) ((trgb >> 8) & 0xFF)
#define GET_B(trgb) (trgb & 0xFF)
//=== keys

#define W_MAC 13
#define A_MAC 0
#define S_MAC 1
#define D_MAC 2
#define ESC_MAC 53
#define LEFT_MAC 123
#define RIGHT_MAC 124
#define UP_MAC 126
#define DOWN_MAC 125
#define SPACE_MAC 49
#define E_MAC 14
#define T_MAC 17
#define Y_MAC 16
#define Z_MAC 6
#define F_MAC 3
#define CNTRL_MAC 256
#define SHIFT_MAC 257
#define TAB_MAC 48
#define N_MAC 45

#define LIN_1 49
#define LIN_2 50
#define LIN_3 51
#define LIN_4 52
#define W_LIN 119
#define A_LIN 97
#define S_LIN 115
#define D_LIN 100
#define ESC_LIN 65307
#define LEFT_LIN 65361
#define RIGHT_LIN 65363
#define UP_LIN 65362
#define DOWN_LIN 65364
#define E_LIN 101
#define T_LIN 116
#define Y_LIN 121
#define Z_LIN 122
#define F_LIN 102
#define CNTRL_LIN 65507
#define TAB_LIN 65289
#define N_LIN 110
#define H_LIN 104
#define SHIFT_LIN 65505
#define SPACE_LIN 32

// ANSI escape codes for colors
#define CRESET "\033[0m"
#define CBLACK "\033[30m"   /* Black */
#define CRED "\033[31m"     /* Red */
#define CGREEN "\033[32m"   /* Green */
#define CYELLOW "\033[33m"  /* Yellow */
#define CBLUE "\033[34m"    /* Blue */
#define CMAGENTA "\033[35m" /* Magenta */
#define CCYAN "\033[36m"    /* Cyan */
#define CWHITE "\033[37m"   /* White */

//======================================

typedef struct s_gun
{
    void *reloading_frames[50];  // Array to store gun frame images
    void *shooting_frames[30];
    void *walking_frames[13];
    void *running_frames[23];
    void *scope_shooting_frames[19];
    void *first_scope_frames[15];
    void *last_scope_frames[5];
    void *shooting_scope_frames[6];

    int width;          // Width of gun image
    int height;         // Height of gun image
    int current_frame;  // Current frame being displayed
    int frame_delay;    // Delay counter for animation
    int is_shooting;
    int show_scope;
    int is_reloading;  // Flag for shooting animation
    int shooted;
    int is_showing_scope;
} t_gun;

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
    void *img[18];      // Array to store door frame images
    int width;          // Height of door image
    int height;         // Width of door image
    int current_frame;  // Current frame being displayed
    int frame_delay;    // Delay counter for animation
    int is_opening;     // Flag for opening animation
    int is_open;        // Flag to indicate if door is fully open
    int is_closing;     // Flag for closing animation
    int is_closed;      // Flag to indicate if door is fully closed
    int active_x;       // X coordinate of currently animating door
    int active_y;       // Y coordinate of currently animating door
} t_door;

//======================================

typedef struct s_color
{
    char *color;
    int r;
    int g;
    int b;
} t_color;

//======================================

typedef struct s_player
{
    int radius;
    float pos_x;         // double pos_x;
    float pos_y;         // double
    int turn_direction;  // -1 if left, +1 if right
    int walk_direction;  // -1 if back, +1 if front
    double rotation_angle;
    double move_speed;
    double rotation_speed;
} t_player;

//======================================

typedef struct s_map
{
    char **grid;
    int width;
    int height;
    int valid;
} t_map;

//======================================

typedef struct s_texture
{
    char *path;
    t_img_data img_data;
    int width;
    int height;
} t_texture;

//======================================

typedef struct s_ray
{
    double ray_angle;
    double wall_hit_x;
    double wall_hit_y;
    double distance;
    int was_hit_vertical;
    int is_ray_facing_up;
    int is_ray_facing_down;
    int is_ray_facing_left;
    int is_ray_facing_right;
    int wall_hit_content;
} t_ray;

//======================================

typedef struct s_game
{
    void *mlx;
    void *win;
    t_img_data img;

    t_texture north;
    int win_width;
    int win_height;
    int num_rays;
    t_texture south;
    double ray_angle;
    t_texture west;
    t_texture east;
    t_ray *rays;
    t_color floor;
    t_color ceiling;
    t_map map;
    t_player player;
} t_game;

//==== vector struct ========
typedef struct s_vector
{
    int button;
    int pressed;
    float x;
    float y;
} t_vector;

//======== casted ray data =================
typedef struct s_ray_data
{
    t_vector ray_dir;
    t_vector delta_dist;
    t_vector side_dist;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    int side;
    float angle;
    float dist;
    float wall_height;
    int object_hitted;  // wall 0     &     close door 1      &     open door 2
    // struct s_ray_data   *will_render_above;// list of thing that will render
    // above each other (example: door will render above another door that will
    // render above a wall)
} t_ray_data;


//= Sprites structure============================
typedef struct s_sprite
{
    t_vector    position;
    t_texture   texture;
    t_texture   *frames;
    float       z;
    float dist;
    int display_start_x;
    int display_start_y;
    int display_end_x;
    int display_end_y;
}   t_sprite;

//==== data =================
typedef struct s_data
{
    void *mlx;
    void *win;
    // t_img_data	walls;
    int move_forward;
    int move_backward;
    int move_left;
    int move_right;
    int rotate_left;
    int rotate_right;
    int show_scope;
    int is_tab_pressed;
    int is_sound_playing;
    t_texture north_img;
    t_texture south_img;
    t_texture east_img;
    int speed;
    t_texture west_img;
    t_texture door_img;
    t_texture door_open_img;
    t_texture door_animating_img;

    t_img_data scope;
    t_img_data background_img;
    int ceiling_color;
    int floor_color;
    char **map;
    int height;
    int width;
    float player_angle;  //
    int player_is_moving;
    t_vector player_pos;
    int is_control_pressed;
    t_vector player_dir;
    t_vector mouse_pos;
    t_texture minimap;
    int is_walking;
    int is_running;
    int is_updated;
    int dark_mode;
    t_ray_data front_ray;
    t_gun gun;
    t_gun gun2;
    t_gun gun3;
    int screen_shake_intensity;
    int screen_shake_timer;
    int show_tab;
    int gun_id;
    t_door door;
    float gun_offset_x;
    float zoom_factor;
    t_sprite    *sprites;
    int        num_sprites;
} t_data;

//= Enemie structure============================

// typedef struct s_enemy
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
//     char    type;// type of the cube '0' for air | '1' for wall | 'D' for closed door | 'O' for opend DOor
// } t_map_grid;



//=================================
t_data *get_data(void);

//=== parsing ===========================================

// split by charset

char **ft_split2(char const *s, char *charset);
int check_charset(char *charset, char c);
t_game check_map(int fd, char *file);
int check_file(char *str, int *fd);
int check_if_player_direction(char c);
void render_tab();
void render_transparent_frame(void *frame_img, int width, int height);
void play_sound(const char *file);

//=======================================================
//=== rendering =========================================

void put_pixel(t_img_data *img, int x, int y, int color);
unsigned int pull_pixel(t_texture img, int x, int y);
void init_background(void);
void render_background(void);
void start_walk_sound();
int handle_keys(int keycode, void *garbage);
int ft_close(void);
int mouse_event(int x, int y, void *par);
void    line_between_2points(t_vector point1, t_vector point2, int color);
float   ft_max(float nbr1, float nbr2);
float   ft_min(float nbr1, float nbr2);
void    init_sprites(t_game *game);
double  ft_abs(double nbr);
void    update_door_animation(void);
void    open_door(void);
void    close_door(void);
int     calc_dist(int x, int y, t_vector point);
float   calc_dist_f(float x, float y, t_vector point);
float   dot_product(t_vector v1, t_vector v2);
float   vector_magnitude(t_vector vector);
// t_vector normalise_vector(t_vector vector);
void    rotate_player(float angle);
void    move_backward();
void    move_forward();
void    move_left();
void    move_right();
void    draw_player();
float   normalise_angle(float angle);
int     key_release(int keycode, void *garbage);
void update_movement();
void render_scope();
//

void render_walls(void);
void render_minimap(void);
//
t_ray_data  create_ray(float angle);
void	calculate_distance(t_ray_data *ray);
void	render_sprites(void);

//=== utils =============================================

void print_err(char *str);
void exiter(int code);
//=======================================================

#endif
