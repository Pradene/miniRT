/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:49:25 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:51:21 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

// Init a vector
t_vec2	vector2(float x, float y)
{
	t_vec2	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec3	vector3(float x, float y, float z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec4	vector4(float x, float y, float z, float w)
{
	t_vec4	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}
