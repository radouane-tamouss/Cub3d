#include "cube.h"

#include <mlx.h>

//color a pixel in img in the cords (x, y)
void	put_pixel(t_img_data *img, int x, int y, int color)
{
	char			*dst;
	int				offset;
	unsigned int	*ptr;

	if (y >= WIN_HEIGHT || x >= WIN_WIDTH || x < 0 || y < 0)
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	ptr = (unsigned int *)dst;
	*ptr = color;
}
unsigned int	pull_pixel(t_texture img, int x, int y)
{
	int				offset;
	unsigned int	*ptr;
	char			*dst;


	if (y >= img.height || x >= img.width || x < 0 || y < 0)
		return 0x0;
	offset = y * img.img_data.line_length + x * (img.img_data.bits_per_pixel / 8);
	dst = img.img_data.addr + offset;
	ptr = (unsigned int *)dst;
	return (*ptr);
}

int	main(void)
{
	void	*mlx;
	t_texture	background;
	t_texture	hand;
	char	*relative_path = "ArtStation-Explore.xpm";

	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "test");

	background.img_data.img = mlx_xpm_file_to_image(mlx, "textures/north.xpm", &(background.width), &(background.height));
	hand.img_data.img = mlx_xpm_file_to_image(mlx, "textures/torch.xpm", &(hand.width), &(hand.height));
	background.img_data.addr = mlx_get_data_addr(background.img_data.img, &(background.img_data.bits_per_pixel), &(background.img_data.line_length), &(background.img_data.endian));
	hand.img_data.addr = mlx_get_data_addr(hand.img_data.img, &(hand.img_data.bits_per_pixel), &(hand.img_data.line_length), &(hand.img_data.endian));
	if (background.img_data.img == NULL || hand.img_data.img == NULL)
	{
		printf("err\n");
		exit(1);
	}
	int i = 0;
	int j = 0;
	int	color;

	while (i < background.height)
	{
		j = 0;
		while (j < background.width)
		{
			color = pull_pixel(hand, j, i);
			if (color != WHITE)
				put_pixel(&(background.img_data), j, i, color);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(mlx, mlx_win, background.img_data.img, 0, 0);



	mlx_loop(mlx);
}
