/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:49:15 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:50:17 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

// Normalize a vector (sum of x, y, z equal 1)
vec3	normalize(const vec3 v)
{
	float	magnitude;
	float	d;
	vec3	res;

	d = dot(v, v);
	magnitude = sqrt(d);
	if (magnitude == 0)
		return (v);
	res = v / magnitude;
	return (res);
}
