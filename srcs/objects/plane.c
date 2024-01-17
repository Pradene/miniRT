/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:01:57 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:01:58 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	check_plane(t_obj *obj)
{
	if (!check_color(obj->color) || !check_rotation(obj->rotation))
		return (0);
	return (1);
}

int	plane(t_data *data, char **args)
{
	t_obj_list	*obj;

	if (string_array_size(args) != 4)
		return (0);
	obj = malloc(sizeof(t_obj_list));
	if (!obj)
		return (0);
	obj->object.type = PLANE;
	if (!atovec3(args[1], &obj->object.origin))
		return (free(obj), 0);
	if (!atovec3(args[2], &obj->object.rotation))
		return (free(obj), 0);
	obj->object.color = atocolor(args[3]);
	if (!check_plane(&obj->object))
		return (free(obj), 0);
	obj->object.rotation = normalize(obj->object.rotation);
	add_objects(&data->objects, obj);
	return (1);
}
