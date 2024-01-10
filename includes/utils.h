/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:57:10 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:03:57 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>

# include "mlx_utils.h"

void	pixel_put(t_image *img, int x, int y, rgba c);

int		string_array_size(char **sa);
void	string_array_free(char **sa);
void	string_array_copy(char **dest, char **src);

float	ft_atof(char *s, char **end);

float	map(float v, vec2 range, vec2 nrange);

float	distance(vec3 p1, vec3 p2);

float	clamp(float v, float min, float max);

float	radian(float angle);

#endif
