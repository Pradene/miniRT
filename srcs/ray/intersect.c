#include "../../includes/rt.h"

t_color get_color(t_ray ray, t_hit *h)
{
    t_data      *data;
    vec4        dir;
    t_color     c;
    float       ratio;

    c = color(0, 0, 0, 1);
    if (h->object == NULL)
        return (c);
    data = get_data();
    dir = h->w_position + h->object->origin - data->light.origin;
    vector_normalize(&dir);
    ray.origin = h->object->origin + h->w_position * 1.0001;
    ray.direction = -(ray.origin - data->light.origin);
    vector_normalize(&ray.direction);
    if (rayHit(ray))
    {
        c.r = h->object->color.r * data->alight.brightness;
        c.g = h->object->color.g * data->alight.brightness;
        c.b = h->object->color.b * data->alight.brightness;
        return (c);
    }
    dir *= -1;
    ratio = fmaxf(0.0, vector_dot(&h->normal, &dir));
    c.r = h->object->color.r * fminf(1.0, ratio + data->alight.brightness);
    c.g = h->object->color.g * fminf(1.0, ratio + data->alight.brightness);
    c.b = h->object->color.b * fminf(1.0, ratio + data->alight.brightness);
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

t_hit   ray_cylinder_intersection(t_obj *obj, t_ray r)
{
    t_hit   h;
    float   a;
    float   b;
    float   c;

    (void)obj;
    (void)r;
    (void)h;
    return (miss_ray());
}

t_hit   ray_plane_intersection(t_obj *obj, t_ray r)
{
    float   denom;
    t_hit   h;
    vec4    tmp;

    denom = vector_dot(&obj->rotation, &r.direction);
    if (fabsf(denom) > 0.0001)
    {
        tmp = obj->origin - r.origin;
        h.distance = vector_dot(&tmp, &obj->rotation) / denom;
        h.object = obj;
        h.w_position = tmp + r.direction * h.distance;
        h.normal = obj->rotation;
        return (h);
    }
    return (miss_ray());
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
        else if (tmp->object.type == PLANE)
        {
            if (ray_plane_intersection(&tmp->object, r).distance >= 0)
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
    t_hit       h;
    t_hit       ht;

    data = get_data();
    tmp = data->objects;
    h = miss_ray();
    h.distance = FLT_MAX;
    while (tmp)
    {
        if (tmp->object.type == SPHERE)
            ht = ray_sphere_intersection(&tmp->object, r);
        else if (tmp->object.type == PLANE)
            ht = ray_plane_intersection(&tmp->object, r);
        if (ht.distance > 0.0 && ht.distance < h.distance)
            h = ht;
        tmp = tmp->next;
    }
    return (get_color(r, &h));
}
