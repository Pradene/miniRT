#include "minirt.h"

int	check_irange(int value, int min, int max) {
	return (min <= value && value <= max);
}

int	check_frange(float value, float min, float max) {
	return (min <= value && value <= max);
}

int	check_color(Color color) {
	return (
        check_frange(color.r, 0.0, 1.0) &&
        check_frange(color.g, 0.0, 1.0) &&
        check_frange(color.b, 0.0, 1.0) &&
        check_frange(color.a, 0.0, 1.0)
    );
}

int	check_sphere(Object *obj) {
	return (obj->sphere.radius > 0.);
}

int	check_rotation(Vector direction) {
	return (
        check_frange(direction.x, -1.0, 1.0) &&
        check_frange(direction.y, -1.0, 1.0) &&
        check_frange(direction.z, -1.0, 1.0)
    );
}

int	check_camera(Camera *camera) {
	return (check_frange(camera->fov, 0.0f, 180.0f) && check_rotation(camera->direction));
}

int	check_intensity(float intensity) {
	return (check_frange(intensity, 0.0, 1.0));
}

int	check_light(Light light) {
	return (check_color(light.color) && check_intensity(light.intensity));
}

int	check_ambient(AmbientLight light) {
	return (check_color(light.color) && check_intensity(light.intensity));
}

int	check_cylinder(Object *object) {
	return (
        check_color(object->material.color) &&
        check_rotation(object->rotation) &&
        object->cylinder.height > 0 &&
        object->cylinder.radius > 0
    );
}

int	check_plane(Object *object) {
	return (check_color(object->material.color) && check_rotation(object->rotation));
}