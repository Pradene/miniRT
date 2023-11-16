#include "../../includes/rt.h"

float   min(float f1, float f2)
{
    if (f1 < f2)
        return (f1);
    return (f2);
}

float   max(float f1, float f2)
{
    if (f1 > f2)
        return (f1);
    return (f2);
}

t_color get_color(t_obj obj, t_ray ray, float t)
{
    t_data      *data;
    t_vector4   hp;
    t_vector4   dir;
    t_color     c;
    float       ratio;

    data = get_data();
    hp = vector_substract(ray.origin, obj.origin);
    hp = vector_add(hp, vector_multiply(ray.direction, t));
    vector_normalize(&hp);
    dir = vector_add(hp, obj.origin);
    dir = vector_substract(dir, data->light.origin);
    vector_normalize(&dir);
    ray.origin = vector_add(obj.origin, vector_multiply(hp, 1.0001));
    ray.direction = vector_substract(ray.origin, data->light.origin);
    ray.direction = vector_multiply(ray.direction, -1);
    vector_normalize(&ray.direction);
    if (rayHit(ray))
    {
        c.r = obj.color.r * data->alight.brightness;
        c.g = obj.color.g * data->alight.brightness;
        c.b = obj.color.b * data->alight.brightness;
        return (c);
    }
    ratio = max(0.0, vector_dot(hp, vector_multiply(dir, -1)));
    c.r = obj.color.r * min(1.0, ratio + data->alight.brightness);
    c.g = obj.color.g * min(1.0, ratio + data->alight.brightness);
    c.b = obj.color.b * min(1.0, ratio + data->alight.brightness);
    return (c);
}

float   ray_sphere_intersection(t_obj obj, t_ray r)
{
    float       a;
    float       b;
    float       c;
    t_vector4   tmp;
    float       discriminant;

    tmp = vector_substract(r.origin, obj.origin);
    a = vector_dot(r.direction, r.direction);
    b = 2 * vector_dot(tmp, r.direction);
    c = vector_dot(tmp, tmp) - (obj.diameter / 2) * (obj.diameter / 2);
    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return (-1.0);
    return (-b - sqrt(discriminant)) / (2.0 * a);
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
            if (ray_sphere_intersection(tmp->object, r) >= 0)
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
    float       tdistance;
    float       distance;

    c = color(0, 0, 0, 1);
    data = get_data();
    tmp = data->objects;
    distance = FLT_MAX;
    while (tmp)
    {
        if (tmp->object.type == SPHERE)
        {
            tdistance = ray_sphere_intersection(tmp->object, r);
            if (tdistance > 0.0 && tdistance < distance)
            {
                distance = tdistance;
                c = get_color(tmp->object, r, distance);
            }
        }
        tmp = tmp->next;
    }
    return (c);
}
