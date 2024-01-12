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
	float	f;
	char	*tmp;
	char	**colors;

	colors = ft_split(s, ',');
	if (!colors)
		return (color(-1, -1, -1, -1));
	if (string_array_size(colors) != 3)
		return (string_array_free(colors), color(-1, -1, -1, -1));
	f = ft_atof(colors[0], &tmp);
	if (tmp != colors[0] + ft_strlen(colors[0]))
		return (color(-1, -1, -1, -1));
	c.r = (f / 255.0);
	f = ft_atof(colors[1], &tmp);
	if (tmp != colors[1] + ft_strlen(colors[1]))
		return (color(-1, -1, -1, -1));
	c.g = (f / (float)255);
	f = ft_atof(colors[2], &tmp);
	if (tmp != colors[2] + ft_strlen(colors[2]))
		return (color(-1, -1, -1, -1));
	c.b = (f / (float)255);
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

rgba	itocolor(int c)
{
	rgba	color;

	color.a = (float)((c >> 24) & 0xFF) / 255.0;
	color.r = (float)((c >> 16) & 0xFF) / 255.0;
	color.g = (float)((c >> 8) & 0xFF) / 255.0;
	color.b = (float)((c >> 0) & 0xFF) / 255.0;
	return (color);
}
