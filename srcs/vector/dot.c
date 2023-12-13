#include "../../includes/rt.h"

// this function gives the dot product of 2 vectors / points
float   dot(const vec4 v1, const vec4 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}