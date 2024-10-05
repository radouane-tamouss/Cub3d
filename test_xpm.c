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
	offset = y * img.img.line_length + x * (img.img.bits_per_pixel / 8);
	dst = img.img.addr + offset;
	ptr = (unsigned int *)dst;
	return (*ptr);
}

int	main(void)
{
	void	*mlx;
	t_texture	img;
	char	*relative_path = "ArtStation-Explore.xpm";

	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello world!");

	img.img.img = mlx_xpm_file_to_image(mlx, "ArtStation-Explore.xpm", &(img.width), &(img.height));
	img.img.addr = mlx_get_data_addr(img.img.img, &(img.img.bits_per_pixel), &(img.img.line_length), &(img.img.endian));

	if (img.img.img == NULL)
	{
		printf("err\n");
		exit(1);
	}

	t_img_data drawn_img;

	drawn_img.img = mlx_new_image(mlx, img.width, img.height);
	drawn_img.addr = mlx_get_data_addr(drawn_img.img, &(drawn_img.bits_per_pixel), &(drawn_img.line_length), &(drawn_img.endian));

	int i = 0;
	int j = 0;
	int color;

	while (i < img.height)
	{
		j = 0;
		while (j < img.width)
		{
			color = pull_pixel(img, j, i);
			put_pixel(&(drawn_img), j, i, color);
			j++;
		}
		i++;
	}
	
	mlx_put_image_to_window(mlx, mlx_win, drawn_img.img, 200, 200);
	mlx_loop(mlx);
}
