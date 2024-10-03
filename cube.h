/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/03 11:39:51 rtamouss         ###   ########.fr       */
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

//== const sizes =========

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000


# define SQUARE_SIZE 64 
# define PI 3.14159265359
#define ROTATION_SPEED 0.1
#define MOVE_SPEED 0.1

//===========================
//====== mlx img struct ===== 

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

//=========================
//======== colors =========

# define WHITE 0xffffff
# define BLACK 0x000000
# define BLUE  0x0000ff
# define RED   0xff0000
# define GREEN 0x009900
# define BROWN 0xCC6600
# define CYAN  0x00ffff
// keys

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
    double pos_x;
    double pos_y;
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

typedef struct s_game
{
    void *mlx;
    void *win;
    t_image_data img;

    
    t_texture north;
    t_texture south;
    t_texture west;
    t_texture east;
    t_color floor;
    t_color ceiling;
    t_map map;
    t_player player;
} t_game;



//===========================
//==== data =================

// typedef struct s_data
// {
// 	void		*mlx;
// 	void		*win;
// 	t_img_data	img_data;
// 	int			ceiling_color;
// 	int			floor_color;
// 	//TODO comlete this
// } t_data;




//===========================
//==== struct of HEAP CONTROLLER ==

typedef struct	s_heap
{
	void	*ptr;
	struct s_heap	*next;
} t_heap;

//=================================

//=======================================================
//=== parsing ===========================================

// split by charset

char	**ft_split2(char const *s, char *charset);
int	check_charset(char *charset, char c);

//=======================================================
//=== rendering =========================================

//=======================================================
//=== garbage collector =================================

void	*mallocate(size_t size);
void	free_all_heap(void);
void	ft_free(void *ptr);
//=======================================================


#endif