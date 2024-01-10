/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:29:01 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:32:18 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

vec4	discriminant(t_obj *obj, t_ray r)
{
	vec4	result;
	vec3	tmp1;
	vec3	tmp2;

	tmp1 = r.direction - dot(r.direction, obj->rotation) * obj->rotation;
	tmp2 = r.origin - obj->origin \
	- dot(r.origin - obj->origin, obj->rotation) * obj->rotation;
	result.x = dot(tmp1, tmp1);
	result.y = 2 * dot(tmp1, tmp2);
	result.z = dot(tmp2, tmp2) - powf(obj->diameter / 2, 2.0);
	result.w = result.y * result.y - 4 * result.z * result.x;
	return (result);
}

t_hit	ray_cylinder_intersection(t_obj *obj, t_ray r)
{
	t_hit	h;
	vec4	d;
	float	t;
	t_obj	tmp;

	d = discriminant(obj, r);
	if (d.w < 0)
		return (miss_ray());
	t = (-d.y - sqrt(d.w)) / (2.0 * d.x);
	h.w_position = r.origin + r.direction * t;
	if (dot(obj->rotation, h.w_position - (obj->origin - obj->rotation * obj->height / 2)) > 0 \
	&& dot(obj->rotation, h.w_position - (obj->origin + obj->rotation * obj->height / 2)) < 0)
	{
		h.w_position = r.origin + r.direction * t;
		h.distance = t;
		h.object = obj;
		h.normal = dot(h.w_position - obj->origin, obj->rotation) * obj->rotation;
		h.normal = h.w_position - obj->origin - h.normal;
		h.normal = normalize(h.normal);
		return (h);
	}
	tmp = *obj;
	tmp.origin = obj->origin + obj->rotation * obj->height / 2;
	h = ray_plane_intersection(&tmp, r);
	if (dot(h.w_position - tmp.origin, h.w_position - tmp.origin) < powf(obj->diameter / 2, 2.0))
	{
		h.object = obj;
		return (h);
	}
	tmp.origin = obj->origin - obj->rotation * obj->height / 2;
	h = ray_plane_intersection(&tmp, r);
	if (dot(h.w_position - tmp.origin, h.w_position - tmp.origin) < powf(obj->diameter / 2, 2.0))
	{
		h.object = obj;
		return (h);
	}
	return (miss_ray());
}
