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

// static void update_vectors(Camera *camera) {
//     camera->direction.x = cosf(radian(camera->yaw)) * cosf(radian(camera->pitch));
//     camera->direction.y = sinf(radian(camera->pitch));
//     camera->direction.z = sinf(radian(camera->yaw)) * cosf(radian(camera->pitch));
//     camera->direction = normalize(camera->direction);

//     Vector up = vector(0., 1., 0.);
//     camera->right = normalize(cross(camera->direction, up));

//     camera->up = normalize(cross(camera->right, camera->direction));
// }

int rotate(Scene *scene, int key) {
    (void)scene;
    (void)key;

	return (0);


    // if (key != R_UP && key != R_DOWN && key != R_RIGHT && key != R_LEFT) {
	// 	return (0);
    // }

    // if (key == R_LEFT) {
    //     scene->camera->yaw += 1.;
    // } else if (key == R_RIGHT) {
    //     scene->camera->yaw -= 1.;
    // } else if (key == R_UP) {
    //     scene->camera->pitch += 1.;
    // } else if (key == R_DOWN) {
    //     scene->camera->pitch -= 1.;
    // }

    // if (scene->camera->pitch >= 90.0f) scene->camera->pitch = 90.0f;
    // if (scene->camera->pitch <= -90.0f) scene->camera->pitch = -90.0f;

    // update_vectors(scene->camera);

    // view_matrix(
    //     scene->camera, 
    //     scene->camera->direction
    // );
    // scene->camera->iview = mat_inverse(scene->camera->view);
    
    // calculate_rays(scene->camera);

    // return (1);
}

int	move(Scene *scene, int key) {
	Vector	right;
	Vector	up;
	Vector	direction;

	up = vector(0, 1, 0);
	direction = normalize(scene->camera->direction);
	right = normalize(cross(direction, up));
	up = normalize(cross(right, direction));
	if (key != UP && key != DOWN && key != RIGHT && key != LEFT && key != FORWARD && key != BACKWARD) {
		return (0);
    }

	if (key == RIGHT) {
		scene->camera->origin += right * scene->elapsed * MOVEMENT_SPEED;

    } else if (key == LEFT) {
		scene->camera->origin -= right * scene->elapsed * MOVEMENT_SPEED;

    } else if (key == FORWARD) {
        scene->camera->origin += direction * scene->elapsed * MOVEMENT_SPEED;

    } else if (key == BACKWARD) {
        scene->camera->origin -= direction * scene->elapsed * MOVEMENT_SPEED;

    } else if (key == DOWN) {
        scene->camera->origin -= up * scene->elapsed * MOVEMENT_SPEED;

    } else if (key == UP) {
        scene->camera->origin += up * scene->elapsed * MOVEMENT_SPEED;

    }

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