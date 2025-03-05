#include "minirt.h"

Vector	cylinder_discriminant(Object *obj, Ray r)
{
	Vector	result;
	Vector	tmp1;
	Vector	tmp2;

	tmp1 = r.direction - dot(r.direction, obj->rotation) * obj->rotation;
	tmp2 = r.origin - obj->origin - dot(r.origin - obj->origin, obj->rotation) * obj->rotation;
	result.x = dot(tmp1, tmp1);
	result.y = 2 * dot(tmp1, tmp2);
	result.z = dot(tmp2, tmp2) - powf(obj->cylinder.radius, 2.0);
	result.w = result.y * result.y - 4 * result.z * result.x;
	return (result);
}

Hit	ray_cap_intersection(Object *obj, Ray r, Vector offset) {
	Hit	    h;
	Vector	origin;
	float	denom;

	denom = dot(obj->rotation, r.direction);
	if (fabsf(denom) > 0.0001) {
		origin = (obj->origin + offset) - r.origin;
		h.object = obj;
		h.distance = dot(origin, obj->rotation) / denom;
		h.position = r.origin + r.direction * h.distance;
		h.normal = obj->rotation;
		origin += r.origin;
		if (denom > 0.0001) {
			h.normal *= -1;
        }

		if (dot(h.position - origin, h.position - origin) < powf(obj->cylinder.radius, 2.0)) {
			return (h);
        }
	}

	return (miss_ray());
}

Hit	ray_caps_intersection(Object *obj, Ray r) {
	Hit	h1;
	Hit	h2;

	h1 = ray_cap_intersection(obj, r, (obj->rotation * obj->cylinder.height / 2));
	h2 = ray_cap_intersection(obj, r, -(obj->rotation * obj->cylinder.height / 2));
	if (h1.distance > 0 && (h1.distance < h2.distance || h2.distance < 0)) {
		return (h1);
    }

	if (h2.distance > 0 && (h2.distance < h1.distance || h1.distance < 0)) {
		return (h2);
    }

	return (miss_ray());
}

Hit	ray_curve_intersection(Object *obj, Ray r, float t) {
	Hit	    h;
	Vector	hit_pos;
	Vector	offset;

	offset = obj->rotation * obj->cylinder.height / 2;
	hit_pos = r.origin + r.direction * t;
	if (dot(obj->rotation, hit_pos - (obj->origin - offset)) > 0 \
	&& dot(obj->rotation, hit_pos - (obj->origin + offset)) < 0)
	{
		h.position = r.origin + r.direction * t;
		h.distance = t;
		h.object = obj;
		h.normal = dot(h.position - obj->origin, obj->rotation) \
		* obj->rotation;
		h.normal = normalize(h.position - obj->origin - h.normal);
		return (h);
	}
	return (miss_ray());
}

Hit	ray_curves_intersection(Object *obj, Ray r) {
	Hit	h1;
	Hit	h2;
	Vector	d;
	float	t;

	d = cylinder_discriminant(obj, r);
	if (d.w < 0) {
		return (miss_ray());
    }

	t = (-d.y - sqrt(d.w)) / (2.0 * d.x);
	h1 = ray_curve_intersection(obj, r, t);
	t = (-d.y + sqrt(d.w)) / (2.0 * d.x);
	h2 = ray_curve_intersection(obj, r, t);
	h2.normal *= -1;
	if (h1.distance > 0 && (h1.distance < h2.distance || h2.distance < 0)) {
		return (h1);
    }

	if (h2.distance > 0 && (h2.distance < h1.distance || h1.distance < 0)) {
        return (h2);
    }
    
	return (miss_ray());
}


Hit cylinder_intersection(Object *obj, Ray r) {
	Hit	h1;
	Hit	h2;

	h1 = ray_curves_intersection(obj, r);
	h2 = ray_caps_intersection(obj, r);
	if (h1.distance > 0 && (h1.distance < h2.distance || h2.distance < 0)) {
		return (h1);
    }

	if (h2.distance > 0 && (h2.distance < h1.distance || h1.distance < 0)) {
		return (h2);
    }

	return (miss_ray());
}

int	cylinder(Scene *scene, char **args) {
	Object	*object;
	char	*tmp;

	if (size_strings(args) != 6) {
		return (0);
    }

	object = malloc(sizeof(Object));
	if (!object) {
		return (0);
    }

	object->type = CYLINDER;
	if (!atopoint(args[1], &object->origin)) {
		free(object);
        return (0);
    }

	if (!atovector(args[2], &object->rotation)) {
		free(object);
        return (0);
    }
    object->rotation = normalize(object->rotation);

	object->cylinder.radius = ft_atof(args[3], &tmp);
	if (tmp != args[3] + ft_strlen(args[3])) {
		free(object);
        return (0);
    }

	object->cylinder.height = ft_atof(args[4], &tmp);
	if (tmp != args[4] + ft_strlen(args[4])) {
		free(object);
        return (0);
    }

	object->material.color = atocolor(args[5]);
	if (!check_cylinder(object)) {
		free(object);
        return (0);
    }

    if (add_object(scene, object)) {
        free(object);
        return (0);
    }

	return (1);
}
