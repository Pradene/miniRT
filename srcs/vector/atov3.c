#include "../../includes/rt.h"

vec3   atov3(char *s)
{
    vec3    v;
    char    *tmp;
    char    **infos;

    v = vector3(0, 0, 0);
    infos = ft_split(s, ',');
    if (!infos)
        return (v);
    if (string_array_size(infos) != 3)
        return (string_array_free(infos), v);
    v.x = ft_atof(infos[0], &tmp);
    v.y = ft_atof(infos[1], &tmp);
    v.z = ft_atof(infos[2], &tmp);
    string_array_free(infos);
    return (v);
}