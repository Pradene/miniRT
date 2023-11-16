#ifndef RAY
# define RAY

#include "vector.h"

typedef struct s_ray
{
    t_vector4   origin;
    t_vector4   direction;
}   t_ray;

t_color intersect(t_ray r);
bool    rayHit(t_ray r);

#endif