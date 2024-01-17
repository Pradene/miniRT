/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:59 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:05:30 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# include "../libft/libft.h"

# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define PI 3.14159265359

typedef struct s_data
{
	t_obj_list	*objects;
	t_camera	camera;
	t_light		light;
	t_alight	alight;
	void		*id;
	void		*win;
	float		et;
	t_image		img;
	int			frame;
	float		aspect_ratio;
}	t_data;

int		camera(t_data *data, char **args);
int		cylinder(t_data *data, char **args);
int		plane(t_data *data, char **args);
int		sphere(t_data *data, char **args);
int		light(t_data *data, char **args);
int		ambient_light(t_data *data, char **args);

// Data
t_data	*get_data(void);
int		free_data(void);

// Rendering
void	renderer(char *name);
void	render(void);
int		update(t_data *data);

// Events
int		key(int key, t_data *data);
int		mouse(int button, int x, int y, t_data *data);

#endif
