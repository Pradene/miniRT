#include "../../includes/rt.h"

// Normalize a vector (sum of x, y, z equal 1)
void    vector_normalize(vec4 *v)
{
    float   magnitude;
    float   res;

    res = vector_dot(*v, *v);
    magnitude = sqrt(res);
    *v /= magnitude;
}