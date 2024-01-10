/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:51 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:00:50 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "objects.h"

typedef struct s_ray
{
	vec3	origin;
	vec3	direction;
}	t_ray;

t_hit	miss_ray(void);

t_hit	ray_plane_intersection(t_obj *obj, t_ray r);
t_hit	ray_sphere_intersection(t_obj *obj, t_ray r);
t_hit	ray_cylinder_intersection(t_obj *obj, t_ray r);

rgba	intersect(t_ray r);
t_hit	ray_hit(t_ray r);

#endif
