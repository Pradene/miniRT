/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:00:04 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:00:06 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	check_cylinder(t_obj *obj)
{
	if (!check_color(obj->color) || !check_rotation(obj->rotation) \
	|| obj->height < 0 || obj->diameter < 0)
		return (0);
	return (1);
}

int	cylinder(t_data *data, char **args)
{
	t_obj_list	*obj;
	char		*tmp;

	if (string_array_size(args) != 6)
		return (0);
	obj = malloc(sizeof(t_obj_list));
	if (!obj)
		return (0);
	obj->object.type = CYLINDER;
	if (!atovec3(args[1], &obj->object.origin))
		return (free(obj), 0);
	if (!atovec3(args[2], &obj->object.rotation))
		return (free(obj), 0);
	obj->object.diameter = ft_atof(args[3], &tmp);
	if (tmp != args[3] + ft_strlen(args[3]))
		return (free(obj), 0);
	obj->object.height = ft_atof(args[4], &tmp);
	if (tmp != args[4] + ft_strlen(args[4]))
		return (free(obj), 0);
	obj->object.color = atocolor(args[5]);
	if (!check_cylinder(&obj->object))
		return (free(obj), 0);
	obj->object.rotation = normalize(obj->object.rotation);
	add_objects(&data->objects, obj);
	return (1);
}
