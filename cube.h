/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/04 16:47:54 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include "lib/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include "lib/get_next_line.h"
# include <math.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>

//== const sizes =========

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define MY_PI 3.14159265358979323846
# define FOV (60 * (MY_PI / 180))
# define GRID_DIST 32
# define ZOOM 350
# define SPEED 4


# define SQUARE_SIZE 64 
# define PI 3.14159265359
#define ROTATION_SPEED 0.1
#define MOVE_SPEED 0.1
#define WALL_STRIP_WIDTH 100 
#define FOV_ANGLE 60 * (PI / 180)
//=== buttons ====
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
}				t_img_data;


//======== colors =========

# define WHITE 0xffffff
# define BLACK 0x000000
# define BLUE  0x0000ff
# define RED   0xff0000
# define GREEN 0x009900
# define BROWN 0xCC6600
# define CYAN  0x00ffff
//-- manipulating colors --

# define CREATE_TRGB(t, r, g, b) (t << 24 | r << 16 | g << 8 | b)
# define GET_T(trgb) ((trgb >> 24) & 0xFF)
# define GET_R(trgb) ((trgb >> 16) & 0xFF)
# define GET_G(trgb) ((trgb >> 8) & 0xFF)
# define GET_B(trgb) (trgb & 0xFF)
//=== keys

# define W_MAC 13
# define A_MAC 0
# define S_MAC 1
# define D_MAC 2
# define ESC_MAC 53
# define LEFT_MAC 123
# define RIGHT_MAC 124
# define UP_MAC 126
# define DOWN_MAC 125
# define E_MAC 14

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

// ANSI escape codes for colors
#define CRESET   "\033[0m"
#define CBLACK   "\033[30m"      /* Black */
#define CRED     "\033[31m"      /* Red */
#define CGREEN   "\033[32m"      /* Green */
#define CYELLOW  "\033[33m"      /* Yellow */
#define CBLUE    "\033[34m"      /* Blue */
#define CMAGENTA "\033[35m"      /* Magenta */
#define CCYAN    "\033[36m"      /* Cyan */
#define CWHITE   "\033[37m"      /* White */


typedef struct s_color
{
    char *color;
    int r;
    int g;
    int b;
} t_color;

typedef struct s_texture
{
    char *path;
    void *img;
    int width;
    int height;
} t_texture;

typedef struct s_player
{
    int radius;
    float pos_x;// double pos_x;
    float pos_y;// double 
    int turn_direction; // -1 if left, +1 if right
    int walk_direction; // -1 if back, +1 if front
    double rotation_angle;
    double move_speed;
    double rotation_speed;
} t_player;

typedef struct s_map
{
    char **grid;
    int width;
    int height;
    int valid;
} t_map;

typedef struct s_image_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image_data;

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

typedef struct s_game
{
    void *mlx;
    void *win;
    t_image_data img;

    
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
	float	x;
	float	y;
}	t_vector;


//======== casted ray data =================
typedef struct s_ray_data {
    t_vector ray_dir;
    t_vector delta_dist;
    t_vector side_dist;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    int side;
} t_ray_data;
//==== data =================

typedef struct s_data
{
	void		*mlx;
	void		*win;
	// t_img_data	walls;
	t_img_data	north_img;
	t_img_data	south_img;
	t_img_data	east_img;
	t_img_data	west_img;
	t_img_data	background_img;
	int			ceiling_color;
	int			floor_color;
	char		**map;
	int			height;
	int			width;
	float		player_angle;//
	t_vector	player_pos;
	t_vector	player_dir;
	t_vector	mouse_pos;
	//TODO comlete this
} t_data;


//==== struct of HEAP CONTROLLER ==

typedef struct	s_heap
{
	void	*ptr;
	struct s_heap	*next;
} t_heap;

//=================================
t_data	*get_data(void);

//=== parsing ===========================================

// split by charset

char	**ft_split2(char const *s, char *charset);
int	check_charset(char *charset, char c);

//=======================================================
//=== rendering =========================================

void	put_pixel(t_img_data *img, int x, int y, int color);
void	init_background(void);
void	render_background(void);
int		handle_keys(int keycode, void *garbage);
int		ft_close(void);
int mouse_event(int x, int y, void *par);
void	line_between_2points(t_vector point1,
				t_vector point2, int color);
float	ft_max(float nbr1, float nbr2);
float	ft_min(float nbr1, float nbr2);
double	ft_abs(double nbr);
int	calc_dist(int x, int y, t_vector point);
void	rotate_player(float angle);
void	move_backward();
void	move_forward();
void	move_left();
void	move_right();
void	draw_player();
float	normalise_angle(float angle);
//

void	render_walls(void);
//=== garbage collector =================================

void	*mallocate(size_t size);
void	free_all_heap(void);
void	ft_free(void *ptr);
//=== utils =============================================

void print_err(char *str);
void	exiter(int code);
//=======================================================

#endif