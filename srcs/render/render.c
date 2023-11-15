#include "../../includes/rt.h"

// transform a t_color struct into an integer color
int rgba_to_color(t_color c)
{
    int color;

    c.r = clamp(c.r, 0.0, 1.0);
    c.g = clamp(c.g, 0.0, 1.0);
    c.b = clamp(c.b, 0.0, 1.0);
    c.a = clamp(c.a, 0.0, 1.0);
    color = ((int)(c.a * 255) << 24) | ((int)(c.r * 255) << 16) \
    | ((int)(c.g * 255) << 8) | ((int)(c.b * 255) << 0);
    return (color);
}

void	pixel_put(t_image *img, int x, int y, t_color c)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = rgba_to_color(c);
}

// y = i / WIDTH
// x = i % WIDTH
void    trace(t_data *data)
{
    // int         i;
    // t_ray       r;
    // t_color     c;

    // c.r = 0;
    // c.g = 0;
    // c.b = 0;
    // c.a = 1;
    // i = 0;
    // r.position = data->camera.position;
    // while (i < HEIGHT * WIDTH)
    // {

    //     data->pixels[i].x = (((i % WIDTH + 0.5) / WIDTH) * 2.0 - 1.0) * ASPECT_RATIO * tan(radian(data->camera.fov / 2));
    //     data->pixels[i].y = (((HEIGHT - (i / WIDTH + 0.5)) / HEIGHT) * 2.0 - 1.0) * tan(radian(data->camera.fov / 2));
    //     data->pixels[i].z = -1;
    //     // r.direction = vector_add(&data->camera.direction, &data->pixels[i]);
    //     vector_normalize(&r.direction);

    //     c = intersect(r);
    //     // c.r = (float)(i % WIDTH) / WIDTH;
    //     // c.g = (float)(i / WIDTH) / HEIGHT;
    //     // c.b = 0;
    //     // c.a = 1;
    //     pixel_put(&data->img, i % WIDTH, i / WIDTH, c);
    //     ++i;
    // }

    int     y;
    int     x;
    t_ray   ray;
    t_color color;

    y = -1;
    ray.position = data->camera.position;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            ray.direction = data->pixels[y * WIDTH + x];            
            // vector_normalize(&ray.direction);
            color = intersect(ray);
            pixel_put(&data->img, x, y, color);
        }
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

void    calculatePixels(t_data *data)
{
    int     i;

    i = 0;
    while (i < HEIGHT * WIDTH)
    {
        data->pixels[i].x = data->camera.direction.x + (((i % WIDTH + 0.5) / WIDTH) * 2.0 - 1.0) * ASPECT_RATIO * tan(radian(data->camera.fov / 2));
        data->pixels[i].y = data->camera.direction.y + (((HEIGHT - (i / WIDTH + 0.5)) / HEIGHT) * 2.0 - 1.0) * tan(radian(data->camera.fov / 2));
        data->pixels[i].z = data->camera.direction.z + -1;
        data->pixels[i].w = 1;
        vector_normalize(&data->pixels[i]);
        ++i;
    }
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