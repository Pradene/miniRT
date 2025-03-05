#include "minirt.h"

ObjectType  get_object_type(char *type)
{
	int					i;
	static const char	*types[] = {
        "C",
        "A",
        "L",
        "sp",
        "pl",
        "cy",
        NULL
    };

	if (!type) {
		return (ERROR);
    }

	i = -1;
	while (types[++i]) {
		if (!ft_strcmp(types[i], type)) {
			return (i + 1);
        }
	}

	return (ERROR);
}

int	create_object_type(Scene *scene, ObjectType type, char **args) {
	if (type == CAMERA) {
		return camera(scene, args);
	} else if (type == AMBIENT) {
		return ambient(scene, args);
	} else if (type == LIGHT) {
		return light(scene, args);
	} else if (type == SPHERE) {
		return sphere(scene, args);
	} else if (type == CYLINDER) {
		return cylinder(scene, args);
	} else if (type == PLANE) {
		return plane(scene, args);
	}

	return (0);
}

int	create_object(Scene *scene, char *line) {
	char		**args;
	ObjectType	type;
	int			status;

	if (!line) {
		return (0);
    }

	args = ft_split(line, ' ');
	if (!args) {
		return (0);
    }

	if (!args[0]) {
        return (free_strings(args), 1);
    }

	type = get_object_type(args[0]);
	if (type == ERROR) {
		return (free_strings(args), 0);
    }

	status = create_object_type(scene, type, args);
	free_strings(args);
	return (status);
}

int	create_objects(char **strings) {
	Scene	*scene;
	int		i;

	if (!strings) {
		return (1);
    }

	i = -1;
	scene = get_scene();
	while (strings[++i]) {
		if (!create_object(scene, strings[i])) {
			return (1);
        }
	}

	return (0);
}