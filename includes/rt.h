#ifndef RT
# define RT

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include <limits.h>
# include <float.h>

# include "color.h"
# include "objects.h"
# include "parsing.h"
# include "ray.h"
# include "utils.h"
# include "vector.h"

#include "../libft/libft.h"

# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define PI 3.14159265359

# define WIDTH 1920
# define HEIGHT 1080
# define ASPECT_RATIO (float)WIDTH / (float)HEIGHT

typedef struct s_image
{
	void	*image;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_data
{
    t_obj_list  *objects;
    t_camera    camera;
    t_light     light;
    t_alight    alight;
    void        *id;
    void        *win;
    t_image     img;
    t_vector4   pixels[HEIGHT * WIDTH];
}   t_data;

// Data
t_data  *get_data();
int     free_data();

// Rendering
void    renderer(char *name);
void    render();

// Events
int	    key(int key, t_data *data);

#endif