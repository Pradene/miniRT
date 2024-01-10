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

typedef float	mat44 __attribute__((matrix_type(4, 4)));
typedef float	mat33 __attribute__((matrix_type(3, 3)));

mat44	mat(void);
mat44	mat_copy(mat44 m);
void	mat_print(mat44 m);
vec4	mat_vec_product(mat44 m, vec4 v);
mat44	mat_product(mat44 m, mat44 n);

mat44	mat_inverse(mat44 m);

#endif
