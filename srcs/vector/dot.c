#include "../../includes/rt.h"

// this function gives the dot product of 2 vectors / points
float   vector_dot(t_vector4 v1, t_vector4 v2)
{
    float   res;

    res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return (res);
}