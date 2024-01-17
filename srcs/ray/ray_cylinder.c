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

t_vec4	discriminant(t_obj *obj, t_ray r)
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

int	ray_curved_interscetion(t_obj *obj, t_hit h)
{
	t_vec3	v;

	v = obj->rotation * obj->height / 2;
	if (dot(obj->rotation, h.w_position - (obj->origin - v)) > 0 \
	&& dot(obj->rotation, h.w_position - (obj->origin + v)) < 0)
		return (1);
	return (0);
}

int	ray_caps_intersection(t_obj obj, t_ray r, t_hit *h)
{
	t_vec3	half_h;
	t_vec3	origin;

	origin = obj.origin;
	half_h = obj.rotation * obj.height / 2;
	obj.origin = origin + half_h;
	*h = ray_plane_intersection(&obj, r);
	if (dot(h->w_position - obj.origin, h->w_position - obj.origin) \
	< powf(obj.diameter / 2, 2.0))
		return (1);
	obj.origin = origin - half_h;
	*h = ray_plane_intersection(&obj, r);
	if (dot(h->w_position - obj.origin, h->w_position - obj.origin) \
	< powf(obj.diameter / 2, 2.0))
		return (1);
	return (0);
}

t_hit	ray_cylinder_intersection(t_obj *obj, t_ray r)
{
	t_hit	h;
	t_vec4	d;
	float	t;

	d = discriminant(obj, r);
	if (d.w < 0)
		return (miss_ray());
	t = (-d.y - sqrt(d.w)) / (2.0 * d.x);
	h.w_position = r.origin + r.direction * t;
	if (ray_curved_interscetion(obj, h))
	{
		h.w_position = r.origin + r.direction * t;
		h.distance = t;
		h.object = obj;
		h.normal = dot(h.w_position - obj->origin, obj->rotation) \
		* obj->rotation;
		h.normal = normalize(h.w_position - obj->origin - h.normal);
		return (h);
	}
	if (ray_caps_intersection(*obj, r, &h))
	{
		h.object = obj;
		return (h);
	}
	return (miss_ray());
}
