#include "../../includes/rt.h"

t_color get_color(t_obj obj, t_ray ray, float t)
{
    t_data      *data;
    vec4        hp;
    vec4        dir;
    vec4        normal;
    t_color     c;
    float       ratio;

    data = get_data();
    hp = ray.origin - obj.origin + ray.direction * t;
    normal = hp;
    vector_normalize(&normal);
    dir = hp + obj.origin - data->light.origin;
    vector_normalize(&dir);
    ray.origin = obj.origin + hp * 1.0001;
    ray.direction = -(ray.origin - data->light.origin);
    vector_normalize(&ray.direction);
    if (rayHit(ray))
    {
        c.r = obj.color.r * data->alight.brightness;
        c.g = obj.color.g * data->alight.brightness;
        c.b = obj.color.b * data->alight.brightness;
        return (c);
    }
    ratio = fmaxf(0.0, vector_dot(hp, -dir));
    c.r = obj.color.r * fminf(1.0, ratio + data->alight.brightness);
    c.g = obj.color.g * fminf(1.0, ratio + data->alight.brightness);
    c.b = obj.color.b * fminf(1.0, ratio + data->alight.brightness);
    return (c);
}

float   ray_sphere_intersection(t_obj obj, t_ray r)
{
    float  a;
    float  b;
    float  c;
    vec4   tmp;
    float  discriminant;

    tmp = r.origin - obj.origin;
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
