#include "../cube.h"

// this will calculate wich pixel should take from image buffer
unsigned int get_right_pixel(float i, t_ray_data ray)
{
    int pixel_x;
    float pixel_y;
    float hit_point;
    t_texture texture;

    if (ray.side == 0)  // if it hits on the vertical side
    {
        hit_point = get_data()->player_pos.y + (ray.dist * ray.ray_dir.y);
        if (ray.object_hitted == 2)
            texture = get_data()->door_open_img;
        else if (ray.object_hitted == 1)
            texture = get_data()->door_img;
        else if (ray.object_hitted == 3)
            texture = get_data()->door_animating_img;
        else if (ray.ray_dir.x > 0)
            texture = get_data()->east_img;
        else
            texture = get_data()->west_img;
    }
    else  // else if it ray hit on horizontal side
    {
        hit_point = get_data()->player_pos.x + (ray.dist * ray.ray_dir.x);
        if (ray.object_hitted == 2)
            texture = get_data()->door_open_img;
        else if (ray.object_hitted == 1)
            texture = get_data()->door_img;
        else if (ray.object_hitted == 3)
            texture = get_data()->door_animating_img;
        else if (ray.ray_dir.y > 0)
            texture = get_data()->north_img;
        else
            texture = get_data()->south_img;
    }
    pixel_x = (int)(hit_point * texture.width / GRID_DIST) % texture.width;
    pixel_y = (int)((i - (WIN_HEIGHT / 2 - ray.wall_height / 2)) /
                    ray.wall_height * texture.height) %
              texture.height;
    return (pull_pixel(texture, pixel_x, (int)pixel_y));
}

// this will find the texture
int calc_color(t_ray_data ray, int start, int i, int end)
{
    int projected_wall;
    int color;

    projected_wall = end - start;
    color = get_right_pixel(i, ray);
    if (GET_T(color) == 255)
    {
        return (color);
    }
    if (get_data()->dark_mode)
        color = CREATE_TRGB(
            0,
            (int)(GET_R(color) * ((float)projected_wall / (float)WIN_HEIGHT)),
            (int)(GET_G(color) * ((float)projected_wall / (float)WIN_HEIGHT)),
            ((int)(GET_B(color) *
            ((float)projected_wall / (float)WIN_HEIGHT))));
    return (color);
}

void draw_col(t_ray_data ray, int col)
{
    int start;
    int end;
    int i;

    ray.wall_height =
        (GRID_DIST / (ray.dist * cos(ray.angle - get_data()->player_angle))) *
        ((WIN_WIDTH / 2) / tan((FOV * get_data()->zoom_factor) / 2));
    start = (WIN_HEIGHT - (int)ray.wall_height) / 2;
    end = start + (int)ray.wall_height;
    if (start < 0) start = 0;
    if (end > WIN_HEIGHT) end = WIN_HEIGHT;
    i = start;
    while (i < end)
    {
		put_pixel(&(get_data()->background_img), col, i,
			calc_color(ray, start, i, end));
        i++;
    }
}

int	check_hitting_object(t_ray_data *ray, char current_tile, int data_taken, int col)
{
	if (current_tile == '1')
	{
		ray->object_hitted = 0;
		if (!data_taken && ray->angle == get_data()->player_angle)
		{
			get_data()->front_ray = *ray;
			calculate_ray_distance(&(get_data()->front_ray));
			data_taken = 1;
		}
	}
	else if (current_tile == 'P')
	{
		ray->object_hitted = 3;
		if (!data_taken && ray->angle == get_data()->player_angle)
		{
			get_data()->front_ray = *ray;
			calculate_ray_distance(&(get_data()->front_ray));
			data_taken = 1;
		}
		perform_dda(*ray, data_taken, col);
	}
	else if (current_tile == 'D')
	{
		ray->object_hitted = 1;
		if (!data_taken && ray->angle == get_data()->player_angle)
		{
			get_data()->front_ray = *ray;
			calculate_ray_distance(&(get_data()->front_ray));
			data_taken = 1;
		}
	}
	else if (current_tile == 'O')
	{
		ray->object_hitted = 2;
		if (!data_taken && ray->angle == get_data()->player_angle)
		{
			get_data()->front_ray = *ray;
			calculate_ray_distance(&(get_data()->front_ray));
			data_taken = 1;
		}
		perform_dda(*ray, data_taken, col);
	}
	else
		return (0);
	return (1);
}

void    perform_dda(t_ray_data ray, int data_taken, int col)
{
    while (1)
    {
        if (ray.side_dist.x < ray.side_dist.y)
        {
            ray.side_dist.x += ray.delta_dist.x;
            ray.map_x += ray.step_x;
            ray.side = 0;
        }
        else
        {
            ray.side_dist.y += ray.delta_dist.y;
            ray.map_y += ray.step_y;
            ray.side = 1;
        }
		if (check_hitting_object(&ray, get_data()->map[ray.map_y][ray.map_x]
            , data_taken, col))
		{
			calculate_ray_distance(&ray);
			draw_col(ray, col);
			return;
		}
    }
}

void render_walls(void)
{
	int		col;
	float	ray_angle;

	col = 0;
	while (col < WIN_WIDTH)
	{
		ray_angle = normalise_angle(get_data()->player_angle
			- ((FOV * get_data()->zoom_factor) / 2)
			+ (col * ((FOV * get_data()->zoom_factor) / WIN_WIDTH)));
		perform_dda(create_ray(ray_angle), 0, col);
		++col;
	}
}
