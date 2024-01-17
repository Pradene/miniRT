/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:00:55 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:00:56 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	check_sphere(t_obj *obj)
{
	if (!check_color(obj->color) || obj->diameter < 0)
		return (0);
	return (1);
}

int	sphere(t_data *data, char **args)
{
	t_obj_list	*obj;
	char		*tmp;

	if (string_array_size(args) != 4)
		return (0);
	obj = malloc(sizeof(t_obj_list));
	if (!obj)
		return (0);
	obj->object.type = SPHERE;
	if (!atovec3(args[1], &obj->object.origin))
		return (free(obj), 0);
	obj->object.diameter = ft_atof(args[2], &tmp);
	if (tmp != args[2] + ft_strlen(args[2]))
		return (free(obj), 0);
	obj->object.color = atocolor(args[3]);
	if (!check_sphere(&obj->object))
		return (free(obj), 0);
	add_objects(&data->objects, obj);
	return (1);
}
