#include "minirt.h"

Hit	plane_intersection(Object *obj, Ray r) {
	float	denom;
	Hit 	h;
	Vector	tmp;

	denom = dot(obj->rotation, r.direction);
	if (fabsf(denom) > 0.0001) {
		tmp = obj->origin - r.origin;
		h.object = obj;
		h.distance = dot(tmp, obj->rotation) / denom;
		h.position = r.origin + r.direction * h.distance;
		h.normal = obj->rotation;
		if (denom > 0.0001) {
			h.normal *= -1;
        }

		return (h);
	}

	return (miss_ray());
}

int	plane(Scene *scene, char **args) {
	Object	*object;

	if (size_strings(args) != 4) {
		return (0);
    }

	object = malloc(sizeof(Object));
	if (!object) {
		return (0);
    }

	object->type = PLANE;
	if (!atopoint(args[1], &object->origin)) {
		free(object);
        return (0);
    }

	if (!atovector(args[2], &object->rotation)) {
		free(object);
        return (0);
    }
    object->rotation = normalize(object->rotation);

	object->material.color = atocolor(args[3]);
	if (!check_plane(object)) {
		free(object);
        return (0);
    }

	if (add_object(scene, object)) {
		free_scene();
		return (0);
	}

	return (1);
}
