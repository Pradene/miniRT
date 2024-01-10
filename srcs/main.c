/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:51:38 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:52:41 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

// This function initialize a sort of global structure data and return it
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	initialisation(void)
{
	t_data	*data;

	data = get_data();
	data->objects = NULL;
	data->camera.created = 0;
	data->light.created = 0;
	data->alight.created = 0;
}

int	free_data(void)
{
	t_data	*data;

	data = get_data();
	free_objects(&data->objects);
	if (data->id && data->img.image)
		mlx_destroy_image(data->id, data->img.image);
	if (data->id && data->win)
		mlx_destroy_window(data->id, data->win);
	if (data->id)
		mlx_destroy_display(data->id);
	free(data->id);
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2 || !ft_strrcmp(av[1], ".rt"))
	{
		printf("Error: You have to run the program with: ./minirt map.rt\n");
		return (1);
	}
	initialisation();
	if (parsing(av[1]))
		return (1);
	renderer("miniRT");
	render();
	free_data();
	return (0);
}
