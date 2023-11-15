#include "../../includes/rt.h"

// this function add a vector to another vector or to a point
// v1 can be a point or a vector
// v2 has to be a vector
// v will be a point or a vector depending on v1

t_vector4   vector_add(t_vector4 v1, t_vector4 v2)
{
    t_vector4   v;

    v = vector(0, 0, 0, -1);
    if (v1.w == 1.0 && v2.w != 1.0)
        return (v);
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    v.w = v1.w;
    return (v);
}

t_vector4   vector_multiply(t_vector4 v, const float m)
{
    t_vector4   rv;

    rv.x = v.x * m;
    rv.y = v.y * m;
    rv.z = v.z * m;
    rv.w = v.w;
    return (rv);
}

t_vector4   vector_divide(t_vector4 v, const float d)
{
    t_vector4   rv;

    rv.x = v.x / d;
    rv.y = v.y / d;
    rv.z = v.z / d;
    rv.w = v.w;
    return (rv);
}
