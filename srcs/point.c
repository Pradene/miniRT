#include "minirt.h"

void	point_print(Point p) {
	printf("%f %f %f\n", p.x, p.y, p.z);
}

Point point(float x, float y, float z) {
    Point   point;

    point.x = x;
    point.y = y;
    point.z = z;
    point.w = 1.0f;
    
    return (point);
}

int	atopoint(char *s, Point *v) {
	char	*tmp;
	char	**args;

	*v = point(0, 0, 0);
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