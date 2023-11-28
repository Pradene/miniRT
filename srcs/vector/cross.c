#include "../../includes/rt.h"

// Give the cross product of 2 vectors
// the cross product is a vector perpendicular
// to the plane created by the 2 vectors
vec4   vector_cross(const vec4 *v1, const vec4 *v2)
{
    vec4   v;

    v.x = v1->y * v2->z - v1->z * v2->y;
    v.y = v1->z * v2->x - v1->x * v2->z;
    v.z = v1->x * v2->y - v1->y * v2->x;
    v.w = 1.0;
    return (v);
}