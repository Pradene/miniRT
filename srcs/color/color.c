/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:33:33 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 11:34:18 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

rgba	color(float r, float g, float b, float a)
{
	rgba	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

rgba	atocolor(char *s)
{
	rgba	c;
	char	**colors;

	c.r = 0.0;
	c.g = 0.0;
	c.b = 0.0;
	c.a = 1.0;
	colors = ft_split(s, ',');
	if (!colors)
		return (c);
	if (string_array_size(colors) < 3 || string_array_size(colors) > 4)
		return (string_array_free(colors), c);
	c.r = ((float)ft_atoi(colors[0]) / (float)255);
	c.g = ((float)ft_atoi(colors[1]) / (float)255);
	c.b = ((float)ft_atoi(colors[2]) / (float)255);
	if (string_array_size(colors) == 4)
		c.a = ft_atof(colors[3], NULL);
	string_array_free(colors);
	return (c);
}

// transform a rgba struct into an integer color
int	colortoi(rgba c)
{
	int	color;

	c.r = clamp(c.r, 0.0, 1.0);
	c.g = clamp(c.g, 0.0, 1.0);
	c.b = clamp(c.b, 0.0, 1.0);
	c.a = clamp(c.a, 0.0, 1.0);
	color = ((int)(c.a * 255) << 24) | ((int)(c.r * 255) << 16) \
	| ((int)(c.g * 255) << 8) | ((int)(c.b * 255) << 0);
	return (color);
}
