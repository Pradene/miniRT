#include "minirt.h"

Color	get_color(Ray ray, Hit *h) {
	Scene	*scene;
	Vector	direction;
	Color	c;
	float	ratio;
	float	t;

	c = color(0, 0, 0, 1);
	if (h->object == NULL) {
		return (c);
    }

	scene = get_scene();
	c = h->object->material.color;
	ray.origin = h->position + h->normal * 0.0001;
	ray.direction = -(ray.origin - scene->light->origin);
	ray.direction = normalize(ray.direction);
	t = ray_hit(ray).distance;
	if (t != -1 && t < distance(scene->light->origin, ray.origin)) {
		return (h->object->material.color * scene->ambient->intensity);
    }

	direction = -1 * normalize(h->position - scene->light->origin);
	ratio = fmaxf(0.0, dot(h->normal, direction));
	c = h->object->material.color * fminf(1.0, ratio + scene->ambient->intensity);
	return (c);
}

Hit	miss_ray(void) {
	Hit	h;

	h.distance = -1;
	h.object = NULL;
	h.normal = vector(0., 0., 0.);
	h.position = point(0., 0., 0.);
	return (h);
}

Hit	ray_hit(Ray r) {
	Scene		*scene;
	Hit		    h;
	Hit		    ht;
    int         i;

	scene = get_scene();

	h = miss_ray();
	h.distance = FLT_MAX;

    i = -1;
	while ((size_t)++i < scene->count) {
		if (scene->objects[i]->type == SPHERE) {
			ht = sphere_intersection(scene->objects[i], r);
        } else if (scene->objects[i]->type == CYLINDER) {
			ht = cylinder_intersection(scene->objects[i], r);
        } else if (scene->objects[i]->type == PLANE) {
			ht = plane_intersection(scene->objects[i], r);
        }

		if (ht.distance > 0.0 && ht.distance < h.distance) {
			h = ht;
        }
	}

	if (h.distance == FLT_MAX) {
		h.distance = -1;
    }

	return (h);
}

Color	intersect(Ray r) {
	Hit		h;

	h = ray_hit(r);
	return (get_color(r, &h));
}