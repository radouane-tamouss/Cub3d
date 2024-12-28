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
// clang-format off

static	void	destroy_remaining_images(void)
{
	if (get_data()->north_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->north_img.img_data.img);
	if (get_data()->south_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->south_img.img_data.img);
	if (get_data()->east_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->east_img.img_data.img);
	if (get_data()->west_img.img_data.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->west_img.img_data.img);
	if (get_data()->background_img.img != NULL)
		mlx_destroy_image(get_data()->mlx, get_data()->background_img.img);
}

// this will act as clean exiter , that free and remove leaks before exiting
void	exiter(int code)
{
	if (get_data()->mlx != NULL)
	{
		destroy_remaining_images();
		mlx_destroy_display(get_data()->mlx);
		free(get_data()->mlx);
	}
	free_all_heap();
	exit(code);
}
