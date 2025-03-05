/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:42:22 by lpradene          #+#    #+#             */
/*   Updated: 2022/11/08 11:32:26 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *s, char **end)
{
	float	f;
	int		i;
	int		j;
	float	sign;

	f = 0.0;
	(*end) = s;
	if (!s)
		return (f);
	sign = 1.0;
	i = 0;
	if (s[i] == '-')
		sign *= -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
		f = f * 10 + (s[i++] - '0');
	(*end) = s + i;
	if (s[i] != '.')
		return (f * sign);
	j = i;
	while (ft_isdigit(s[++i]))
		f += (s[i] - '0') * (1.0 / (10.0 * ((float)i - (float)j)));
	(*end) = s + i;
	return (f * sign);
}