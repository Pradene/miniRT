#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
    float   r;
    float   g;
    float   b;
    float   a;
}   t_color;

t_color color(float r, float g, float b, float a);

t_color atocolor(char *s);

int rgba_to_color(t_color c);

#endif