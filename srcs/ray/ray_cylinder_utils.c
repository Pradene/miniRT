/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:19 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/18 17:11:19 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_vec4	cylinder_discriminant(t_obj *obj, t_ray r)
{
	t_vec4	result;
	t_vec3	tmp1;
	t_vec3	tmp2;

	tmp1 = r.direction - dot(r.direction, obj->rotation) * obj->rotation;
	tmp2 = r.origin - obj->origin \
	- dot(r.origin - obj->origin, obj->rotation) * obj->rotation;
	result.x = dot(tmp1, tmp1);
	result.y = 2 * dot(tmp1, tmp2);
	result.z = dot(tmp2, tmp2) - powf(obj->diameter / 2, 2.0);
	result.w = result.y * result.y - 4 * result.z * result.x;
	return (result);
}

t_hit	ray_cap_intersection(t_obj *obj, t_ray r, t_vec3 offset)
{
	t_hit	h;
	t_vec3	origin;
	float	denom;

	denom = dot(obj->rotation, r.direction);
	if (fabsf(denom) > 0.0001)
	{
		origin = (obj->origin + offset) - r.origin;
		h.object = obj;
		h.distance = dot(origin, obj->rotation) / denom;
		h.w_position = r.origin + r.direction * h.distance;
		h.normal = obj->rotation;
		origin += r.origin;
		if (denom > 0.0001)
			h.normal *= -1;
		if (dot(h.w_position - origin, h.w_position - origin) \
		< powf(obj->diameter / 2, 2.0))
			return (h);
	}
	return (miss_ray());
}

t_hit	ray_caps_intersection(t_obj *obj, t_ray r)
{
	t_hit	h1;
	t_hit	h2;

	h1 = ray_cap_intersection(obj, r, (obj->rotation * obj->height / 2));
	h2 = ray_cap_intersection(obj, r, -(obj->rotation * obj->height / 2));
	if (h1.distance > 0 && (h1.distance < h2.distance || h2.distance < 0))
		return (h1);
	if (h2.distance > 0 && (h2.distance < h1.distance || h1.distance < 0))
		return (h2);
	return (miss_ray());
}

t_hit	ray_curve_intersection(t_obj *obj, t_ray r, float t)
{
	t_hit	h;
	t_vec3	hit_pos;
	t_vec3	offset;

	offset = obj->rotation * obj->height / 2;
	hit_pos = r.origin + r.direction * t;
	if (dot(obj->rotation, hit_pos - (obj->origin - offset)) > 0 \
	&& dot(obj->rotation, hit_pos - (obj->origin + offset)) < 0)
	{
		h.w_position = r.origin + r.direction * t;
		h.distance = t;
		h.object = obj;
		h.normal = dot(h.w_position - obj->origin, obj->rotation) \
		* obj->rotation;
		h.normal = normalize(h.w_position - obj->origin - h.normal);
		return (h);
	}
	return (miss_ray());
}

t_hit	ray_curves_intersection(t_obj *obj, t_ray r)
{
	t_hit	h1;
	t_hit	h2;
	t_vec4	d;
	float	t;

	d = cylinder_discriminant(obj, r);
	if (d.w < 0)
		return (miss_ray());
	t = (-d.y - sqrt(d.w)) / (2.0 * d.x);
	h1 = ray_curve_intersection(obj, r, t);
	t = (-d.y + sqrt(d.w)) / (2.0 * d.x);
	h2 = ray_curve_intersection(obj, r, t);
	h2.normal *= -1;
	if (h1.distance > 0 && (h1.distance < h2.distance || h2.distance < 0))
		return (h1);
	if (h2.distance > 0 && (h2.distance < h1.distance || h1.distance < 0))
		return (h2);
	return (miss_ray());
}
