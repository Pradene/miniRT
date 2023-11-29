#include "../../includes/rt.h"

void    calculate_rays(t_camera *cam)
{
    int     i;
    float   x;
    float   y;
    vec4    r;
    vec4    v;

    i = -1;
    while (++i < HEIGHT * WIDTH)
    {
        x = (float)(i % WIDTH + 0.5) / WIDTH * 2 - 1.0;
        y = (float)(i / WIDTH + 0.5) / HEIGHT * 2 - 1.0;
        v = mat_vec_product(cam->m_inverse_projection, vector4(x, y, 1, 1));
        v /= v.w;
        vector_normalize(&v);
        r = mat_vec_product(cam->m_inverse_view, v);
        cam->ray_direction[i] = r;
    }
}

void    view_matrix(t_camera *cam, vec4 forward)
{
    vec4   right;
    vec4   up;

    up = vector4(0, 1, 0, 1);
    vector_normalize(&forward);
    right = vector_cross(&forward, &up);
    vector_normalize(&right);
    up = vector_cross(&right, &forward);
    vector_normalize(&up);
    cam->m_view[0][0] = right.x;
    cam->m_view[0][1] = up.x;
    cam->m_view[0][2] = forward.x;
    cam->m_view[0][3] = 0;
    cam->m_view[1][0] = right.y;
    cam->m_view[1][1] = up.y;
    cam->m_view[1][2] = forward.y;
    cam->m_view[1][3] = 0;
    cam->m_view[2][0] = right.z;
    cam->m_view[2][1] = up.z;
    cam->m_view[2][2] = forward.z;
    cam->m_view[2][3] = 0;
    cam->m_view[3][0] = -vector_dot(&cam->origin, &right);
    cam->m_view[3][1] = -vector_dot(&cam->origin, &up);
    cam->m_view[3][2] = -vector_dot(&cam->origin, &forward);
    cam->m_view[3][3] = 1;
}

void    projection_matrix(t_camera *cam, int near, int far, int fov)
{
    cam->m_projection[0][0] = 1.0 / (ASPECT_RATIO * tan((float)fov / 2));
    cam->m_projection[1][1] = 1.0 / tan((float)fov / 2);
    cam->m_projection[2][2] = -(far + near) / (far - near);
    cam->m_projection[2][3] = -1.0;
    cam->m_projection[3][2] = -(2 * far * near) / (far - near);
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
    mat(&data->camera.m_view);
    mat(&data->camera.m_inverse_view);
    mat(&data->camera.m_projection);
    mat(&data->camera.m_inverse_projection);
    view_matrix(&data->camera, data->camera.direction);
    mat_inverse(data->camera.m_view, &data->camera.m_inverse_view);
    projection_matrix(&data->camera, 1, 100, data->camera.fov);
    mat_inverse(data->camera.m_projection, &data->camera.m_inverse_projection);
    if (!check_camera(data->camera))
        return (0);
    return (1);
}

void    move_camera(t_camera *cam)
{
    view_matrix(cam, cam->direction);
    mat_inverse(cam->m_view, &cam->m_inverse_view);
}

void    rotate_camera(t_camera *cam, float angle_x, float angle_y)
{
    mat44   rot;
    float   angle_z;

    angle_z = 0;
    rot[0][0] = cos(angle_y) * cos(angle_z);
    rot[0][1] = sin(angle_x) * sin(angle_y) * cos(angle_z) - cos(angle_x) * sin(angle_z); 
    rot[0][2] = cos(angle_x) * sin(angle_y) * cos(angle_z) + sin(angle_x) * sin(angle_z); 
    rot[0][3] = 0;
    rot[1][0] = cos(angle_y) * sin(angle_z);
    rot[1][1] = sin(angle_x) * sin(angle_y) * sin(angle_z) + cos(angle_x) * cos(angle_z);
    rot[1][2] = cos(angle_x) * sin(angle_y) * sin(angle_z) - sin(angle_x) * cos(angle_z); 
    rot[1][0] = 0;
    rot[2][0] = -sin(angle_y);
    rot[2][1] = sin(angle_x) * cos(angle_y);
    rot[2][2] = cos(angle_x) * cos(angle_y);
    rot[2][3] = 0;
    rot[3][0] = 0;
    rot[3][1] = 0;
    rot[3][2] = 0;
    rot[3][3] = 1;
    // cam->m_view = mat_product(cam->m_view, rot);
    // mat_inverse(cam->m_view, &cam->m_inverse_view);

    cam->direction = mat_vec_product(rot, cam->direction);
    vector_normalize(&cam->direction);
    view_matrix(cam, cam->direction);
    mat_inverse(cam->m_view, &cam->m_inverse_view);
    calculate_rays(cam);
}
