#include "minirt.h"

int	light(Scene *scene, char **args) {
	char	*tmp;
	Light	*light;

	if (size_strings(args) != 4) {
		return (0);
    }

	if (scene->light) {
		return (0);
    }

    light = malloc(sizeof(Light));
    if (!light) {
        return (0);
    }

	if (!atopoint(args[1], &light->origin)) {
		return (0);
    }

	light->intensity = ft_atof(args[2], &tmp);
	if (tmp != args[2] + ft_strlen(args[2])) {
		return (0);
    }

	light->color = atocolor(args[3]);
    if (!check_light(*light)) {
		return (0);
    }

	scene->light = light;
	return (1);
}
