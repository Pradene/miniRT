#ifndef VECTOR_H
# define VECTOR_H

#include <stdbool.h>

typedef float vec2 __attribute__((ext_vector_type(2)));
typedef float vec3 __attribute__((ext_vector_type(3)));
typedef float vec4 __attribute__((ext_vector_type(4)));
typedef float quat __attribute__((ext_vector_type(4)));


vec2    vector2(float x, float y);
vec4    vector4(float x, float y, float z, float w);
float   dot(const vec4 v1, const vec4 v2);
vec4    cross(const vec4 v1, const vec4 v2);

vec4    v4_normalize(const vec4 v);

vec4    atov4(char *s, bool vector);

#endif