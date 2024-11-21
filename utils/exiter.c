/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:02:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/21 03:29:00 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"

// this will act as clean exiter , that free and remove leaks before exiting
void	exiter(int code)
{
	free_all_heap();
	int i = 0;
	while (i < 27)
	{
		mlx_destroy_image(get_data()->mlx, get_data()->gun2.shooting_frames[i]);
		i++;
	}

	i = 0;
	while(i < 20)
	{
		mlx_destroy_image(get_data()->mlx, get_data()->gun2.img[i]);
		// printf("destoryed\n");
		i++;
	}
	i = 0;
	while (i < 18)
	{
		mlx_destroy_image(get_data()->mlx, get_data()->gun.img[i]);
		i++;
	}
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