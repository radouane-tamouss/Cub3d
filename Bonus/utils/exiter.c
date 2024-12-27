/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:02:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/26 02:37:10 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// as its name says, you give it array of images and its size the function will
// destroy all of them as long they're not NULL
static void	multiple_images_destroyer(void **images, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (images == NULL)
		return ;
	while (i < size)
	{
		if (images[i] != NULL)
			mlx_destroy_image(get_data()->mlx, images[i]);
		++i;
	}
}

static void	multiple_textures_destroyer(t_texture *textures, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (textures == NULL)
		return ;
	while (i < size)
	{
		if (textures[i].img_data.img != NULL)
			mlx_destroy_image(get_data()->mlx, textures[i].img_data.img);
		++i;
	}
}

static	void	destroy_remaining_images(void)
{
	int	i;

	i = 0;
	while (i < get_data()->num_sprites)
	{
		if (get_data()->sprites[i].texture.img_data.img != NULL)
			mlx_destroy_image(get_data()->mlx,
				get_data()->sprites[i].texture.img_data.img);
		++i;
	}
	if (get_data()->north_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->north_img.img_data.img);
	if (get_data()->south_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->south_img.img_data.img);
	if (get_data()->east_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->east_img.img_data.img);
	if (get_data()->west_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->west_img.img_data.img);
	if (get_data()->door_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->door_img.img_data.img);
	if (get_data()->door_open_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx,
			get_data()->door_open_img.img_data.img);
	if (get_data()->background_img.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->background_img.img);
}

// this will act as clean exiter , that free and remove leaks before exiting
void	exiter(int code)
{
	if (get_data()->mlx != NULL)
	{
		multiple_images_destroyer(get_data()->gun.shooting_frames, 15);
		multiple_images_destroyer(get_data()->gun.running_frames, 11);
		multiple_images_destroyer(get_data()->gun.reloading_frames, 12);
		multiple_images_destroyer(get_data()->gun.first_scope_frames, 6);
		multiple_images_destroyer(get_data()->gun.last_scope_frames, 5);
		multiple_images_destroyer(get_data()->gun.scope_shooting_frames, 6);
		multiple_textures_destroyer(get_data()->dying_frames, 15);
		multiple_textures_destroyer(get_data()->sprites_frames, 16);
		multiple_textures_destroyer(get_data()->door.images, 17);
		multiple_images_destroyer(get_data()->gun.walking_frames, 11);
		destroy_remaining_images();
		mlx_destroy_display(get_data()->mlx);
		free(get_data()->mlx);
	}
	free_all_heap();
	exit(code);
}
