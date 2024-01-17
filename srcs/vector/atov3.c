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

t_vec3	atov3(char *s)
{
	t_vec3	v;
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

int	atovec3(char *s, t_vec3 *v)
{
	char	*tmp;
	char	**infos;

	*v = vector3(0, 0, 0);
	infos = ft_split(s, ',');
	if (!infos)
		return (0);
	if (string_array_size(infos) != 3)
		return (string_array_free(infos), 0);
	v->x = ft_atof(infos[0], &tmp);
	if (tmp != infos[0] + ft_strlen(infos[0]))
		return (string_array_free(infos), 0);
	v->y = ft_atof(infos[1], &tmp);
	if (tmp != infos[1] + ft_strlen(infos[1]))
		return (string_array_free(infos), 0);
	v->z = ft_atof(infos[2], &tmp);
	if (tmp != infos[2] + ft_strlen(infos[2]))
		return (string_array_free(infos), 0);
	string_array_free(infos);
	return (1);
}
