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

float   get_elapsed_time(void)
{
    float           elapsed_time;
    struct timeval  tv;
    long            time;
    static long     last_frame = 0;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    elapsed_time = time - last_frame;
    last_frame = time;
    return (elapsed_time);
}

int update(t_data *data)
{
    if (!data->win)
        return (1);
    data->et = get_elapsed_time();
    trace(data);
    mlx_put_image_to_window(data->id, data->win, data->img.image, 0, 0);
    return (0);
}

void    render()
{
    t_data  *data;

    data = get_data();
    calculate_rays(&data->camera);
    mlx_loop_hook(data->id, &update, data);
	mlx_hook(data->win, 2, 1L << 0, &key, data);
	mlx_hook(data->win, 17, 0, &free_data, data);
    mlx_loop(data->id);
}