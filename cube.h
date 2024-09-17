/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/17 21:03:40 by eouhrich         ###   ########.fr       */
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
# define BROWN 0xCC6600
# define RED 0xff0000
# define GREEN 0x009900
# define CYAN 0x00ffff
# define BLUE 0x0000ff

//===========================

#endif