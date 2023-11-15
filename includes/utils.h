#ifndef UTILS
# define UTILS

# include <stdlib.h>
# include <stdbool.h>

int     string_array_size(char **sa);
void    free_string_array(char **sa);
void    copy_string_array(char **dest, char **src);

float   ft_atof(char *s, char **end);

float   clamp(float v, float min, float max);

float   radian(float angle);

#endif