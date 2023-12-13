#include "../../includes/rt.h"

rgba    color(float r, float g, float b, float a)
{
    rgba c;

    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return (c);
}

rgba    atocolor(char *s)
{
    rgba    c;
    char    **colors;

    c.r = 0.0;
    c.g = 0.0;
    c.b = 0.0;
    c.a = 1.0;
    colors = ft_split(s, ',');
    if (!colors)
        return (c);
    if (string_array_size(colors) < 3 || string_array_size(colors) > 4)
        return (free_string_array(colors), c);
    c.r = (float)(ft_atoi(colors[0]) / 255);
    c.g = (float)(ft_atoi(colors[1]) / 255);
    c.b = (float)(ft_atoi(colors[2]) / 255);
    if (string_array_size(colors) == 4)
        c.a = ft_atof(colors[3], NULL);
    free_string_array(colors);
    return (c);
}

// transform a rgba struct into an integer color
int colortoi(rgba c)
{
    int color;

    c.r = clamp(c.r, 0.0, 1.0);
    c.g = clamp(c.g, 0.0, 1.0);
    c.b = clamp(c.b, 0.0, 1.0);
    c.a = clamp(c.a, 0.0, 1.0);
    color = ((int)(c.a * 255) << 24) | ((int)(c.r * 255) << 16) \
    | ((int)(c.g * 255) << 8) | ((int)(c.b * 255) << 0);
    return (color);
}