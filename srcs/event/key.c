#include "../../includes/rt.h"

#define MOVEMENT_SPEED 0.002

int	key(int key, t_data *data)
{
	vec4   right;
    vec4   up;
    vec4   forward;

	forward = data->camera.direction;
    right = vector_cross(forward, vector4(0, 1, 0, 1));
    vector_normalize(&right);
    up = vector_cross(right, forward);
    vector_normalize(&up);
	if (key == 65307)
		free_data();
	else if (key == 65361)
	{
		data->camera.origin -= right * data->et * MOVEMENT_SPEED;
		move_camera(&data->camera);
	}
	else if (key == 65363)
	{
		data->camera.origin += right * data->et * MOVEMENT_SPEED;
		move_camera(&data->camera);
	}
	else if (key == 65362)
	{
		data->camera.origin -= up * data->et * MOVEMENT_SPEED;
		move_camera(&data->camera);
	}
	else if (key == 65364)
	{
		data->camera.origin += up * data->et * MOVEMENT_SPEED;
		move_camera(&data->camera);
	}
	else if (key == 45)
	{
		data->camera.origin -= forward * data->et * MOVEMENT_SPEED;
		move_camera(&data->camera);
	}
	else if (key == 61)
	{
		data->camera.origin += forward * data->et * MOVEMENT_SPEED;
		move_camera(&data->camera);
	}

	if (key == 119)
	{
		rotate_camera(&data->camera, -1 * data->et * MOVEMENT_SPEED, 0);
	}
	else if (key == 97)
	{
		rotate_camera(&data->camera, 0, -1 * data->et * MOVEMENT_SPEED);
	}
	else if (key == 115)
	{
		rotate_camera(&data->camera, 1 * data->et * MOVEMENT_SPEED, 0);
	}
	else if (key == 100)
	{
		rotate_camera(&data->camera, 0, 1 * data->et * MOVEMENT_SPEED);
	}
	return (0);
}