#include "../../includes/rt.h"

// Normalize a vector (sum of x, y, z equal 1)
vec4    normalize(const vec4 v)
{
    float   magnitude;
    float   d;
    vec4    res;

    d = dot(v, v);
    magnitude = sqrt(d);
    if (magnitude == 0)
        return (v);
    res = v / magnitude;
    res.w = v.w;
    return (res);
}