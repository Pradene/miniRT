/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:47:00 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:47:01 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

float	map(float v, vec2 range, vec2 nrange)
{
	return ((v - range[0]) / (range[1] - range[0]) \
	* (nrange[1] - nrange[0]) + nrange[0]);
}
