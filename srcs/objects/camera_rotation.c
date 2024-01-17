/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:22:45 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:22:46 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_quat	normalize_quat(t_quat q)
{
	float	length;

	length = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if (length != 0.0f)
		q /= length;
	return (q);
}

t_quat	multiply_quat(t_quat q1, t_quat q2)
{
	t_quat	result;

	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return (result);
}

// Function to create a rotation t_quat from an angle (in radians) and an axis
t_quat	angle_axis(float angle, t_vec3 axis)
{
	t_quat	result;

	axis = normalize(axis);
	result.x = axis.x * sin(angle * 0.5);
	result.y = axis.y * sin(angle * 0.5);
	result.z = axis.z * sin(angle * 0.5);
	result.w = cos(angle * 0.5);
	return (result);
}

// Function to rotate a 3D vector using a t_quat
t_vec3	rotate(t_vec3 v, t_quat q)
{
	t_vec3	result;
	t_quat	vector_quat;
	t_quat	result_quat;

	vector_quat.x = v.x;
	vector_quat.y = v.y;
	vector_quat.z = v.z;
	vector_quat.w = 0.0;
	result_quat = multiply_quat(\
		multiply_quat(q, vector_quat), \
		normalize_quat((t_quat){-q.x, -q.y, -q.z, q.w}));
	result = vector3(result_quat.x, result_quat.y, result_quat.z);
	result = normalize(result);
	return (result);
}
