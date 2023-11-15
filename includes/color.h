#ifndef COLOR
# define COLOR

typedef struct s_color
{
    float   r;
    float   g;
    float   b;
    float   a;
}   t_color;

t_color color(float r, float g, float b, float a);

t_color atocolor(char *s);

#endif