#include "minirt.h"

#define MOVEMENT_SPEED 0.002
#define ROTATION_SPEED 0.02

#define UP 61
#define DOWN 45
#define RIGHT 65361
#define LEFT 65363
#define FORWARD 65362
#define BACKWARD 65364

#define R_LEFT 100
#define R_RIGHT 97
#define R_UP 119
#define R_DOWN 115

int rotate(Scene *scene, int key) {
    Camera *camera = scene->camera;

    float sensitivity = 1.5f;
    float delta = radian(sensitivity);

    if (key == R_LEFT)          camera->yaw -= delta;
    else if (key == R_RIGHT)    camera->yaw += delta;
    else if (key == R_UP)       camera->pitch += delta;
    else if (key == R_DOWN)     camera->pitch -= delta;
    else                        return (0);

    camera->yaw = fmodf(camera->yaw, 2 * PI);
    if (camera->yaw < 0) camera->yaw += 2 * PI;

    camera->pitch = fmaxf(fminf(camera->pitch, PI/2 - 0.01f), -PI/2 + 0.01f);

    Vector dir = direction(camera);
    Point target = camera->origin + dir;
    
    camera->view = view_matrix(camera->origin, target, (Vector){0, 1, 0, 0});
    camera->iview = mat_inverse(camera->view);
    
    calculate_rays(camera);
    return (1);
}

int	move(Scene *scene, int key) {
	Vector	right;
	Vector	up;
	Vector	forward;

	up = vector(0, 1, 0);
	forward = direction(scene->camera);
	right = normalize(cross(forward, up));
	up = normalize(cross(right, forward));

	if (key == RIGHT)           scene->camera->origin += right * scene->elapsed * MOVEMENT_SPEED;
    else if (key == LEFT)       scene->camera->origin -= right * scene->elapsed * MOVEMENT_SPEED;
    else if (key == FORWARD)    scene->camera->origin += forward * scene->elapsed * MOVEMENT_SPEED;
    else if (key == BACKWARD)   scene->camera->origin -= forward * scene->elapsed * MOVEMENT_SPEED;
    else if (key == DOWN)       scene->camera->origin -= up * scene->elapsed * MOVEMENT_SPEED;
    else if (key == UP)         scene->camera->origin += up * scene->elapsed * MOVEMENT_SPEED;
    else                        return (0);

    return (1);
}

int	key(int key, Scene *scene) {

	if (key == 65307) {
        free_scene();
    }

	if (move(scene, key) || rotate(scene, key)) {
        scene->frame = 0;
    }

	return (0);
}