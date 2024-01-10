/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:09:54 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:10:50 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	check_irange(int value, int min, int max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

int	check_frange(float value, float min, float max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

int	check_color(rgba color)
{
	if (!check_frange(color.r, 0.0, 1.0) \
	|| !check_frange(color.g, 0.0, 1.0) \
	|| !check_frange(color.b, 0.0, 1.0) \
	|| !check_frange(color.a, 0.0, 1.0))
		return (0);
	return (1);
}

int	check_brightness(float brightness)
{
	if (!check_frange(brightness, 0.0, 1.0))
		return (0);
	return (1);
}

int	check_fov(int fov)
{
	if (!check_irange(fov, 0, 180))
		return (0);
	return (1);
}

int	check_rotation(vec3 direction)
{
	if (!check_frange(direction.x, -1.0, 1.0) \
	|| !check_frange(direction.y, -1.0, 1.0) \
	|| !check_frange(direction.z, -1.0, 1.0))
		return (0);
	return (1);
}
