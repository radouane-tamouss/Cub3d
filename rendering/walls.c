#include "../cube.h"
// this init the direction (vector) of the ray
void init_ray_dir(t_ray_data *ray, float ray_angle)
{
	ray->angle = ray_angle;
    ray->ray_dir.x = cos(ray_angle);
    ray->ray_dir.y = sin(ray_angle);
    ray->map_x = (int)(get_data()->player_pos.x / GRID_DIST);
    ray->map_y = (int)(get_data()->player_pos.y / GRID_DIST);
}
// calc the delta that we need to travel to hit the intersact with the next line of grid
void calc_delta_dist(t_ray_data *ray)
{
    ray->delta_dist.x = ft_abs(1 / ray->ray_dir.x);
    ray->delta_dist.y = ft_abs(1 / ray->ray_dir.y);
}
//calc the distance need to travel from intersection to another x
void calc_step_and_side_dist_x(t_ray_data *ray)
{
    float player_x;

    player_x = get_data()->player_pos.x / GRID_DIST;

    if (ray->ray_dir.x < 0)
    {
        ray->step_x = -1;
        ray->side_dist.x = (player_x - ray->map_x) * ray->delta_dist.x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist.x = (ray->map_x + 1.0 - player_x) * ray->delta_dist.x;
    }
}
//calc the distance need to travel from intersection to another y
void calc_step_and_side_dist_y(t_ray_data *ray)
{
    float player_y;

    player_y = get_data()->player_pos.y / GRID_DIST;

    if (ray->ray_dir.y < 0)
    {
        ray->step_y = -1;
        ray->side_dist.y = (player_y - ray->map_y) * ray->delta_dist.y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist.y = (ray->map_y + 1.0 - player_y) * ray->delta_dist.y;
    }
}
// traveling till hit the wall and save the data
int perform_dda(t_ray_data *ray)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (get_data()->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
    return hit;
}

void	calculate_distance(t_ray_data *ray)
{
    if (ray->side == 0)
        ray->dist = (ray->side_dist.x - ray->delta_dist.x) * GRID_DIST;
    else
        ray->dist = (ray->side_dist.y - ray->delta_dist.y) * GRID_DIST;
}

// casting the ray and grab all wanted data (coords of wall, side, ...)
t_ray_data cast_ray(float ray_angle)
{
    t_ray_data ray;


    init_ray_dir(&ray, ray_angle);
    calc_delta_dist(&ray);
    calc_step_and_side_dist_x(&ray);
    calc_step_and_side_dist_y(&ray);
    perform_dda(&ray);
	calculate_distance(&ray);
    return ray;
}

// this will calculate wich pixel should take from image buffer
unsigned int get_right_pixel(float i, t_ray_data ray)
{
    int pixel_x;
    float pixel_y;
    float hit_point;
    t_texture texture;
    // float tex_pos;

    if (ray.side == 0) // if it hits on the vertical side
    {
        hit_point = get_data()->player_pos.y + (ray.dist * ray.ray_dir.y);
		if (ray.ray_dir.x > 0)
			texture = get_data()->east_img;
		else
			texture = get_data()->west_img;
    }
    else // else if it ray hit on horizontal side
    {
        hit_point = get_data()->player_pos.x + (ray.dist * ray.ray_dir.x);
        if (ray.ray_dir.y > 0)
			texture = get_data()->north_img;
		else
			texture = get_data()->south_img;
    }

    // calc the x coords in the texture
    pixel_x = (int)(hit_point * texture.width / GRID_DIST) % texture.width;


	// trying to find t x and y of the pixel must be pulled from the texture image

    // calc the y coords in the texture
    pixel_y = (int)((i - (WIN_HEIGHT / 2 - ray.wall_height / 2)) / ray.wall_height * texture.height) % texture.height;
	// making sure the y pixel is between 0 and height of our texture
    // pixel_y = fmaxf(0, fminf(pixel_y, texture.height - 1));
    return (pull_pixel(texture, pixel_x, (int)pixel_y));
}

// this will find the texture later
int calc_color(t_ray_data ray, int start, int i, int end)
{
    int projected_wall;
	int	color;

    projected_wall = end - start;
	color = get_right_pixel(i, ray);
	color = CREATE_TRGB(0,
		((int)(GET_R(color) * ((float)projected_wall / (float)WIN_HEIGHT))),
		((int)(GET_G(color) * ((float)projected_wall / (float)WIN_HEIGHT))),
		((int)(GET_B(color) * ((float)projected_wall / (float)WIN_HEIGHT))));
	return (color);
}


void draw_col(t_ray_data ray, int col)
{
	float wall_height;
	int start;
	int end;
	int i;

	ray.wall_height = (GRID_DIST / ray.dist) * ((WIN_WIDTH / 2) / tan(FOV / 2));
	start = (WIN_HEIGHT - (int)ray.wall_height) / 2;
	end = start + (int)ray.wall_height;
	if (start < 0)
		start = 0;
	if (end > WIN_HEIGHT)
		end = WIN_HEIGHT;
	i = start;
	while (i < end)
	{
        put_pixel(&(get_data()->background_img), col, i, calc_color(ray, start, i, end));
		i++;
	}
}

// will calc the angle of the ray then cast to the wall and calc the dist
void render_col(int col)
{
    float ray_angle;
	t_ray_data	ray;
	int color;

	ray_angle = normalise_angle(get_data()->player_angle - (FOV/2) + (col * (FOV/WIN_WIDTH)));
	ray = cast_ray(ray_angle);
    draw_col(ray, col);
}

// this will draw the the walls on the background img (it will not put it to window)
void	render_walls(void)
{
	int i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		render_col(i++);// render each column of the window
	}
}
