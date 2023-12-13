#include "../../includes/rt.h"

t_hit   ray_sphere_intersection(t_obj *obj, t_ray r)
{
    float   a;
    float   b;
    float   c;
    float   discriminant;
    t_hit   h;
    vec4    tmp;

    tmp = r.origin - obj->origin;
    a = dot(r.direction, r.direction);
    b = 2 * dot(tmp, r.direction);
    c = dot(tmp, tmp) - powf(obj->diameter / 2, 2.0);
    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return (miss_ray());
    h.distance = (-b - sqrt(discriminant)) / (2.0 * a);
    h.object = obj;
    h.w_position = tmp + r.direction * h.distance;
    h.normal = normalize(h.w_position);
    h.w_position += obj->origin;
    return (h);
}
