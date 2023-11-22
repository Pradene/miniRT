#include "../../includes/rt.h"

#define MOVEMENT_SPEED 0.002

int	key(int key, t_data *data)
{
	vec4   right;
    vec4   up;
    vec4   forward;

	forward = data->camera.direction;
	right = vector_cross(vector4(0, 1, 0, 1), forward);
    vector_normalize(&right);
    up = vector_cross(forward, right);
    vector_normalize(&up);

	printf("%d\n", key);
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
	return (0);
}