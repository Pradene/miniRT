#include "../../includes/rt.h"

// Init a vector
vec2 vector2(float x, float y)
{
    vec2   v;

    v.x = x;
    v.y = y;
    return (v);
}

vec3 vector3(float x, float y, float z)
{
    vec3   v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

vec4 vector4(float x, float y, float z, float w)
{
    vec4   v;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return (v);
}