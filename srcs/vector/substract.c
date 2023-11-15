#include "../../includes/rt.h"

// this function substract a vector to another vector or to a point
// v1 can be a point or a vector
// v2 can be point just if v1 is also a point

t_vector4   vector_substract(t_vector4 v1, t_vector4 v2)
{
    t_vector4   v;

    v = vector(0, 0, 0, -1);
    if (v1.w == 1.0 && v2.w != 1.0)
        return (v);
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    v.w = v1.w;
    return (v);
}