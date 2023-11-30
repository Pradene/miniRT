#include "../../includes/rt.h"

#define MOVEMENT_SPEED 0.002

int	key(int key, t_data *data)
{
	float x = 0;
	vec4   right;
    vec4   up;
    vec4   forward;
	quat	q;
	bool	r;

	// printf("%d\n", key);

	up = vector4(0, 1, 0, 1);
	forward = data->camera.direction;
	vector_normalize(&forward);
    right = vector_cross(&forward, &up);
    vector_normalize(&right);
    up = vector_cross(&right, &forward);
    vector_normalize(&up);

	// Movement
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
		float radx = radian(x);
		q = angleAxis(radx, vector4(0, 1, 0, 1));
		q = normalize_quat(q);

		data->camera.direction = rotate(data->camera.direction, q);

    	view_matrix(&data->camera, data->camera.direction);
    	mat_inverse(data->camera.m_view, &data->camera.m_inverse_view);
    	calculate_rays(&data->camera);
	}
	
	return (0);
}