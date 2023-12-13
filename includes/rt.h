#ifndef RT_H
# define RT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include <time.h>
# include <sys/time.h>

# include <limits.h>
# include <float.h>

# include "camera.h"
# include "color.h"
# include "matrix.h"
# include "mlx_utils.h"
# include "objects.h"
# include "parsing.h"
# include "ray.h"
# include "utils.h"
# include "vector.h"

#include "../libft/libft.h"

# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define PI 3.14159265359

typedef struct s_data
{
    t_obj_list  *objects;
    t_camera    camera;
    t_light     light;
    t_alight    alight;
    void        *id;
    void        *win;
    float       et;
    t_image     img;
}   t_data;

// Data
t_data  *get_data();
int     free_data();

// Rendering
void    renderer(char *name);
void    render();
int     update(t_data *data);

// Events
int	    key(int key, t_data *data);

#endif