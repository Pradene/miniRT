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

typedef float	t_vec2 __attribute__((ext_vector_type(2)));
typedef float	t_vec3 __attribute__((ext_vector_type(3)));
typedef float	t_vec4 __attribute__((ext_vector_type(4)));
typedef float	t_quat __attribute__((ext_vector_type(4)));

t_vec2	vector2(float x, float y);
t_vec3	vector3(float x, float y, float z);
t_vec4	vector4(float x, float y, float z, float w);
float	dot(const t_vec3 v1, const t_vec3 v2);
t_vec3	cross(const t_vec3 v1, const t_vec3 v2);

t_vec3	normalize(const t_vec3 v);

int		atovec3(char *s, t_vec3 *v);
t_vec3	atov3(char *s);

#endif
