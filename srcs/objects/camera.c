/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:46:41 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:06:27 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	calculate_rays(t_camera *cam)
{
	int		i;
	float	x;
	float	y;
	vec4	tmp;
	vec3	r;

	i = -1;
	while (++i < HEIGHT * WIDTH)
	{
		x = map(i % WIDTH + 0.5, vector2(0, WIDTH), vector2(-1, 1));
		y = map(i / WIDTH + 0.5, vector2(0, HEIGHT), vector2(-1, 1));
		tmp = mat_vec_product(cam->m_inverse_projection, vector4(x, y, 1, 1));
		r = normalize(tmp.xyz / tmp.w);
		tmp = mat_vec_product(cam->m_inverse_view, vector4(r.x, r.y, r.z, 0));
		r = tmp.xyz;
		cam->ray_direction[i] = r;
	}
}

void	view_matrix(t_camera *cam, vec3 forward)
{
	vec3	right;
	vec3	up;

	up = vector3(0, 1, 0);
	forward = normalize(forward);
	right = normalize(cross(forward, up));
	up = normalize(cross(right, forward));
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

void	calculate_m_view(t_camera *cam)
{
	view_matrix(cam, cam->direction);
	cam->m_inverse_view = mat_inverse(cam->m_view);
}

void	projection_matrix(t_camera *cam, int near, int far, int fov)
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

int	check_camera(t_camera *camera)
{
	if (!check_fov(camera->fov) || !check_direction(camera->direction))
		return (0);
	return (1);
}

int	camera(char **args)
{
	t_data		*data;
	t_camera	*cam;
	char		*tmp;

	data = get_data();
	cam = &data->camera;
	if (string_array_size(args) != 4)
		return (0);
	if (data->camera.created)
		return (0);
	cam->origin = atov3(args[1]);
	cam->direction = atov3(args[2]);
	cam->direction = normalize(cam->direction);
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

void	quaternion_to_matrix(quat q, mat44 *m)
{
	q = normalize_quat(q);
	(*m)[0][0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	(*m)[0][1] = 2.0f * (q.x * q.y - q.z * q.w);
	(*m)[0][2] = 2.0f * (q.x * q.z + q.y * q.w);
	(*m)[0][3] = 0.0f;
	(*m)[1][0] = 2.0f * (q.x * q.y + q.z * q.w);
	(*m)[1][1] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
	(*m)[1][2] = 2.0f * (q.y * q.z - q.x * q.w);
	(*m)[1][3] = 0.0f;
	(*m)[2][0] = 2.0f * (q.x * q.z - q.y * q.w);
	(*m)[2][1] = 2.0f * (q.y * q.z + q.x * q.w);
	(*m)[2][2] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
	(*m)[2][3] = 0.0f;
	(*m)[3][0] = 0.0f;
	(*m)[3][1] = 0.0f;
	(*m)[3][2] = 0.0f;
	(*m)[3][3] = 1.0f;
}

mat44	translate(t_camera *cam)
{
	mat44	m;
	vec3	up;
	vec3	right;
	vec3	forward;

	m = mat();
	up = vector3(0, 1, 0);
	forward = normalize(cam->direction);
	right = normalize(cross(forward, up));
	up = normalize(cross(right, forward));
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

quat	normalize_quat(quat q)
{
	float	length;

	length = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if (length != 0.0f)
		q /= length;
	return (q);
}

quat	multiply_quat(quat q1, quat q2)
{
	quat	result;

	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return (result);
}

// Function to create a rotation quat from an angle (in radians) and an axis
quat	angle_axis(float angle, vec3 axis)
{
	quat	result;

	axis = normalize(axis);
	result.x = axis.x * sin(angle * 0.5);
	result.y = axis.y * sin(angle * 0.5);
	result.z = axis.z * sin(angle * 0.5);
	result.w = cos(angle * 0.5);
	return (result);
}

// Function to rotate a 3D vector using a quat
vec3	rotate(vec3 v, quat q)
{
	vec3	result;
	quat	vector_quat;
	quat	result_quat;

	vector_quat.x = v.x;
	vector_quat.y = v.y;
	vector_quat.z = v.z;
	vector_quat.w = 0.0;
	result_quat = multiply_quat(\
		multiply_quat(q, vector_quat), \
		normalize_quat((quat){-q.x, -q.y, -q.z, q.w}));
	result = vector3(result_quat.x, result_quat.y, result_quat.z);
	result = normalize(result);
	return (result);
}
