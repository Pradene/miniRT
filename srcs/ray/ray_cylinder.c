#include "../../includes/rt.h"

t_hit   ray_cylinder_intersection(t_obj *obj, t_ray r)
{
    t_hit   h;
    float   a;
    float   b;
    float   c;
    float   discriminant;
    vec4    tmp1;
    vec4    tmp2;
    float   t;

    tmp1 = r.direction - dot(r.direction, obj->rotation) * obj->rotation;
    tmp2 = r.origin - obj->origin;
    tmp2 = tmp2 - dot(tmp2, obj->rotation) * obj->rotation;

    a = dot(tmp1, tmp1);
    b = 2 * dot(tmp1, tmp2);
    c = dot(tmp2, tmp2) - powf(obj->diameter / 2, 2.0);
    discriminant = b * b - 4 * c * a;
    if (discriminant < 0)
        return (miss_ray());
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    h.w_position = r.origin + r.direction * t;
    if (dot(obj->rotation, h.w_position - (obj->origin - obj->rotation * obj->height / 2)) > 0 \
    && dot(obj->rotation, h.w_position - (obj->origin + obj->rotation * obj->height / 2)) < 0)
    {
        h.w_position = r.origin + r.direction * t;
        h.distance = t;
        h.object = obj;

        h.normal = dot(h.w_position - obj->origin, obj->rotation) * obj->rotation;
        h.normal = h.w_position - obj->origin - h.normal;
        h.normal = normalize(h.normal);
        return (h);
    }
    t_obj   o;

    o = *obj;
    o.origin = obj->origin + obj->rotation * obj->height / 2;
    t_hit   ht;

    ht = ray_plane_intersection(&o, r);
    if (dot(o.rotation, ht.w_position - o.origin) == 0 \
    && dot(ht.w_position - o.origin, ht.w_position - o.origin) < powf(obj->diameter / 2, 2.0))
    {
        return (ht);
    }

    o.origin = obj->origin - obj->rotation * obj->height / 2;

    ht = ray_plane_intersection(&o, r);
    if (dot(o.rotation, ht.w_position - o.origin) == 0 \
    && dot(ht.w_position - o.origin, ht.w_position - o.origin) < powf(obj->diameter / 2, 2.0))
    {
        return (ht);
    }
    return (miss_ray());
}