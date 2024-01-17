/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:07:15 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:07:16 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	check_light(t_light light)
{
	if (!check_color(light.color) || !check_brightness(light.brightness))
		return (0);
	return (1);
}

int	light(t_data *data, char **args)
{
	char	*tmp;

	if (string_array_size(args) != 4)
		return (0);
	if (data->light.created)
		return (0);
	if (!atovec3(args[1], &data->light.origin))
		return (0);
	data->light.brightness = ft_atof(args[2], &tmp);
	if (tmp != args[2] + ft_strlen(args[2]))
		return (0);
	data->light.color = atocolor(args[3]);
	data->light.created = 1;
	if (!check_light(data->light))
		return (0);
	return (1);
}
