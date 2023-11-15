#include "../../includes/rt.h"

// Normalize a vector (sum of x, y, z equal 1)
void    vector_normalize(t_vector4 *v)
{
    float   magnitude;
    float   res;

    if (v->w != 1.0)
        return ;
    res = vector_dot(*v, *v);
    magnitude = sqrt(res);
    v->x /= magnitude;
    v->y /= magnitude;
    v->z /= magnitude;
}