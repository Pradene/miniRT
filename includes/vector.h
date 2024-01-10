/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:57:20 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:06:15 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>

typedef float	vec2 __attribute__((ext_vector_type(2)));
typedef float	vec3 __attribute__((ext_vector_type(3)));
typedef float	vec4 __attribute__((ext_vector_type(4)));
typedef float	quat __attribute__((ext_vector_type(4)));

vec2	vector2(float x, float y);
vec3	vector3(float x, float y, float z);
vec4	vector4(float x, float y, float z, float w);
float	dot(const vec3 v1, const vec3 v2);
vec3	cross(const vec3 v1, const vec3 v2);

vec3	normalize(const vec3 v);

vec3	atov3(char *s);

#endif
