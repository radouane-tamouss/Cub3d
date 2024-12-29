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

// clang-format off
int	loop_hook(void)
{
	update_movement();
	init_background();
	render_walls();
	render_minimap();
	render_sprites();
	update_door_animation();
	render_background();
	render_gun();
	render_cyrcle(WIN_WIDTH / 2, WIN_HEIGHT * 0.53f, 3, BLACK);
	return (0);
}

void	load_all_frames(void)
{
	load_shooting_gun3_frames();
	load_running_gun3_frames();
	load_reloading_gun3_frames();
	load_first_scope_frames();
	load_last_scope_frames();
	load_shooting_scope_frames();
	load_walking_gun3_frames();
	load_door_frames();
}

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	if (ac != 2 || check_file(av[1], &fd) == 0)
		return (print_err("Usage: ./Cube3d map.cub"), 0);
	game = check_map(fd, av[1]);
	close(fd);
	init_data(game);
	init_sprites(&game);
	init_background();
	render_walls();
	render_minimap();
	render_sprites();
	render_background();
	load_all_frames();
	render_gun();
	mlx_loop_hook(get_data()->mlx, loop_hook, NULL);
	mlx_loop(get_data()->mlx);
	return (0);
}
