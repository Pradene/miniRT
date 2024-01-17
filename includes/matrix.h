/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:11 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:04:24 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef float	t_mat44 __attribute__((matrix_type(4, 4)));
typedef float	t_mat33 __attribute__((matrix_type(3, 3)));

t_mat44	mat(void);
t_mat44	mat_copy(t_mat44 m);
void	mat_print(t_mat44 m);
t_vec4	mat_vec_product(t_mat44 m, t_vec4 v);
t_mat44	mat_product(t_mat44 m, t_mat44 n);

t_mat44	mat_inverse(t_mat44 m);

float	mat3_determinant(t_mat33 m);
float	cofactor(t_mat44 m, int r, int c);
float	mat4_determinant(t_mat44 m);

#endif
