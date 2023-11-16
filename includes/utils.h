#ifndef UTILS
# define UTILS

# include <stdlib.h>
# include <stdbool.h>

#include "mlx_utils.h"

void	pixel_put(t_image *img, int x, int y, t_color c);

int     string_array_size(char **sa);
void    free_string_array(char **sa);
void    copy_string_array(char **dest, char **src);

float   ft_atof(char *s, char **end);

float   clamp(float v, float min, float max);

float   radian(float angle);

#endif