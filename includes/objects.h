#ifndef OBJECTS
# define OBJECTS

# include "vector.h"
# include "color.h"

# define WIDTH 1920
# define HEIGHT 1080
# define ASPECT_RATIO (float)WIDTH / (float)HEIGHT

typedef struct  s_camera
{
    int     created;
    vec4    origin;
    vec4    direction;
    int     fov;
    mat44   m_projection;
    mat44   m_inverse_projection;
    mat44   m_view;
    mat44   m_inverse_view;
    vec4    ray_direction[HEIGHT * WIDTH];
}   t_camera;

typedef struct  s_light
{
    int     created;
    vec4    origin;
    t_color color;
    float   brightness;
}   t_light;

typedef struct  s_alight
{
    int     created;
    t_color color;
    float   brightness;
}   t_alight;

typedef enum    e_obj_type
{
    ERROR,
    AMBIENT_LIGHT,
    CAMERA,
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
    t_color     color;
    float       diameter;
    float       height;
    float       width;
}   t_obj;

typedef struct  s_obj_list
{
    t_obj               object;
    struct s_obj_list   *next;
}   t_obj_list;

void    free_objects(t_obj_list **lst);

void    print_objects(void);

int     check_irange(int value, int min, int max);
int     check_frange(float value, float min, float max);
int     check_color(t_color color);
int     check_brightness(float brightness);
int     check_fov(int fov);
int     check_direction(vec4 direction);

void    create_objects(char **sa);

#endif