#include "../../includes/rt.h"

// Init a vector
t_vector4 vector(float x, float y, float z, float w)
{
    t_vector4   v;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return (v);
}