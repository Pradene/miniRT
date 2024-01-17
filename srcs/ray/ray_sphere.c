/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:40:36 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:42:01 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_hit	ray_sphere_intersection(t_obj *obj, t_ray r)
{
	t_vec4	d;
	t_hit	h;
	t_vec3	tmp;

	tmp = r.origin - obj->origin;
	d.x = dot(r.direction, r.direction);
	d.y = 2 * dot(tmp, r.direction);
	d.z = dot(tmp, tmp) - powf(obj->diameter / 2, 2.0);
	d.w = d.y * d.y - 4.0 * d.x * d.z;
	if (d.w < 0.0)
		return (miss_ray());
	if ((-d.y + sqrt(d.w)) / (2.0 * d.x) < 0)
		return (miss_ray());
	h.distance = (-d.y - sqrt(d.w)) / (2.0 * d.x);
	if (h.distance < 0)
		h.distance = (-d.y + sqrt(d.w)) / (2.0 * d.x);
	h.object = obj;
	h.normal = normalize(tmp + r.direction * h.distance);
	h.w_position = obj->origin + tmp + r.direction * h.distance;
	return (h);
}
