/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:02:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/22 02:33:13 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"

static void	multiple_images_destroyer(void	**images, unsigned int	size)
{
	unsigned int	i;

	i = 0;
	if (images == NULL)
		return ;
	while (i < size )
	{
		if (images[i] != NULL)
			mlx_destroy_image(get_data()->mlx, images[i]);
		i++;
	}
}

// this will act as clean exiter , that free and remove leaks before exiting
void	exiter(int code)
{
	free_all_heap();
	int i = 0;
	multiple_images_destroyer(get_data()->gun2.shooting_frames, 27);
	multiple_images_destroyer(get_data()->gun2.img, 20);
	multiple_images_destroyer(get_data()->gun.img, 18);
	multiple_images_destroyer(get_data()->gun2.running_frames, 23);
	multiple_images_destroyer(get_data()->gun2.walking_frames, 13);
	// while (i < 27)
	// {
	// 	mlx_destroy_image(get_data()->mlx, get_data()->gun2.shooting_frames[i]);
	// 	i++;
	// }
	// i = 0;
	// while(i < 20)
	// {
	// 	mlx_destroy_image(get_data()->mlx, get_data()->gun2.img[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < 18)
	// {
	// 	mlx_destroy_image(get_data()->mlx, get_data()->gun.img[i]);
	// 	i++;
	// }
	mlx_destroy_image(get_data()->mlx, get_data()->north_img.img_data.img);
	mlx_destroy_image(get_data()->mlx, get_data()->south_img.img_data.img);
	mlx_destroy_image(get_data()->mlx, get_data()->east_img.img_data.img);
	mlx_destroy_image(get_data()->mlx, get_data()->west_img.img_data.img);
	mlx_destroy_image(get_data()->mlx, get_data()->door_img.img_data.img);
	// mlx_destroy_image(get_data()->mlx, get_data()->minimap.img_data.img);
	// mlx_destroy_image(get_data()->mlx, get_data()->scope.img);
	
	mlx_destroy_image(get_data()->mlx, get_data()->background_img.img);
	mlx_destroy_display(get_data()->mlx);
	free(get_data()->mlx);
	exit(code);
}