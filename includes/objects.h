/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:36 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:04:59 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector.h"
# include "color.h"

typedef struct s_light
{
	int		created;
	t_vec3	origin;
	t_rgba	color;
	float	brightness;
}	t_light;

typedef struct s_alight
{
	int		created;
	t_rgba	color;
	float	brightness;
}	t_alight;

typedef enum e_obj_type
{
	ERROR,
	CAMERA,
	AMBIENT_LIGHT,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_obj
{
	t_obj_type	type;
	t_vec3		origin;
	t_vec3		rotation;
	t_rgba		color;
	float		diameter;
	float		height;
	float		width;
}	t_obj;

typedef struct s_obj_list
{
	t_obj				object;
	struct s_obj_list	*next;
}	t_obj_list;

typedef struct s_hit
{
	t_obj	*object;
	float	distance;
	t_vec3	w_position;
	t_vec3	normal;
}	t_hit;

void		free_objects(t_obj_list **lst);
t_obj_list	*last_objects(t_obj_list *lst);
void		add_objects(t_obj_list **lst, t_obj_list *new);
t_obj_type	check_obj_type(char *type);

void		print_objects(void);

int			check_irange(int value, int min, int max);
int			check_frange(float value, float min, float max);
int			check_color(t_rgba color);
int			check_brightness(float brightness);
int			check_rotation(t_vec3 direction);

int			create_objects(char **sa);

#endif
