#include "minirt.h"

Vector	direction(Camera *camera) {
	Vector v = normalize(vector(
		cosf(camera->yaw) * cosf(camera->pitch),
		sinf(camera->pitch),
		sinf(camera->yaw) * cosf(camera->pitch)
	));

	return (v);
}

Matrix4	view_matrix(Point from, Point to, Vector up) {
	Matrix4	view;

	Vector forward = normalize(to - from);
	Vector right = normalize(cross(forward, up));
	up = normalize(cross(right, forward));
	
	view[0][0] = right.x;
	view[0][1] = up.x;
	view[0][2] = forward.x;
	view[0][3] = 0;
	view[1][0] = right.y;
	view[1][1] = up.y;
	view[1][2] = forward.y;
	view[1][3] = 0;
	view[2][0] = right.z;
	view[2][1] = up.z;
	view[2][2] = forward.z;
	view[2][3] = 0;
	view[3][0] = -dot(from, right);
	view[3][1] = -dot(from, up);
	view[3][2] = -dot(from, forward);
	view[3][3] = 1;

	return (view);
}

Matrix4	projection_matrix(int near, int far, int fov) {
	Matrix4	proj;

	proj[0][0] = 1.0 / (WIDTH / HEIGHT * tanf(radian(fov / 2)));
	proj[0][1] = 0.0;
	proj[0][2] = 0.0;
	proj[0][3] = 0.0;
	proj[1][0] = 0.0;
	proj[1][1] = 1.0 / tanf(radian(fov / 2));
	proj[1][2] = 0.0;
	proj[1][3] = 0.0;
	proj[2][0] = 0.0;
	proj[2][1] = 0.0;
	proj[2][2] = -(far + near) / (far - near);
	proj[2][3] = -1.0;
	proj[3][0] = 0.0;
	proj[3][1] = 0.0;
	proj[3][2] = -(2 * far * near) / (far - near);
	proj[3][3] = 0.0;

	return (proj);
}

void	calculate_rays(Camera *camera) {
	int		i;
	float	x;
	float	y;
	Vector	tmp;
	Vector	r;

	i = -1;
	while (++i < HEIGHT * WIDTH) {
		x = map(i % WIDTH + 0.5, 0, WIDTH, -1, 1);
		y = map(i / WIDTH + 0.5, 0, HEIGHT, -1, 1);
		tmp = mat_vec_product(camera->iproj, point(x, y, 1));
		r = normalize(tmp / tmp.w);
		tmp = mat_vec_product(camera->iview, r);

		camera->ray_direction[i] = tmp;
	}
}

int	camera(Scene *scene, char **args) {
	Camera	*camera;
	char	*tmp;

    camera = NULL;
	if (size_strings(args) != 4) {
		return (0);
    }

	if (scene->camera) {
        return (0);
    }

    camera = malloc(sizeof(Camera));
    if (!camera) {
        return (0);
    }

	if (!atopoint(args[1], &camera->origin)) {
        free(camera);
        return (0);
    }
    
	Vector	v;
	if (!atovector(args[2], &v)) {
        free(camera);
        return (0);
    }

	camera->fov = ft_atof(args[3], &tmp);
    camera->near = 1;
    camera->far = 100;

	camera->pitch = asin(v.y);
  	camera->yaw = atan2(v.z, v.x);
    
    camera->proj = projection_matrix(camera->near, camera->far, camera->fov);
	camera->iproj = mat_inverse(camera->proj);

	camera->view = view_matrix(
		camera->origin,
		camera->origin + direction(camera),
		vector(0, 1, 0)
	);
	camera->iview = mat_inverse(camera->view);

    if (!check_camera(camera)) {
        free(camera);
		return (0);
    }

	calculate_rays(camera);

    scene->camera = camera;
	return (1);
}

