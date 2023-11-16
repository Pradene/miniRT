#include "../../includes/rt.h"

void    replace_line(float *m[], int index)
{
    int     r;
    int     i;
    float   tmp;

    r = index;
    while (r < 4)
    {
        if ((*m)[r * 8 + index] != 0)
        {
            i = -1;
            while (++i < 8)
            {
                tmp = (*m)[r * 8 + i];
                (*m)[r * 8 + i] = (*m)[index * 8 + i];
                (*m)[index * 8 + i] = tmp;
            }
            break ;
        }
        ++r;
    }
}

void    inverse_mat(t_mat m, t_mat *res)
{
    int     i;
    int     j;
    int     k;
    float   pivot;
    float   factor;
    float   *tmp;

    (void)res;
    tmp = malloc(sizeof(float) * (4 * 8));
    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
        {
            if (i == j)
                tmp[i * 8 + j + 4] = 1;
            else
                tmp[i * 8 + j + 4] = 0;
            tmp[i * 8 + j] = m.array[i * 4 + j];
        }
    }

    i = -1;
    while (++i < 4)
    {
        pivot = tmp[i * 8 + i];
        if (pivot == 0)
        {
            replace_line(&tmp, i);
            pivot = tmp[i * 8 + i];
        }
        j = -1;
        while (++j < 4 * 2)
        {
            if (pivot != 0)
                tmp[i * 8 + j] /= pivot;
        }
        k = -1;
        while (++k < 4)
        {
            if (k != i)
            {
                factor = tmp[k * 8 + i];
                j = -1;
                while (++j < 4 * 2)
                    tmp[k * 8 + j] -= factor * tmp[i * 8 + j];
            }
        }
    }
}
