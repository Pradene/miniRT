#include "../../includes/rt.h"

vec4   atov4(char *s, bool vector)
{
    vec4    v;
    char    *tmp;
    char    **infos;

    v = vector4(0, 0, 0, 0);
    infos = ft_split(s, ',');
    if (!infos)
        return (v);
    if (string_array_size(infos) != 3)
        return (free_string_array(infos), v);
    v.x = ft_atof(infos[0], &tmp);
    v.y = ft_atof(infos[1], &tmp);
    v.z = ft_atof(infos[2], &tmp);
    if (vector)
        v.w = 1.0;
    free_string_array(infos);
    return (v);
}