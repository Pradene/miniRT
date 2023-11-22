#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "matrix.h"

# define WIDTH 1920
# define HEIGHT 1080
# define ASPECT_RATIO (float)WIDTH / (float)HEIGHT

typedef struct  s_camera
{
    int     created;
    vec4    origin;
    vec4    direction;
    int     fov;
    mat44   m_projection;
    mat44   m_inverse_projection;
    mat44   m_view;
    mat44   m_inverse_view;
    vec4    ray_direction[HEIGHT * WIDTH];
}   t_camera;

void    calculate_rays(t_camera *cam);
int     camera(char **args);

void    move_camera(t_camera *cam);

#endif