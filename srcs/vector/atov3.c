/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atov3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:48:45 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:50:38 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

vec3	atov3(char *s)
{
	vec3	v;
	char	*tmp;
	char	**infos;

	v = vector3(0, 0, 0);
	infos = ft_split(s, ',');
	if (!infos)
		return (v);
	if (string_array_size(infos) != 3)
		return (string_array_free(infos), v);
	v.x = ft_atof(infos[0], &tmp);
	v.y = ft_atof(infos[1], &tmp);
	v.z = ft_atof(infos[2], &tmp);
	string_array_free(infos);
	return (v);
}
