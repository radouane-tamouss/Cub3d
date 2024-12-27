/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:26:16 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/27 01:47:25 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	init_dest_src_y_data(int **dest_data, int **src_data, t_img_data *dest,
		t_img_data *src)
{
	int	y;

	y = -1;
	*dest_data = (int *)dest->addr;
	*src_data = (int *)src->addr;
	return (y);
}

void	put_xpm_image(t_img_data *dest, t_img_data *src, int start_x,
		int start_y)
{
	int	y;
	int	x;
	int	src_pixel;
	int	*dest_data;
	int	*src_data;

	if (!dest || !src || !dest->addr || !src->addr)
		return ;
	y = init_dest_src_y_data(&dest_data, &src_data, dest, src);
	while (++y < src->height)
	{
		if ((start_y + y) < 0 || (start_y + y) >= WIN_HEIGHT)
			continue ;
		x = -1;
		while (++x < src->width)
		{
			if ((start_x + x) < 0 || (start_x + x) >= WIN_WIDTH)
				continue ;
			src_pixel = src_data[y * (dest->line_length / 4) + x];
			if ((src_pixel & 0x00FFFFFF) == 0)
				continue ;
			dest_data[(start_y + y) * (src->line_length / 4)
				+ (start_x + x)] = src_pixel;
		}
	}
}

void	render_transparent_frame(void *frame_img, int width, int height)
{
	t_img_data	current_frame;
	int			pos_x;
	int			pos_y;

	if (!frame_img)
	{
		printf("frame_img is null\n");
		return ;
	}
	current_frame.img = frame_img;
	current_frame.width = width;
	current_frame.height = height;
	current_frame.addr = safer_get_data_addr(current_frame.img,
			&current_frame.bits_per_pixel, &current_frame.line_length,
			&current_frame.endian);
	pos_x = (WIN_WIDTH / 2 - width / 2);
	pos_y = WIN_HEIGHT - height + 4;
	put_xpm_image(&get_data()->background_img, &current_frame, pos_x, pos_y);
}
