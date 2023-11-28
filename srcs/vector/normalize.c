#include "../../includes/rt.h"

// Normalize a vector (sum of x, y, z equal 1)
void    vector_normalize(vec4 *v)
{
    float   magnitude;
    float   res;

    res = vector_dot(v, v);
    magnitude = sqrt(res);
    if (magnitude != 0)
        *v /= magnitude;
    v->w = 1.0;
}

vec4    normalize(const vec4 *v)
{
    float   magnitude;
    float   dot;
    vec4    res;

    res = vector4(0, 0, 0, 0);
    dot = vector_dot(v, v);
    magnitude = sqrt(dot);
    if (magnitude != 0)
        res = *v / magnitude;
    return (res);
}