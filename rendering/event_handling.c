#include "../cube.h"

int	ft_close(void)
{
	exiter(0);
	return (0);
}

int	handle_keys(int keycode, void *garbage)
{
	(void)garbage;
	if (keycode == ESC)
	{
		mlx_destroy_window(get_data()->mlx, get_data()->win);
		exiter(0);
	}
	return (0);
}
