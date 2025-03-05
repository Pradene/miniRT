#include "minirt.h"

Color	color(float r, float g, float b, float a) {
	Color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

Color	atocolor(char *s) {
	Color	c;
	float	f;
	char	*tmp;
	char	**colors;

	colors = ft_split(s, ',');
	if (!colors) {
		return (color(-1, -1, -1, -1));
    }

	if (size_strings(colors) != 3) {
		free_strings(colors);
        return (color(-1, -1, -1, -1));
    }

	f = ft_atof(colors[0], &tmp);
	if (tmp != colors[0] + ft_strlen(colors[0])) {
		return (color(-1, -1, -1, -1));
    }

	c.r = (f / (float)255);
	f = ft_atof(colors[1], &tmp);
	if (tmp != colors[1] + ft_strlen(colors[1])) {
		return (color(-1, -1, -1, -1));
    }

	c.g = (f / (float)255);
	f = ft_atof(colors[2], &tmp);
	if (tmp != colors[2] + ft_strlen(colors[2])) {
		return (color(-1, -1, -1, -1));
    }

	c.b = (f / (float)255);
	free_strings(colors);

    c.a = 1.0;
	return (c);
}

int	colortoi(Color c) {
	int	color;

	c.r = clamp(c.r, 0.0, 1.0);
	c.g = clamp(c.g, 0.0, 1.0);
	c.b = clamp(c.b, 0.0, 1.0);
	c.a = clamp(c.a, 0.0, 1.0);
	color = ((int)(c.a * 255) << 24) |
            ((int)(c.r * 255) << 16) |
            ((int)(c.g * 255) << 8) |
            ((int)(c.b * 255) << 0);
	return (color);
}

Color	itocolor(int c) {
	Color	color;

	color.a = (float)((c >> 24) & 0xFF) / 255.0;
	color.r = (float)((c >> 16) & 0xFF) / 255.0;
	color.g = (float)((c >> 8) & 0xFF) / 255.0;
	color.b = (float)((c >> 0) & 0xFF) / 255.0;
	return (color);
}