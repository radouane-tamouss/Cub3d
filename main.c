/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:26 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/17 23:32:49 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// this will be used to store data and share it
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
// initialazing the struct data of cube
void	init_data()
{
	get_data()->mlx = mlx_init();
	if (get_data()->mlx != NULL)
	{
		get_data()->win = mlx_new_window(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");
		get_data()->walls.img = mlx_new_image(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	}
	if (get_data()->mlx == NULL || get_data()->win == NULL || get_data()->walls.img == NULL)
	{
		print_err("CUB3D: mlx failed\n");
		exiter(1);
	}
	get_data()->walls.addr = mlx_get_data_addr(get_data()->walls.img,
			&(get_data()->walls.bits_per_pixel), &(get_data()->walls.line_length),
			&(get_data()->walls.endian));
	get_data()->floor_color = GREEN;// TODO this just for startin befroe parsing is complete
	get_data()->ceiling_color = CYAN;// TODO this just for startin befroe parsing is complete
	create_background();
	mlx_hook(get_data()->win, 2, 1L << 0, handle_keys, NULL);// this to handle when a key pressed
	mlx_hook(get_data()->win, 17, 1L << 0, ft_close, NULL);// this to handle when red arrow clicked

}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	init_data();
	render_background();
	//TODO complete .. 
	mlx_loop(get_data()->mlx);
	return (0);
}