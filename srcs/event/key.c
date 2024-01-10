/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:40:32 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 11:40:36 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

#define MOVEMENT_SPEED 0.002

int	key(int key, t_data *data)
{
	float	x;
	vec3	right;
	vec3	up;
	vec3	forward;
	quat	q;
	bool	r;

	up = vector3(0, 1, 0);
	forward = normalize(data->camera.direction);
	right = normalize(cross(forward, up));
	up = normalize(cross(right, forward));
	if (key == 65307)
		free_data();
	else if (key == 65361)
	{
		data->camera.origin += right * data->et * MOVEMENT_SPEED;
		calculate_m_view(&data->camera);
	}
	else if (key == 65363)
	{
		data->camera.origin -= right * data->et * MOVEMENT_SPEED;
		calculate_m_view(&data->camera);
	}
	else if (key == 65362)
	{
		data->camera.origin += forward * data->et * MOVEMENT_SPEED;
		calculate_m_view(&data->camera);
	}
	else if (key == 65364)
	{
		data->camera.origin -= forward * data->et * MOVEMENT_SPEED;
		calculate_m_view(&data->camera);
	}
	else if (key == 45)
	{
		data->camera.origin -= up * data->et * MOVEMENT_SPEED;
		calculate_m_view(&data->camera);
	}
	else if (key == 61)
	{
		data->camera.origin += up * data->et * MOVEMENT_SPEED;
		calculate_m_view(&data->camera);
	}
	x = 0;
	r = false;
	if (key == 97)
	{
		r = true;
		x += -1;
	}
	else if (key == 100)
	{
		r = true;
		x += 1;
	}
	if (r)
	{
		q = angle_axis(radian(x), vector3(0, 1, 0));
		q = normalize_quat(q);
		data->camera.direction = rotate(data->camera.direction, q);
		calculate_m_view(&data->camera);
		calculate_rays(&data->camera);
	}
	return (0);
}
