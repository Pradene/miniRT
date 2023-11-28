#include "../../includes/rt.h"

t_color get_color(t_obj obj, t_ray ray, t_hit *h)
{
    t_data      *data;
    vec4        dir;
    t_color     c;
    float       ratio;

    data = get_data();
    dir = h->w_position + obj.origin - data->light.origin;
    vector_normalize(&dir);
    ray.origin = obj.origin + h->w_position * 1.0001;
    ray.direction = -(ray.origin - data->light.origin);
    vector_normalize(&ray.direction);
    if (rayHit(ray))
    {
        c.r = obj.color.r * data->alight.brightness;
        c.g = obj.color.g * data->alight.brightness;
        c.b = obj.color.b * data->alight.brightness;
        return (c);
    }
    dir *= -1;
    ratio = fmaxf(0.0, vector_dot(&h->normal, &dir));
    c.r = obj.color.r * fminf(1.0, ratio + data->alight.brightness);
    c.g = obj.color.g * fminf(1.0, ratio + data->alight.brightness);
    c.b = obj.color.b * fminf(1.0, ratio + data->alight.brightness);
    return (c);
}

t_hit   miss_ray()
{
    t_hit   h;

    h.distance = -1;
    h.object = NULL;
    h.normal = 0;
    h.w_position = 0;
    return (h);
}

t_hit   ray_sphere_intersection(t_obj *obj, t_ray r)
{
    float   a;
    float   b;
    float   c;
    float   discriminant;
    t_hit   h;
    vec4    tmp;

    tmp = r.origin - obj->origin;
    a = vector_dot(&r.direction, &r.direction);
    b = 2 * vector_dot(&tmp, &r.direction);
    c = vector_dot(&tmp, &tmp) - (obj->diameter / 2) * (obj->diameter / 2);
    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return (miss_ray());
    h.distance = (-b - sqrt(discriminant)) / (2.0 * a);
    h.object = obj;
    h.w_position = tmp + r.direction * h.distance;
    h.normal = normalize(&h.w_position);
    return (h);
}

bool    rayHit(t_ray r)
{
    t_data      *data;
    t_obj_list  *tmp;

    data = get_data();
    tmp = data->objects;
    while (tmp)
    {
        if (tmp->object.type == SPHERE)
        {
            if (ray_sphere_intersection(&tmp->object, r).distance >= 0)
                return (true);
        }
        tmp = tmp->next;
    }
    return (false);
}

t_color intersect(t_ray r)
{
    t_data      *data;
    t_obj_list  *tmp;
    t_color     c;
    t_hit       h;
    t_hit       ht;

    c = color(0, 0, 0, 1);
    data = get_data();
    tmp = data->objects;
    h.distance = FLT_MAX;
    while (tmp)
    {
        if (tmp->object.type == SPHERE)
        {
            ht = ray_sphere_intersection(&tmp->object, r);
            if (ht.distance > 0.0 && ht.distance < h.distance)
            {
                h = ht;
                c = get_color(tmp->object, r, &h);
            }
        }
        tmp = tmp->next;
    }
    return (c);
}
