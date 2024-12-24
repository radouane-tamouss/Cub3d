/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:22 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/24 23:30:52 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// color a pixel in img in the cords (x, y)
void	put_pixel(t_img_data *img, int x, int y, int color)
{
	char			*dst;
	int				offset;
	unsigned int	*ptr;

	if (y >= WIN_HEIGHT || x >= WIN_WIDTH
		|| x < 0 || y < 0 || get_t(color) == 255)
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	ptr = (unsigned int *)dst;
	*ptr = color;
}

unsigned int	pull_pixel(t_texture img, int x, int y)
{
	int				offset;
	unsigned int	*ptr;
	char			*dst;

	if (y >= img.height || x >= img.width || x < 0 || y < 0)
		return (BLACK);
	offset = y * img.img_data.line_length
		+ x * (img.img_data.bits_per_pixel / 8);
	dst = img.img_data.addr + offset;
	ptr = (unsigned int *)dst;
	return (*ptr);
}

static void	choose_cube_texture(t_ray_data ray, t_texture *texture)
{
	if (ray.object_hitted == 'O')
		*texture = get_data()->door_open_img;
	else if (ray.object_hitted == 'D')
		*texture = get_data()->door_img;
	else if (ray.object_hitted == 'P')
	{
		*texture = get_data()->door.images[get_data()->door.current_frame];
		if (texture->width == 0)
	{
		fprintf(stderr, "get_data()->door.current_frame => %d\n", get_data()->door.current_frame);
		fprintf(stderr, "its zero, pointer => %p\n", texture->img_data.img);
		exit(1);
	}
	}
	else if (ray.side == 0 && ray.ray_dir.x > 0)
		*texture = get_data()->east_img;
	else if (ray.side == 0)
		*texture = get_data()->west_img;
	else if (ray.ray_dir.y > 0)
		*texture = get_data()->north_img;
	else
		*texture = get_data()->south_img;
}

// this will calculate wich pixel should take from image buffer
static unsigned int	get_right_pixel(float i, t_ray_data ray)
{
	int			pixel_x;
	float		pixel_y;
	float		hit_point;
	t_texture	texture;

	if (ray.side == 0)
		hit_point = get_data()->player_pos.y + (ray.dist * ray.ray_dir.y);
	else
		hit_point = get_data()->player_pos.x + (ray.dist * ray.ray_dir.x);
	choose_cube_texture(ray, &texture);
	// if (texture.width == 0)
	// {
	// 	fprintf(stderr, "its zero, pointer => %p\n", texture.img_data.addr);
	// 	exit(1);
	// }
	pixel_x = (int)(hit_point * texture.width / GRID_DIST) % texture.width;
	pixel_y = (int)((i - (WIN_HEIGHT / 2 - ray.wall_height / 2))
			/ ray.wall_height * texture.height) % texture.height;
	return (pull_pixel(texture, pixel_x, (int)pixel_y));
}

// this will find the texture
int	calc_color(t_ray_data ray, int start, int i, int end)
{
	int	projected_wall;
	int	color;

	projected_wall = end - start;
	color = get_right_pixel(i, ray);
	if (get_t(color) == 255)
		return (color);
	if (get_data()->dark_mode)
		color = create_trgb(0,
				(int)(get_r(color)
					* ((float)projected_wall / (float)WIN_HEIGHT)),
				(int)(get_g(color)
					* ((float)projected_wall / (float)WIN_HEIGHT)),
				((int)(get_b(color)
						* ((float)projected_wall / (float)WIN_HEIGHT))));
	return (color);
}
