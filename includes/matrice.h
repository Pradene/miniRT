#ifndef MATRICE
# define MATRICE

typedef struct s_mat
{
    float   array[4 * 4];
}   t_mat;

void    inverse_mat(t_mat m, t_mat *res);

#endif