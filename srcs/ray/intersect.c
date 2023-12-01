#include "../../includes/rt.h"

float   distance(vec4 p1, vec4 p2)
{
    return (2 * (p1.x * p2.x) + 2 * (p1.y * p2.y) + 2 * (p1.z * p2.z));
}

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
    ray.origin = h->w_position + h->normal * 0.0001;
    ray.direction = -(ray.origin - data->light.origin);
    vector_normalize(&ray.direction);
    float   d = ray_hit(ray).distance;
    if (d > 0)
    {
        c.r = h->object->color.r * data->alight.brightness;
        c.g = h->object->color.g * data->alight.brightness;
        c.b = h->object->color.b * data->alight.brightness;
        return (c);
    }
    dir = h->w_position - data->light.origin;
    vector_normalize(&dir);
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

// mat44   transform(vec4 origin, vec4 v)
// {
//     mat44   m;

//     m[0][0] = 0;
//     m[0][1] = -v.z;
//     m[0][2] = v.y;
//     m[0][3] = origin.x;

//     m[1][0] = v.z;
//     m[1][1] = 0;
//     m[1][2] = -v.x;
//     m[1][3] = origin.y;

//     m[2][0] = -v.y;
//     m[2][1] = v.x;
//     m[2][2] = 0;
//     m[2][3] = origin.z;

//     m[3][0] = 0;
//     m[3][1] = 0;
//     m[3][2] = 0;
//     m[3][3] = 1;
//     return (m);

// }

// t_hit   ray_cylinder_intersection(t_obj *obj, t_ray r)
// {
//     t_hit   h;
//     mat44   m;
//     mat44   mi;

//     m = transform(obj->origin, obj->rotation);
//     mat_inverse(m, &mi);
//     r.origin = mat_vec_product(mi, r.origin);
//     r.direction = mat_vec_product(mi, r.direction);

//     float   a;
//     float   b;
//     float   c;

//     a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
//     b = 2 * (r.direction.x * r.direction.x + r.origin.z * r.origin.z);
//     c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - obj->diameter / 2 * obj->diameter / 2;

//     float   discriminant;
//     discriminant = b * b - 4 * a * c;
//     if (discriminant < 0)
//         return (miss_ray());

//     float   t;
//     t = (-b - sqrt(discriminant)) / (2.0 * a);
//     h.w_position = r.origin * r.direction * t;

//     if (h.w_position.y < 0 || h.w_position.y > obj->height)
//         return (miss_ray());
//     printf("ok\n");
    
//     h.w_position = mat_vec_product(m, h.w_position);
//     h.distance = t;
//     h.object = obj;
//     h.normal = vector4(0, 1, 0, 1);

//     return (h);
// }

float   dot(vec4 v1, vec4 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}


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
    if (dot(obj->rotation, h.w_position - obj->origin) > 0 \
    && dot(obj->rotation, h.w_position - (obj->origin + obj->rotation * obj->height)) < 0)
    {
        h.w_position = r.origin - obj->origin + r.direction * t;
        h.distance = t;
        h.object = obj;
        h.normal = vector4(0, 1, 0, 1);
        return (h);
    }
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
        h.w_position = r.origin + r.direction * h.distance;
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
    h.w_position += obj->origin;
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
