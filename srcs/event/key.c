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
#define ROTATION_SPEED 0.02
#define UP 61
#define DOWN 45
#define RIGHT 65361
#define LEFT 65363
#define FORWARD 65362
#define BACKWARD 65364

void	move(t_data *data, int key, int *moved)
{
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;

	up = vector3(0, 1, 0);
	forward = normalize(data->camera.direction);
	right = normalize(cross(forward, up));
	up = normalize(cross(right, forward));
	if (key != UP && key != DOWN && key != RIGHT && key != LEFT \
	&& key != FORWARD && key != BACKWARD)
		return ;
	(*moved) = 1;
	if (key == RIGHT)
		data->camera.origin += right * data->et * MOVEMENT_SPEED;
	else if (key == LEFT)
		data->camera.origin -= right * data->et * MOVEMENT_SPEED;
	else if (key == FORWARD)
		data->camera.origin += forward * data->et * MOVEMENT_SPEED;
	else if (key == BACKWARD)
		data->camera.origin -= forward * data->et * MOVEMENT_SPEED;
	else if (key == DOWN)
		data->camera.origin -= up * data->et * MOVEMENT_SPEED;
	else if (key == UP)
		data->camera.origin += up * data->et * MOVEMENT_SPEED;
}

int	rotate_view(t_data *data, int key, int *rotated)
{
	float	angle;

	angle = 0.0;
	if (key != 97 && key != 100)
		return (angle);
	(*rotated) = 1;
	if (key == 97)
		angle = -1 * data->et * ROTATION_SPEED;
	else if (key == 100)
		angle = 1 * data->et * ROTATION_SPEED;
	return (angle);
}

int	key(int key, t_data *data)
{
	t_quat	q;
	float	angle;
	int		rotated;
	int		moved;

	moved = 0;
	rotated = 0;
	data->frame = 0;
	if (key == 65307)
		free_data();
	move(data, key, &moved);
	if (moved)
		calculate_m_view(&data->camera);
	angle = rotate_view(data, key, &rotated);
	if (rotated)
	{
		q = angle_axis(radian(angle), vector3(0, 1, 0));
		q = normalize_quat(q);
		data->camera.direction = rotate(data->camera.direction, q);
		calculate_m_view(&data->camera);
		calculate_rays(&data->camera);
	}
	return (0);
}
