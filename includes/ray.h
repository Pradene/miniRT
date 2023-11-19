#ifndef RAY
# define RAY

#include "vector.h"

typedef struct s_ray
{
    vec4   origin;
    vec4   direction;
}   t_ray;

t_color intersect(t_ray r);
bool    rayHit(t_ray r);

#endif