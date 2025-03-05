#include "minirt.h"

int	size_strings(char **strings) {
	int	i;

	if (!strings) {
		return (0);
    }

	i = -1;
	while (strings[++i]);
	return (i);
}

void    free_strings(char **strings) {
    int	i;

	if (!strings) {
		return ;
    }

	i = -1;
	while (strings[++i]) {
		free(strings[i]);
    }

	free(strings);
	strings = NULL;
}

void	copy_strings(char **dest, char **src) {
	int	i;

	if (!src) {
		return ;
    }

	i = -1;
	while (src[++i]) {
		dest[i] = src[i];
    }

	dest[i] = NULL;
}

float	dot(const Vector v1, const Vector v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vector	normalize(const Vector v) {
	float	magnitude;
	float	d;
	Vector	res;

	d = dot(v, v);
	magnitude = sqrt(d);
	if (magnitude == 0) {
		return (v);
    }

	res.x = v.x / magnitude;
	res.y = v.y / magnitude;
	res.z = v.z / magnitude;
	return (res);
}

float	radian(float angle) {
	return (angle * (PI / 180));
}

float	clamp(float value, float min, float max) {
	return (fmaxf(min, fminf(value, max)));
}

float	distance(Point p1, Point p2) {
	return (
        sqrt(
            powf(p2.x - p1.x, 2.0) + 
            powf(p2.y - p1.y, 2.0) +
            powf(p2.z - p1.z, 2.0)
        )
    );
}

float	closest_distance(Vector d) {
	float	t;

	t = (-d.y - sqrt(d.w)) / (2.0 * d.x);
	if (t < 0) {
		t = (-d.y + sqrt(d.w)) / (2.0 * d.x);
    }

	return (t);
}

float	map(float v, float minr, float maxr, float minnr, float maxnr) {
	return ((v - minr) / (maxr - minr) * (maxnr - minnr) + minnr);
}

Vector	cross(const Vector v1, const Vector v2) {
	Vector	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}