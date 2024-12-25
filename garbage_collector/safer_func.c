/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safer_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:49:30 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/25 20:41:22 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// void    *safer_new_image(void *mlx, int width, int height)//TODO not used yet
// {
//     void    *img;

//     if (width <= 0 || height <= 0 || mlx == NULL)
//         exiter(1);
//     img = mlx_new_image(mlx, width, height);
//     if (img == NULL)
//     {
// 		print_err("CUB3D: mlx failed\n");
//         exiter(1);
//     }
//     return (img);
// }





void    *safer_get_data_addr(void *img, int *bits_per_pixel,
			   int *size_line, int *endian)
{
    void    *addr;
    if (img == NULL || bits_per_pixel == NULL || size_line == NULL
        || size_line == NULL || endian == NULL)
        exiter(1);
    addr = mlx_get_data_addr(img, bits_per_pixel, size_line, endian);
    if (addr == NULL)
    {
		print_err("CUB3D: mlx failed\n");
        exiter(1);
    }
    return (addr);
}
void	*safer_xpm_file_to_image(void *xvar,char *filename,
			       int *width,int *height)
{
    void    *img;

    if (xvar == NULL || filename == NULL || width == NULL || height == NULL)
        exiter(0);
    img = mlx_xpm_file_to_image(xvar, filename, width, height);
    if (img == NULL)
    {
		print_err("CUB3D: mlx failed\n");
        exiter(1);
    }
    return (img);
}
