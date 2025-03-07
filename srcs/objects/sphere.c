#include "minirt.h"

Hit	sphere_intersection(Object *object, Ray r) {
	Hit	    h;
	Vector	ray;
	float	a;
	float	b;
	float	c;
	float	d;

	ray = r.origin - object->origin;
	a = dot(r.direction, r.direction);
	b = 2 * dot(ray, r.direction);
	c = dot(ray, ray) - powf(object->sphere.radius, 2.0);
	d = b * b - 4.0 * a * c;
	if (d < 0.0) {
		return (miss_ray());
    }

	if ((-b + sqrt(d)) / (2.0 * a) < 0) {
		return (miss_ray());
    }

	h.distance = (-b - sqrt(d)) / (2.0 * a);
	if (h.distance < 0) {
		h.distance = (-b + sqrt(d)) / (2.0 * a);
    }

	h.object = object;
	h.normal = normalize(ray + r.direction * h.distance);
	if ((-b - sqrt(d)) / (2.0 * a) < 0) {
        h.normal *= -1;
    }
    
	h.position = object->origin + ray + r.direction * h.distance;
	return (h);
}

int	sphere(Scene *scene, char **args) {
	Object  *object;
	char	*tmp;

	if (size_strings(args) != 4) {
		return (0);
    }

	object = malloc(sizeof(Object));
	if (!object) {
		return (0);
    }

	object->type = SPHERE;
	if (!atopoint(args[1], &object->origin)) {
		return (free(object), 0);
    }

	object->sphere.radius = ft_atof(args[2], &tmp);
	if (tmp != args[2] + ft_strlen(args[2])) {
		return (free(object), 0);
    }

	object->material.color = atocolor(args[3]);
	
	if (!check_sphere(object)) {
		free(object);
		return (0);
	}

	if (add_object(scene, object)) {
		free_scene();
		return (0);
	}
	
	return (1);
}
