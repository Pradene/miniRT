/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:28:01 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:28:46 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_rgba	get_color(t_ray ray, t_hit *h)
{
	t_data	*data;
	t_vec3	dir;
	t_rgba	c;
	float	ratio;
	float	d;

	c = color(0, 0, 0, 1);
	if (h->object == NULL)
		return (c);
	data = get_data();
	c = h->object->color;
	ray.origin = h->w_position + h->normal * 0.0001;
	ray.direction = -(ray.origin - data->light.origin);
	ray.direction = normalize(ray.direction);
	d = ray_hit(ray).distance;
	if (d != -1 && d < distance(data->light.origin, ray.origin))
		return (h->object->color * data->alight.brightness);
	dir = -1 * normalize(h->w_position - data->light.origin);
	ratio = fmaxf(0.0, dot(h->normal, dir));
	c = h->object->color * fminf(1.0, ratio + data->alight.brightness);
	return (c);
}

t_hit	miss_ray(void)
{
	t_hit	h;

	h.distance = -1;
	h.object = NULL;
	h.normal = 0;
	h.w_position = 0;
	return (h);
}

t_hit	ray_hit(t_ray r)
{
	t_data		*data;
	t_obj_list	*tmp;
	t_hit		h;
	t_hit		ht;

	data = get_data();
	tmp = data->objects;
	h = miss_ray();
	h.distance = FLT_MAX;
	while (tmp)
	{
		if (tmp->object.type == SPHERE)
			ht = ray_sphere_intersection(&tmp->object, r);
		else if (tmp->object.type == PLANE)
			ht = ray_plane_intersection(&tmp->object, r);
		else if (tmp->object.type == CYLINDER)
			ht = ray_cylinder_intersection(&tmp->object, r);
		if (ht.distance > 0.0 && ht.distance < h.distance)
			h = ht;
		tmp = tmp->next;
	}
	if (h.distance == FLT_MAX)
		h.distance = -1;
	return (h);
}

t_rgba	intersect(t_ray r)
{
	t_hit		h;

	h = ray_hit(r);
	return (get_color(r, &h));
}
