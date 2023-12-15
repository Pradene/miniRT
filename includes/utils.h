#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>

#include "mlx_utils.h"

void	pixel_put(t_image *img, int x, int y, rgba c);

int     string_array_size(char **sa);
void    free_string_array(char **sa);
void    copy_string_array(char **dest, char **src);

float   ft_atof(char *s, char **end);

float   map(float v, vec2 range, vec2 nrange);

float   distance(vec4 p1, vec4 p2);

float   clamp(float v, float min, float max);

float   radian(float angle);

#endif