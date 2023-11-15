#include "../../includes/rt.h"

// Give the cross product of 2 vectors
// the cross product is a vector perpendicular
// to the plane created by the 2 vectors
t_vector4   vector_cross(t_vector4 v1, t_vector4 v2)
{
    t_vector4   v;

    v.w = -1.0;
    if (v1.w != 1.0 || v2.w != 1.0)
        return (v);
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    v.w = 1.0;
    return (v);
}