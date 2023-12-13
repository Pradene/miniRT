#ifndef RAY_H
# define RAY_H

#include "vector.h"
#include "objects.h"

typedef struct s_ray
{
    vec4   origin;
    vec4   direction;
}   t_ray;

t_hit   miss_ray();

t_hit   ray_plane_intersection(t_obj *obj, t_ray r);
t_hit   ray_sphere_intersection(t_obj *obj, t_ray r);
t_hit   ray_cylinder_intersection(t_obj *obj, t_ray r);

rgba    intersect(t_ray r);
t_hit   ray_hit(t_ray r);

#endif