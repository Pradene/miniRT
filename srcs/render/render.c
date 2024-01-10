/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:43:40 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:43:54 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

// This function define how to interact with the window
void	render(void)
{
	t_data	*data;

	data = get_data();
	calculate_rays(&data->camera);
	mlx_loop_hook(data->id, &update, data);
	mlx_hook(data->win, 2, 1L << 0, &key, data);
	mlx_hook(data->win, 4, 1L << 2, &mouse, data);
	mlx_hook(data->win, 17, 0, &free_data, data);
	mlx_loop(data->id);
}
