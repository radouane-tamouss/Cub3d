#include "../cube.h"

int	ft_close(void)
{
	exiter(0);
	return (0);
}

int	handle_keys(int keycode, void *garbage)
{
	(void)garbage;
	printf("keycode => %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(get_data()->mlx, get_data()->win);
		exiter(0);
	}
	else if (keycode == W)
		get_data()->player_y -= 10;
	else if (keycode == S)
		get_data()->player_y += 10;
	else if (keycode == D)
		get_data()->player_x += 10;
	else if (keycode == A)
		get_data()->player_x -= 10;
	printf("===== coords (%d, %d)\n", get_data()->player_x, get_data()->player_y);
	return (0);
}
