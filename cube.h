/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/17 23:40:42 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>

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

//===========================
//==== data =================

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img_data	walls;
	t_img_data	north_img;
	t_img_data	south_img;
	t_img_data	east_img;
	t_img_data	west_img;
	t_img_data	background_img;
	int			ceiling_color;
	int			floor_color;
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
void	create_background(void);
void	render_background(void);

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