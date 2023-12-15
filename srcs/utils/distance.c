#include "../../includes/rt.h"

float   distance(vec4 p1, vec4 p2)
{
    return (2 * (p1.x * p2.x) + 2 * (p1.y * p2.y) + 2 * (p1.z * p2.z));
}