#include "minirt.h"

void	renderer(char *name) {
	Scene	*scene;

	scene = get_scene();
	scene->win = NULL;
	scene->img.image = NULL;
	scene->img.data = NULL;
	scene->id = mlx_init();
	if (!scene->id) {
		free_scene();
    }

	scene->win = mlx_new_window(scene->id, WIDTH, HEIGHT, name);
	scene->img.image = mlx_new_image(scene->id, WIDTH, HEIGHT);
	scene->img.data = mlx_get_data_addr(
        scene->img.image, \
        &scene->img.bpp, \
		&scene->img.size_line, \
        &scene->img.endian
    );
}

int	get_pixel(Image *img, int x, int y) {
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		return (0);
    }

	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(int *)pixel);
}

void	pixel_put(Image *img, int x, int y, Color c) {
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		return ;
    }

	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = colortoi(c);
}

void	trace(Image *img, Camera *cam) {
	int		i;
	int		frame;
    Ray 	ray;
	Color	color;
	Color	last;

	i = -1;
	frame = get_scene()->frame;
	ray.origin = cam->origin;
	while (++i < HEIGHT * WIDTH) {
		ray.direction = cam->ray_direction[i];
		color = intersect(ray);
		if (frame > 1) {
			last = itocolor(get_pixel(img, i % WIDTH, i / WIDTH));
			color = (color * (1.0 / frame) + last * (1.0 - 1.0 / frame));
		}

		pixel_put(img, i % WIDTH, i / WIDTH, color);
	}
}

float	get_elapsed_time(void) {
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

int	update(Scene *scene) {
	if (!scene->win) {
		return (1);
    }

	scene->frame += 1;
	scene->elapsed = get_elapsed_time();

	trace(&scene->img, scene->camera);
	mlx_put_image_to_window(scene->id, scene->win, scene->img.image, 0, 0);
	return (0);
}

void	render(void) {
	Scene	*scene;

	scene = get_scene();
	mlx_loop_hook(scene->id, &update, scene);
	mlx_hook(scene->win, 2, 1L << 0, &key, scene);
	mlx_hook(scene->win, 17, 0, &free_scene, scene);
	mlx_loop(scene->id);
}
