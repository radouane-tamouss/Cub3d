/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:02:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/23 22:46:27 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// as its name says, you give it array of images and its size the function will
// destroy all of them as long they're not NULL
static void multiple_images_destroyer(void **images, unsigned int size)
{
    unsigned int i;

    i = 0;
    if (images == NULL)
        return;
    while (i < size)
    {
        if (images[i] != NULL)
            mlx_destroy_image(get_data()->mlx, images[i]);
        i++;
    }
}

// this will act as clean exiter , that free and remove leaks before exiting
void exiter(int code)
{
    if (get_data()->mlx != NULL)
    {
        multiple_images_destroyer(get_data()->gun2.shooting_frames, 12);
        multiple_images_destroyer(get_data()->gun2.reloading_frames, 15);
        multiple_images_destroyer(get_data()->gun.reloading_frames, 18);
        multiple_images_destroyer(get_data()->gun2.running_frames, 23);
        multiple_images_destroyer(get_data()->gun2.walking_frames, 13);
        multiple_images_destroyer(get_data()->gun3.shooting_frames, 15);
        multiple_images_destroyer(get_data()->gun3.running_frames, 11);        
        multiple_images_destroyer(get_data()->gun3.reloading_frames, 12);   
        multiple_images_destroyer(get_data()->gun3.first_scope_frames, 6);   
        multiple_images_destroyer(get_data()->gun3.last_scope_frames, 5);   
        multiple_images_destroyer(get_data()->gun3.scope_shooting_frames, 6);           
        multiple_images_destroyer(get_data()->door.img, 17);
        int i ;
        i = 0;
        while (i < 15)
        {
            if (get_data()->dying_frames[i].img_data.img != NULL)
                mlx_destroy_image(get_data()->mlx, get_data()->dying_frames[i].img_data.img);
            i++;
        }
        i = 0;
        while (i < 16)
        {
            if (get_data()->sprites_frames[i].img_data.img != NULL)
                mlx_destroy_image(get_data()->mlx, get_data()->sprites_frames[i].img_data.img);
            i++;
        }
        i = 0;
        while (i < get_data()->num_sprites)
        {
            if (get_data()->sprites[i].texture.img_data.img != NULL)
                mlx_destroy_image(get_data()->mlx, get_data()->sprites[i].texture.img_data.img);
            i++;
        }
        
        // multiple_images_destroyer(get_data()->sprites_frames, 16);
        //============================================================
        //============================================================
            
        multiple_images_destroyer(get_data()->gun3.walking_frames, 11);        

        if (get_data()->north_img.img_data.img != NULL)
            mlx_destroy_image(get_data()->mlx,
                              get_data()->north_img.img_data.img);
        if (get_data()->south_img.img_data.img != NULL)
            mlx_destroy_image(get_data()->mlx,
                              get_data()->south_img.img_data.img);
        if (get_data()->east_img.img_data.img != NULL)
            mlx_destroy_image(get_data()->mlx,
                              get_data()->east_img.img_data.img);
        if (get_data()->west_img.img_data.img != NULL)
            mlx_destroy_image(get_data()->mlx,
                              get_data()->west_img.img_data.img);
        if (get_data()->door_img.img_data.img != NULL)
            mlx_destroy_image(get_data()->mlx,
                              get_data()->door_img.img_data.img);
        if (get_data()->door_animating_img.img_data.img != NULL)
            mlx_destroy_image(get_data()->mlx, get_data()->door_animating_img.img_data.img);
        if (get_data()->door_open_img.img_data.img != NULL)
            mlx_destroy_image(get_data()->mlx, get_data()->door_open_img.img_data.img);
        if (get_data()->background_img.img != NULL)
            mlx_destroy_image(get_data()->mlx, get_data()->background_img.img);
        mlx_destroy_display(get_data()->mlx);
        free(get_data()->mlx);
        // fprintf(stderr, "mlx freed===================================\n");
    }
    free_all_heap();
    exit(code);
}
