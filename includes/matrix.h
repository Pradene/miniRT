#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef float mat44 __attribute__((matrix_type(4, 4)));
typedef float mat33 __attribute__((matrix_type(3, 3)));

void    mat_print(mat44 m);
void    mat(mat44 *m);

bool    mat_inverse(mat44 m, mat44 *inv);

vec4    mat_vec_product(mat44 m, vec4 v);

#endif