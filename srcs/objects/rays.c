/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:39:21 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:39:23 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	calculate_rays(t_camera *cam)
{
	int		i;
	float	x;
	float	y;
	t_vec4	tmp;
	t_vec3	r;

	i = -1;
	while (++i < HEIGHT * WIDTH)
	{
		x = map(i % WIDTH + 0.5, vector2(0, WIDTH), vector2(-1, 1));
		y = map(i / WIDTH + 0.5, vector2(0, HEIGHT), vector2(-1, 1));
		tmp = mat_vec_product(cam->m_inverse_projection, vector4(x, y, 1, 1));
		r = normalize(tmp.xyz / tmp.w);
		tmp = mat_vec_product(cam->m_inverse_view, vector4(r.x, r.y, r.z, 0));
		r = tmp.xyz;
		cam->ray_direction[i] = r;
	}
}
