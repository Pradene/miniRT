/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:41:36 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 11:41:41 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	mouse(int button, int x, int y, t_data *data)
{
	t_ray	r;
	t_hit	h;

	(void)button;
	r.origin = data->camera.origin;
	r.direction = data->camera.ray_direction[y * WIDTH + x];
	h = ray_hit(r);
	if (h.object)
		return (0);
	return (0);
}
