#include "../../includes/rt.h"

void    calculatePixels(t_data *data)
{
    int     i;
    int     x;
    int     y;

    i = 0;
    while (i < HEIGHT * WIDTH)
    {
        x = i % WIDTH;
        y = i / WIDTH;
        data->camera.ray_direction[i].x = data->camera.direction.x + (((i % WIDTH + 0.5) / WIDTH) * 2.0 - 1.0) * ASPECT_RATIO * tan(radian(data->camera.fov / 2));
        data->camera.ray_direction[i].y = data->camera.direction.y + (((HEIGHT - (i / WIDTH + 0.5)) / HEIGHT) * 2.0 - 1.0) * tan(radian(data->camera.fov / 2));
        data->camera.ray_direction[i].z = data->camera.direction.z + -1;
        data->camera.ray_direction[i].w = 1;
        vector_normalize(&data->camera.ray_direction[i]);
        ++i;
    }
}

void    calculateProjection(t_camera *cam, int near, int far, int fov)
{
    float   scale;

    scale = 1 / tan(fov / 2 * PI / 180);
    cam->m_projection.array[0 * 4 + 0] = scale;
    cam->m_projection.array[1 * 4 + 1] = scale;
    cam->m_projection.array[2 * 4 + 2] = -far / (far - near);
    cam->m_projection.array[2 * 4 + 3] = -1;
    cam->m_projection.array[3 * 4 + 2] = -far * near / (far - near);
    cam->m_projection.array[3 * 4 + 3] = 0;
}

int check_camera(t_camera camera)
{
    if (!check_fov(camera.fov) || !check_direction(camera.direction))
        return (0);
    return (1);
}

int camera(char **args)
{
    t_data  *data;
    char    *tmp;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    if (data->camera.created)
        return (0);
    data->camera.origin = atov4(args[1], false);
    data->camera.direction = atov4(args[2], true);
    data->camera.fov = (int)ft_atof(args[3], &tmp);
    data->camera.created = 1;
    calculateProjection(&data->camera, 1, 100, data->camera.fov);
    inverse_mat(data->camera.m_projection, &data->camera.m_inverse_projection);
    if (!check_camera(data->camera))
        return (0);
    return (1);
}
