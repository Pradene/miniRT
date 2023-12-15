#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector.h"
# include "color.h"

typedef struct  s_light
{
    int     created;
    vec4    origin;
    rgba    color;
    float   brightness;
}   t_light;

typedef struct  s_alight
{
    int     created;
    rgba    color;
    float   brightness;
}   t_alight;

typedef enum    e_obj_type
{
    ERROR,
    CAMERA,
    AMBIENT_LIGHT,
    LIGHT,
    SPHERE,
    PLANE,
    CYLINDER
}   t_obj_type;

typedef struct  s_obj
{
    t_obj_type  type;
    vec4        origin;
    vec4        rotation;
    rgba        color;
    float       diameter;
    float       height;
    float       width;
}   t_obj;

typedef struct  s_obj_list
{
    t_obj               object;
    struct s_obj_list   *next;
}   t_obj_list;

typedef struct s_hit
{
    t_obj   *object;
    vec4    w_position;
    float   distance;
    vec4    normal;
}   t_hit;

void    free_objects(t_obj_list **lst);

void    print_objects(void);

int     check_irange(int value, int min, int max);
int     check_frange(float value, float min, float max);
int     check_color(rgba color);
int     check_brightness(float brightness);
int     check_fov(int fov);
int     check_direction(vec4 direction);

int     create_objects(char **sa);

#endif