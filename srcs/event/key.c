#include "../../includes/rt.h"

#define MOVEMENT_SPEED 0.002

int	key(int key, t_data *data)
{
	float	x = 0;
	vec4    right;
    vec4    up;
    vec4    forward;
	quat	q;
	bool	r;

	// printf("%d\n", key);

	up = vector4(0, 1, 0, 1);
	forward = v4_normalize(data->camera.direction);
    right = v4_normalize(cross(forward, up));
    up = v4_normalize(cross(right, forward));

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

		calculate_m_view(&data->camera);
    	calculate_rays(&data->camera);
	}
	
	return (0);
}