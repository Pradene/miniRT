#include "minirt.h"

int	ambient(Scene *scene, char **args) {
	char			*tmp;
	AmbientLight	*ambient;

	if (size_strings(args) != 3) {
		return (0);
    }

	if (scene->ambient) {
		return (0);
    }

    ambient = malloc(sizeof(AmbientLight));
    if (!ambient) {
        return (0);
    }

	ambient->intensity = ft_atof(args[1], &tmp);
	if (tmp != args[1] + ft_strlen(args[1])) {
        return (0);
    }
    
	ambient->color = atocolor(args[2]);

	if (!check_ambient(*ambient)) {
		return (0);
    }

	scene->ambient = ambient;
	return (1);
}