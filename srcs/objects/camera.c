#include "minirt.h"

void	view_matrix(Camera *camera, Vector direction) {
	camera->up = vector(0, 1, 0);
	camera->direction = normalize(direction);
	camera->right = normalize(cross(camera->direction, camera->up));
	camera->up = normalize(cross(camera->right, camera->direction));
	
	camera->view[0][0] = camera->right.x;
	camera->view[0][1] = camera->up.x;
	camera->view[0][2] = camera->direction.x;
	camera->view[0][3] = 0;
	camera->view[1][0] = camera->right.y;
	camera->view[1][1] = camera->up.y;
	camera->view[1][2] = camera->direction.y;
	camera->view[1][3] = 0;
	camera->view[2][0] = camera->right.z;
	camera->view[2][1] = camera->up.z;
	camera->view[2][2] = camera->direction.z;
	camera->view[2][3] = 0;
	camera->view[3][0] = -dot(camera->origin, camera->right);
	camera->view[3][1] = -dot(camera->origin, camera->up);
	camera->view[3][2] = -dot(camera->origin, camera->direction);
	camera->view[3][3] = 1;
}

void	projection_matrix(Camera *camera, int near, int far, int fov) {
	Scene	*scene;

	scene = get_scene();
	if (!scene) {
		return ;
    }

	camera->proj[0][0] = 1.0 / (WIDTH / HEIGHT * tan(radian(fov / 2)));
	camera->proj[0][1] = 0.0;
	camera->proj[0][2] = 0.0;
	camera->proj[0][3] = 0.0;
	camera->proj[1][0] = 0.0;
	camera->proj[1][1] = 1.0 / tan(radian(fov / 2));
	camera->proj[1][2] = 0.0;
	camera->proj[1][3] = 0.0;
	camera->proj[2][0] = 0.0;
	camera->proj[2][1] = 0.0;
	camera->proj[2][2] = -(far + near) / (far - near);
	camera->proj[2][3] = -1.0;
	camera->proj[3][0] = 0.0;
	camera->proj[3][1] = 0.0;
	camera->proj[3][2] = -(2 * far * near) / (far - near);
	camera->proj[3][3] = 0.0;
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
    
	if (!atovector(args[2], &camera->direction)) {
        free(camera);
        return (0);
    }

	camera->direction = normalize(camera->direction);
	camera->fov = ft_atof(args[3], &tmp);
    camera->near = 1;
    camera->far = 100;
	camera->pitch = 0.;
	camera->yaw = 0.;
    
    projection_matrix(camera, camera->near, camera->far, camera->fov);
	view_matrix(camera, camera->direction);

	camera->iview = mat_inverse(camera->view);
	camera->iproj = mat_inverse(camera->proj);

    if (!check_camera(camera)) {
        free(camera);
		return (0);
    }

	calculate_rays(camera);

    scene->camera = camera;
	return (1);
}

