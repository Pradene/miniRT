#include "../../includes/rt.h"

float   *mat(int size)
{
    int     i;
    int     j;
    float   *m;

    m = malloc(sizeof(float) * (size * size));
    if (!m)
        return (NULL);
    i = -1;
    while (++i < size)
    {
        j = -1;
        while (++j < size)
        {
            m[i * size + j] = 0.0;
        }
    }
    return (m);
}

void    replace_line(float **m, int index)
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

float   *increased_mat(float *m)
{
    int     i;
    int     j;
    float   *t;

    t = (float *)malloc(sizeof(float) * (4 * 4 * 2));
    if (!t)
        return (NULL);
    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
        {
            if (i == j)
                t[i * 8 + j + 4] = 1;
            else
                t[i * 8 + j + 4] = 0;
            t[i * 8 + j] = m[i * 4 + j];
        }
    }
    return (t);
}

void    inverse_mat_calcul(float **m)
{
    int     i;
    int     j;
    int     k;
    float   pivot;
    float   factor;

    i = -1;
    while (++i < 4)
    {
        pivot = (*m)[i * 8 + i];
        if (pivot == 0)
        {
            replace_line(m, i);
            pivot = (*m)[i * 8 + i];
        }
        j = -1;
        while (++j < 4 * 2)
            if (pivot != 0)
                (*m)[i * 8 + j] /= pivot;
        k = -1;
        while (++k < 4)
        {
            if (k != i)
            {
                factor = (*m)[k * 8 + i];
                j = -1;
                while (++j < 4 * 2)
                    (*m)[k * 8 + j] -= factor * (*m)[i * 8 + j];
            }
        }
    }
}

void    inverse_mat(float *m, float **res)
{
    int     i;
    int     j;
    float   *tmp;

    tmp = increased_mat(m);
    if (!tmp)
        return ;
    inverse_mat_calcul(&tmp);
    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            (*res)[i * 4 + j] = tmp[i * 8 + j + 4];
    }
    free(tmp);
}
