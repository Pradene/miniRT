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
    if (ray_hit(ray).distance > 0.0)
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
    float   discriminant;
    vec4    tmp;

    r.direction = vector_cross(&r.direction, &obj->rotation);
    a = vector_dot(&r.direction, &r.direction);
    tmp = r.origin - obj->origin;
    tmp = vector_cross(&tmp, &obj->rotation);
    b = 2 * vector_dot(&r.direction, &tmp);
    tmp = r.origin - obj->origin;
    tmp = vector_cross(&tmp, &obj->rotation);
    c = vector_dot(&tmp, &tmp) - powf(obj->diameter / 2, 2.0);
    discriminant = powf(b, 2.0) - 4 * c * a;
    if (discriminant < 0)
        return (miss_ray());
    float   t = (-b - sqrt(discriminant)) / (2.0 * a);
    h.w_position = r.origin - obj->origin + r.direction * t;
    h.object = obj;
    h.distance = t;
    h.normal = vector4(0, 1, 0, 1);
    return (h);
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
    c = vector_dot(&tmp, &tmp) - powf(obj->diameter / 2, 2.0);
    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return (miss_ray());
    h.distance = (-b - sqrt(discriminant)) / (2.0 * a);
    h.object = obj;
    h.w_position = tmp + r.direction * h.distance;
    h.normal = normalize(&h.w_position);
    return (h);
}

t_hit   ray_hit(t_ray r)
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
        else if (tmp->object.type == CYLINDER)
            ht = ray_cylinder_intersection(&tmp->object, r);
        if (ht.distance > 0.0 && ht.distance < h.distance)
            h = ht;
        tmp = tmp->next;
    }
    if (h.distance == FLT_MAX)
        h.distance = -1;
    return (h);
}

t_color intersect(t_ray r)
{
    t_hit       h;

    h = ray_hit(r);
    return (get_color(r, &h));
}
