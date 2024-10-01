/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:22 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/29 16:50:23 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

//color a pixel in img in the cords (x, y)
void	put_pixel(t_img_data *img, int x, int y, int color)
{
	char			*dst;
	int				offset;
	unsigned int	*ptr;

	if (y >= WIN_HEIGHT || x >= WIN_WIDTH || x < 0 || y < 0 )
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	ptr = (unsigned int *)dst;
	*ptr = color;
}
