/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:26 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/27 14:50:03 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// this will be used to store data and share it
// t_data	*get_data(void)
// {
// 	static t_data	data;

// 	return (&data);
// }
// // initialazing the struct data of cube
// void	init_data()
// {
// 	get_data()->mlx = mlx_init();
// 	if (get_data()->mlx != NULL)
// 	{
// 		get_data()->win = mlx_new_window(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
// 		get_data()->data.img = mlx_new_image(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	}
// 	if (get_data()->mlx == NULL || get_data()->win == NULL || get_data()->data.img == NULL)
// 	{
// 		ft_putstr_fd("CUB3D: mlx failed\n", 2);
// 		exiter(1);
// 	}
// 	vars->data.addr = mlx_get_data_addr(vars->data.img,
// 			&(vars->data.bits_per_pixel), &(vars->data.line_length),
// 			&(vars->data.endian));
// 	get_data()->floor_color = BROWN;// TODO this just for startin befroe parsing is complete
// 	get_data()->ceiling_color = CYAN;// TODO this just for startin befroe parsing is complete
// }



int	main(int ac, char **av)
{
	(void) ac;
	(void) av;

	// init_data();
	// render_background();

	//TODO complete .. 
	return (0);
}