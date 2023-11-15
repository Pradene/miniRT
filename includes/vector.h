#ifndef VECTOR
# define VECTOR

#include <stdbool.h>

typedef struct s_vector4
{
    float   x;
    float   y;
    float   z;
    float   w;
}   t_vector4;

t_vector4   vector(float x, float y, float z, float w);
t_vector4   vector_add(t_vector4 v1, t_vector4 v2);
t_vector4   vector_substract(t_vector4 v1, t_vector4 v2);
float       vector_dot(t_vector4 v1, t_vector4 v2);
t_vector4   vector_cross(t_vector4 v1, t_vector4 v2);

t_vector4   vector_multiply(t_vector4 v, const float m);
t_vector4   vector_divide(t_vector4 v, const float d);

void        vector_normalize(t_vector4 *v);

t_vector4   atov4(char *s, bool vector);

#endif