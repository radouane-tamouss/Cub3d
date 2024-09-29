/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rtamouss <rtamouss@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 20:55:34 by eouhrich      #+#    #+#                 */
/*   Updated: 2024/09/29 18:41:48 by rtamouss      ########   odam.nl         */
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
// # include <mlx.h>

//== const sizes =========

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000

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
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_map
{
    char **grid;
    int width;
    int height;
    int valid;
} t_map;

typedef struct s_game
{
    void *mlx;
    void *win;
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