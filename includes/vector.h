#ifndef VECTOR_H
# define VECTOR_H

#include <stdbool.h>

typedef float vec4 __attribute__((ext_vector_type(4)));

vec4   vector4(float x, float y, float z, float w);
float  vector_dot(vec4 v1, vec4 v2);
vec4   vector_cross(vec4 v1, vec4 v2);

void   vector_normalize(vec4 *v);

vec4   atov4(char *s, bool vector);

#endif