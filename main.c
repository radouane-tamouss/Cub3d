/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:55:26 by eouhrich          #+#    #+#             */
/*   Updated: 2024/10/03 19:11:55 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_strdup(char *s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

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
		// get_data()->walls.img = mlx_new_image(get_data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	}
	if (get_data()->mlx == NULL || get_data()->win == NULL)
	{
		print_err("CUB3D: mlx failed\n");
		exiter(1);
	}
	// get_data()->walls.addr = mlx_get_data_addr(get_data()->walls.img,
	// 		&(get_data()->walls.bits_per_pixel), &(get_data()->walls.line_length),
	// 		&(get_data()->walls.endian));
	get_data()->floor_color = BROWN;// TODO this just for startin befroe parsing is complete
	get_data()->ceiling_color = CYAN;// TODO this just for startin befroe parsing is complete
	init_background();
	mlx_hook(get_data()->win, 2, 1L << 0, handle_keys, NULL);// this to handle when a key pressed
	mlx_hook(get_data()->win, 17, 1L << 0, ft_close, NULL);// this to handle when red arrow clicked
	// mlx_mouse_hook(get_data()->win, mouse_event, NULL);
	mlx_hook(get_data()->win, 6, 1L<<6, mouse_event, NULL);
	// mlx_hook(get_data()->win, 5, 1L << 0, mouse_event, NULL);// this to handle when mouse moves
	get_data()->player_pos.x = 3.5 * GRID_DIST;// TODO for test only
	get_data()->player_pos.y =  3.5 * GRID_DIST;// TODO for test only
	get_data()->player_angle = MY_PI/4;
	get_data()->player_dir.x = cos(get_data()->player_angle) * SPEED;
	get_data()->player_dir.y = sin(get_data()->player_angle) * SPEED;

	get_data()->map = (char **)malloc(sizeof(char *) * 11);
	get_data()->map[0] = ft_strdup("1111111111");
	get_data()->map[1] = ft_strdup("1000000001");
	get_data()->map[2] = ft_strdup("1000000001");
	get_data()->map[3] = ft_strdup("1000000001");
	get_data()->map[4] = ft_strdup("1000000001");
	get_data()->map[5] = ft_strdup("1000000001");
	get_data()->map[6] = ft_strdup("1000000001");
	get_data()->map[7] = ft_strdup("1000000001");
	get_data()->map[8] = ft_strdup("1000000001");
	get_data()->map[9] = ft_strdup("1111111111");

	get_data()->height = 10;
	get_data()->width = 10;
}

void	draw_circle(t_img_data *img, int cho3a3, t_vector point)
{
	int i = point.y - cho3a3;
	int j;

	while (i < point.y + cho3a3)
	{
		j = point.x - cho3a3;
		while (j < point.x + cho3a3)
		{
			if (calc_dist(j, i, point) <= cho3a3)
			{
				// printf("pixeled the point x ==%d  | y == %d | with dist == %d\n", j, i, calc_dist(j, i, point));
				put_pixel(img, j, i, RED);
			}
			j++;
		}
		i++;
	}
}

void	draw_player(void)
{
	t_vector player_front;

	player_front.x = get_data()->player_pos.x + 5 * get_data()->player_dir.x;
	player_front.y = get_data()->player_pos.y + 5 * get_data()->player_dir.y;
	draw_circle(&(get_data()->background_img), 7, get_data()->player_pos);
	line_between_2points(get_data()->player_pos,
				player_front, RED);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	init_data();
	// draw_player();
	render_walls();
	render_background();
	//TODO complete .. 
	mlx_loop(get_data()->mlx);
	return (0);
}