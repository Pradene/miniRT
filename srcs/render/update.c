#include "../../includes/rt.h"

// This function send rays for every pixels
// to get the color and put it on the screen
void    trace(t_image *img, t_camera *cam)
{
    int     i;
    t_ray   ray;
    rgba    color;

    i = 0;
    ray.origin = cam->origin;
    while (i < HEIGHT * WIDTH)
    {
        ray.direction = cam->ray_direction[i];
        color = intersect(ray);
        pixel_put(img, i % WIDTH, i / WIDTH, color);
        ++i;
    }
}

// This function gives the time in ms since the last frame
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

// This function is called every frame to render things on screen
int update(t_data *data)
{
    if (!data->win)
        return (1);
    data->et = get_elapsed_time();
    trace(&data->img, &data->camera);
    mlx_put_image_to_window(data->id, data->win, data->img.image, 0, 0);
    return (0);
}