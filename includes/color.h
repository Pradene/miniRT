#ifndef COLOR_H
# define COLOR_H

typedef float rgba __attribute__((ext_vector_type(4)));

rgba    color(float r, float g, float b, float a);

rgba    atocolor(char *s);

int     colortoi(rgba c);

#endif