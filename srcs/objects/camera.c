#include "../../includes/rt.h"

void    calculate_rays(t_camera *cam)
{
    int     i;
    float   x;
    float   y;
    vec4    v;

    i = -1;
    while (++i < HEIGHT * WIDTH)
    {
        x = map(i % WIDTH + 0.5, vector2(0, WIDTH), vector2(-1, 1));
        y = map(i / WIDTH + 0.5, vector2(0, HEIGHT), vector2(-1, 1));
        v = mat_vec_product(cam->m_inverse_projection, vector4(x, y, 1, 1));
        v = v4_normalize(v / v.w);
        cam->ray_direction[i] = v4_normalize(mat_vec_product(cam->m_inverse_view, v));
    }
}

void    view_matrix(t_camera *cam, vec4 forward)
{
    vec4   right;
    vec4   up;

    up = vector4(0, 1, 0, 1);
    forward = v4_normalize(forward);
    right = v4_normalize(cross(forward, up));
    up = v4_normalize(cross(right, forward));
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
    cam->m_view[3][0] = -dot(cam->origin, right);
    cam->m_view[3][1] = -dot(cam->origin, up);
    cam->m_view[3][2] = -dot(cam->origin, forward);
    cam->m_view[3][3] = 1;
}

void    calculate_m_view(t_camera *cam)
{
    view_matrix(cam, cam->direction);
    cam->m_inverse_view = mat_inverse(cam->m_view);
}

void    projection_matrix(t_camera *cam, int near, int far, int fov)
{
    cam->m_projection[0][0] = 1.0 / (ASPECT_RATIO * tan(radian(fov / 2)));
    cam->m_projection[0][1] = 0.0;
    cam->m_projection[0][2] = 0.0;
    cam->m_projection[0][3] = 0.0;

    cam->m_projection[1][0] = 0.0;
    cam->m_projection[1][1] = 1.0 / tan(radian(fov / 2));
    cam->m_projection[1][2] = 0.0;
    cam->m_projection[1][3] = 0.0;

    cam->m_projection[2][0] = 0.0;
    cam->m_projection[2][1] = 0.0;
    cam->m_projection[2][2] = -(far + near) / (far - near);
    cam->m_projection[2][3] = -1.0;

    cam->m_projection[3][0] = 0.0;
    cam->m_projection[3][1] = 0.0;
    cam->m_projection[3][2] = -(2 * far * near) / (far - near);
    cam->m_projection[3][3] = 0.0;
}

int check_camera(t_camera *camera)
{
    if (!check_fov(camera->fov) || !check_direction(camera->direction))
        return (0);
    return (1);
}

int camera(char **args)
{
    t_data      *data;
    t_camera    *cam;
    char        *tmp;

    data = get_data();
    cam = &data->camera;
    if (string_array_size(args) != 4)
        return (0);
    if (data->camera.created)
        return (0);
    cam->origin = atov4(args[1], false);
    cam->direction = atov4(args[2], true);
    cam->direction = v4_normalize(cam->direction);
    cam->fov = (int)ft_atof(args[3], &tmp);
    cam->created = 1;

    cam->m_view = mat();
    cam->m_inverse_view = mat();
    cam->m_projection = mat();
    cam->m_inverse_projection = mat();

    calculate_m_view(cam);
    projection_matrix(cam, 1, 100, cam->fov);
    cam->m_inverse_projection = mat_inverse(cam->m_projection);
    if (!check_camera(cam))
        return (0);
    return (1);
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
    cam->direction = v4_normalize(cam->direction);
    calculate_m_view(cam);
    calculate_rays(cam);
}





//


void quaternionToMatrix(quat q, mat44 *m)
{
    q = normalize_quat(q);

    // Calculate matrix elements
    float xx = q.x * q.x;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float xw = q.x * q.w;

    float yy = q.y * q.y;
    float yz = q.y * q.z;
    float yw = q.y * q.w;

    float zz = q.z * q.z;
    float zw = q.z * q.w;

    // First row
    (*m)[0][0] = 1.0f - 2.0f * (yy + zz);
    (*m)[0][1] = 2.0f * (xy - zw);
    (*m)[0][2] = 2.0f * (xz + yw);
    (*m)[0][3] = 0.0f;

    // Second row
    (*m)[1][0] = 2.0f * (xy + zw);
    (*m)[1][1] = 1.0f - 2.0f * (xx + zz);
    (*m)[1][2] = 2.0f * (yz - xw);
    (*m)[1][3] = 0.0f;

    // Third row
    (*m)[2][0] = 2.0f * (xz - yw);
    (*m)[2][1] = 2.0f * (yz + xw);
    (*m)[2][2] = 1.0f - 2.0f * (xx + yy);
    (*m)[2][3] = 0.0f;

    // Fourth row
    (*m)[3][0] = 0.0f;
    (*m)[3][1] = 0.0f;
    (*m)[3][2] = 0.0f;
    (*m)[3][3] = 1.0f;
}

mat44   translate(t_camera *cam)
{
    mat44   m;
    vec4    up;
    vec4    right;
    vec4    forward;

    mat(&m);
    up = vector4(0, 1, 0, 1);
    forward = v4_normalize(cam->direction);
    right = v4_normalize(cross(forward, up));
    up = v4_normalize(cross(right, forward));
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
    m[2][3] = 0;
    m[3][0] = -dot(cam->origin, right);
    m[3][1] = -dot(cam->origin, up);
    m[3][2] = -dot(cam->origin, forward);
    m[3][3] = 1;
    return (m);
}

quat normalize_quat(quat q)
{
    float length = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    if (length != 0.0f)
        q /= length;
    return q;
}

quat    multiply_quat(quat q1, quat q2)
{
    quat    result;

    result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    return (result);
}

// Function to create a rotation quat from an angle (in radians) and an axis
quat angleAxis(float angle, vec4 axis) {
    quat result;

    // Normalize the axis
    axis = v4_normalize(axis);

    // Calculate half angle
    float halfAngle = angle * 0.5f;

    // Calculate sine and cosine of the half angle
    float sinHalfAngle = sin(halfAngle);
    float cosHalfAngle = cos(halfAngle);

    // Set the quat components
    result.x = axis.x * sinHalfAngle;
    result.y = axis.y * sinHalfAngle;
    result.z = axis.z * sinHalfAngle;
    result.w = cosHalfAngle;

    return (result);
}

// Function to rotate a 3D vector using a quat
vec4    rotate(vec4 v, quat rotationQuat) {
    // Convert the vector to a quat
    quat vectorQuat = {v.x, v.y, v.z, 0.0f};

    // Perform the rotation: qvq*
    quat resultQuat = multiply_quat(
        multiply_quat(rotationQuat, vectorQuat),
        normalize_quat((quat){-rotationQuat.x, -rotationQuat.y, -rotationQuat.z, rotationQuat.w})
    );

    // Extract the rotated vector from the quat
    vec4 result = vector4(resultQuat.x, resultQuat.y, resultQuat.z, 1);
    result = v4_normalize(result);
    return (result);
}