/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:02:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/25 22:30:29 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// as its name says, you give it array of images and its size the function will
// destroy all of them as long they're not NULL
static void multiple_images_destroyer(void **images, unsigned int size)
{
	unsigned int i;

	i = 0;
	if (images == NULL) return;
	while (i < size)
	{
		if (images[i] != NULL) mlx_destroy_image(get_data()->mlx, images[i]);
		i++;
	}
}

// void free_texture(t_texture *texture)
// {
// 	if (texture && texture->img_data.img)
// 	{
// 		mlx_destroy_image(get_data()->mlx, texture->img_data.img);
// 		texture->img_data.img = NULL;
// 		texture->img_data.addr = NULL;
// 	}
// }
//
// this will act as clean exiter , that free and remove leaks before exiting
void exiter(int code)
{
	if (get_data()->mlx != NULL)
	{
		multiple_images_destroyer(get_data()->gun.shooting_frames, 15);
		multiple_images_destroyer(get_data()->gun.running_frames, 11);
		multiple_images_destroyer(get_data()->gun.reloading_frames, 12);
		multiple_images_destroyer(get_data()->gun.first_scope_frames, 6);
		multiple_images_destroyer(get_data()->gun.last_scope_frames, 5);
		multiple_images_destroyer(get_data()->gun.scope_shooting_frames, 6);
		int i;
		i = 0;
		i = 0;
		while (i < 15)
		{
			if (get_data()->dying_frames[i].img_data.img != NULL)
				mlx_destroy_image(get_data()->mlx,
								  get_data()->dying_frames[i].img_data.img);
			i++;
		}
		i = 0;
		while (i < 16)
		{
			if (get_data()->sprites_frames[i].img_data.img != NULL)
				mlx_destroy_image(get_data()->mlx,
								  get_data()->sprites_frames[i].img_data.img);
			i++;
		}
		i = 0;
		while (i < 17)
		{
			if (get_data()->door.images[i].img_data.img != NULL)
				mlx_destroy_image(get_data()->mlx,
								  get_data()->door.images[i].img_data.img);
			i++;
		}
		i = 0;
		while (i < get_data()->num_sprites)
		{
			if (get_data()->sprites[i].texture.img_data.img != NULL)
				mlx_destroy_image(get_data()->mlx,
								  get_data()->sprites[i].texture.img_data.img);
			i++;
		}

		i = 0;
		// multiple_images_destroyer(get_data()->sprites_frames, 16);
		//============================================================
		//============================================================

		multiple_images_destroyer(get_data()->gun.walking_frames, 11);

		t_data *data = get_data();
		if (data == NULL)
		{
			printf("Error: get_data() returned NULL\n");
			return;
		}
		if (data->north_img.img_data.img != NULL)
			mlx_destroy_image(data->mlx, data->north_img.img_data.img);
		if (data->south_img.img_data.img != NULL)
			mlx_destroy_image(data->mlx, data->south_img.img_data.img);
		if (data->east_img.img_data.img != NULL)
			mlx_destroy_image(data->mlx, data->east_img.img_data.img);
		if (data->west_img.img_data.img != NULL)
			mlx_destroy_image(data->mlx, data->west_img.img_data.img);
		if (data->door_img.img_data.img != NULL)
			mlx_destroy_image(data->mlx, data->door_img.img_data.img);
		// if (data->door_animating_img.img_data.img != NULL)
			// mlx_destroy_image(data->mlx, data->door_animating_img.img_data.img);
		// if (data->door_animating_img.img_data.img != NULL)
			// mlx_destroy_image(data->mlx, data->door_animating_img.img_data.img);
		// {
		// 	printf("Destroying image: %p\n",
		// 		   data->door_animating_img.img_data.img);
		// }
		// else
		// {
		// 	printf("No image to destroy\n");
		// }
		if (data->door_open_img.img_data.img != NULL)
			mlx_destroy_image(data->mlx, data->door_open_img.img_data.img);
		if (data->background_img.img != NULL)
			mlx_destroy_image(data->mlx, data->background_img.img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		// fprintf(stderr, "mlx freed===================================\n");
	}
	free_all_heap();
	exit(code);
}
