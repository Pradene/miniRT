/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:07:21 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:07:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	check_ambient_light(t_alight light)
{
	if (!check_color(light.color) || !check_brightness(light.brightness))
		return (0);
	return (1);
}

int	ambient_light(t_data *data, char **args)
{
	char	*tmp;

	if (string_array_size(args) != 3)
		return (0);
	if (data->alight.created)
		return (0);
	data->alight.brightness = ft_atof(args[1], &tmp);
	if (tmp != args[1] + ft_strlen(args[1]))
		return (0);
	data->alight.color = atocolor(args[2]);
	data->alight.created = 1;
	if (!check_ambient_light(data->alight))
		return (0);
	return (1);
}
