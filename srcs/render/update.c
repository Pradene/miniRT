/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:44:38 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:44:55 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	randomize(vec3 *v)
{
	float	r;

	r = ((float)rand() / (float)RAND_MAX - 0.5) * 0.01 + 1;
	v->x *= r;
	r = ((float)rand() / (float)RAND_MAX - 0.5) * 0.01 + 1;
	v->y *= r;
	*v = normalize(*v);
}

int	get_pixel(t_image *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(int *)pixel);
}

// This function send rays for every pixels
// to get the color and put it on the screen
void	trace(t_image *img, t_camera *cam)
{
	int		i;
	int		frame;
	t_ray	ray;
	rgba	color;
	rgba	last;

	i = -1;
	frame = get_data()->frame;
	ray.origin = cam->origin;
	while (++i < HEIGHT * WIDTH)
	{
		ray.direction = cam->ray_direction[i];
		randomize(&ray.direction);
		color = intersect(ray);
		if (frame > 1)
		{
			last = itocolor(get_pixel(img, i % WIDTH, i / WIDTH));
			color = (color * (1.0 / frame) + last * (1.0 - 1.0 / frame));
		}
		pixel_put(img, i % WIDTH, i / WIDTH, color);
	}
}

// This function gives the time in ms since the last frame
float	get_elapsed_time(void)
{
	float			elapsed_time;
	struct timeval	tv;
	long			time;
	static long		last_frame = 0;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	elapsed_time = time - last_frame;
	last_frame = time;
	return (elapsed_time);
}

// This function is called every frame to render things on screen
int	update(t_data *data)
{
	if (!data->win)
		return (1);
	data->frame += 1;
	data->et = get_elapsed_time();
	trace(&data->img, &data->camera);
	mlx_put_image_to_window(data->id, data->win, data->img.image, 0, 0);
	return (0);
}
