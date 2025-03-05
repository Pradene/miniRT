#include "minirt.h"

void	vector_print(Vector v) {
	printf("%f %f %f\n", v.x, v.y, v.z);
}

Vector vector(float x, float y, float z) {
    Vector   vector;

    vector.x = x;
    vector.y = y;
    vector.z = z;
    vector.w = 0.0f;
    
    return (vector);
}

int	atovector(char *s, Vector *v) {
	char	*tmp;
	char	**args;

	*v = vector(0, 0, 0);
	args = ft_split(s, ',');
	if (!args) {
		return (0);
    }

	if (size_strings(args) != 3) {
		return (free_strings(args), 0);
    }

	v->x = ft_atof(args[0], &tmp);
	if (tmp != args[0] + ft_strlen(args[0])) {
		return (free_strings(args), 0);
    }

	v->y = ft_atof(args[1], &tmp);
	if (tmp != args[1] + ft_strlen(args[1])) {
		return (free_strings(args), 0);
    }

	v->z = ft_atof(args[2], &tmp);
	if (tmp != args[2] + ft_strlen(args[2])) {
		return (free_strings(args), 0);
    }

	free_strings(args);
	return (1);
}