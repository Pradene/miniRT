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

void	view_matrix(t_camera *cam, t_vec3 forward)
{
	t_vec3	right;
	t_vec3	up;

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
	t_data	*data;

	data = get_data();
	if (!data)
		return ;
	cam->m_projection[0][0] = 1.0 / (data->aspect_ratio * tan(radian(fov / 2)));
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
	if (!check_irange(camera->fov, 0, 180) \
	|| !check_rotation(camera->direction))
		return (0);
	return (1);
}

int	camera(t_data *data, char **args)
{
	t_camera	*cam;
	char		*tmp;

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
