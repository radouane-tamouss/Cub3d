/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:10:15 by atamousse.r       #+#    #+#             */
/*   Updated: 2024/12/27 01:38:09 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	loop_hook(void)
{
	update_movement();
	init_background();
	render_walls();
	render_background();
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	if (ac != 2 || check_file(av[1], &fd) == 0)
		return (printf("Error\nUsage: ./Cube3d map.cub\n"), 0);
	game = check_map(fd, av[1]);
	close(fd);
	init_data(game);
	init_background();
	render_walls();
	render_background();
	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);
	mlx_loop(get_data()->mlx);
	return (0);
}
