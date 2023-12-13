#include "../../includes/rt.h"

t_hit   ray_plane_intersection(t_obj *obj, t_ray r)
{
    float   denom;
    t_hit   h;
    vec4    tmp;

    denom = dot(obj->rotation, r.direction);
    if (fabsf(denom) > 0.0001)
    {
        tmp = obj->origin - r.origin;
        h.distance = dot(tmp, obj->rotation) / denom;
        h.object = obj;
        h.w_position = r.origin + r.direction * h.distance;
        h.normal = obj->rotation;
        if (denom > 0.0001)
            h.normal *= -1;
        return (h);
    }
    return (miss_ray());
}