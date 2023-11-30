#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "matrix.h"

# define WIDTH 1080
# define HEIGHT 720
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

int     camera(char **args);

void    rotate_camera(t_camera *cam, float angle_x, float angle_y);

void    view_matrix(t_camera *cam, vec4 forward);
void    calculate_m_view(t_camera *cam);
void    calculate_rays(t_camera *cam);

quat    multiply_quat(quat q1, quat q2);
quat    angleAxis(float angle, vec4 axis);
vec4    rotate(vec4 v, quat rotationQuat);
quat    normalize_quat(quat q);
void    quaternionToMatrix(quat q, mat44 *m);
mat44   translate(t_camera *cam);

#endif