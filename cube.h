/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/01 02:18:36 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>

//== const sizes =========

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define MY_PI 3.14159265358979323846
# define FOV (60 * (MY_PI / 180))
# define GRID_DIST 32 
# define ZOOM 200
# define SPEED 4

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

//=========================
//======== colors =========

# define WHITE 0xffffff
# define BLACK 0x000000
# define BLUE  0x0000ff
# define RED   0xff0000
# define GREEN 0x009900
# define BROWN 0xCC6600
# define CYAN  0x00ffff

//==== vector struct ========
typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;


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


//=== rendering =========================================

void	put_pixel(t_img_data *img, int x, int y, int color);
void	init_background(void);
void	render_background(void);
int		handle_keys(int keycode, void *garbage);
int		ft_close(void);
void	line_between_2points(t_vector point1,
				t_vector point2, int color);
float	ft_max(float nbr1, float nbr2);
float	ft_min(float nbr1, float nbr2);
int	ft_abs(int nbr);
int	calc_dist(int x, int y, t_vector point);
void	rotate_player(float angle);
void	move_backward();
void	move_forward();
void	move_left();
void	move_right();
void	draw_player();
//
void	render_walls(void);
//=== garbage collector =================================

void	*mallocate(size_t size);
void	free_all_heap(void);
void	ft_free(void *ptr);
//=== utils =============================================

size_t	ft_strlen(char *str);
void print_err(char *str);
void	exiter(int code);
//=======================================================

#endif