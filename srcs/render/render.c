#include "../../includes/rt.h"

// y = i / WIDTH
// x = i % WIDTH
void    trace(t_data *data)
{
    int     i;
    t_ray   ray;
    t_color color;

    i = 0;
    ray.origin = data->camera.origin;
    while (i < HEIGHT * WIDTH)
    {
        ray.direction = data->camera.ray_direction[i];
        color = intersect(ray);
        pixel_put(&data->img, i % WIDTH, i / WIDTH, color);
        ++i;
    }
}

int update(t_data *data)
{
    if (!data->win)
        return (1);
    trace(data);
    mlx_put_image_to_window(data->id, data->win, data->img.image, 0, 0);
    return (0);
}

void    render()
{
    t_data  *data;

    data = get_data();
    calculatePixels(data);
    mlx_loop_hook(data->id, &update, data);
	mlx_hook(data->win, 2, 1L << 0, &key, data);
	mlx_hook(data->win, 17, 0, &free_data, data);
    mlx_loop(data->id);
}