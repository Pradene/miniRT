#include "../../includes/rt.h"

void    mat_print(mat44 m)
{
    int     i;
    int     j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            printf("%lf ", m[i][j]);
        printf("\n");
    }
    printf("\n");
}

void    mat(mat44 *m)
{
    int     i;
    int     j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            (*m)[i][j] = 0;
    }
}

void    mat_copy(mat44 m, mat44 *cp)
{
    int     i;
    int     j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            (*cp)[i][j] = m[i][j];
    }
}


float determinant3x3(mat33 m) {
    return (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
          - m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2])
          + m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]));
}

float   cofactor(mat44 m, int r, int c)
{
    mat33   tmp;
    int     i;
    int     j;
    int     row;
    int     col;

    row = -1;
    i = 0;
    j = 0;
    while (++row < 4)
    {
        col = -1;
        while (++col < 4)
        {
            if (row == r || col == c)
                continue ;
            tmp[i][j++] = m[row][col];
            j = j % 3;
            if (j == 0)
                i++;
        }
    }
    return (determinant3x3(tmp));
}

float   determinant(mat44 m)
{
    int     i;
    float   res;

    res = 0;
    i = -1;
    while (++i < 4)
        res += m[0][i] * powf(-1, i) * cofactor(m, 0, i);
    return (res);
}

void    adjugate(mat44 m, mat44 *tmp)
{
    int i;
    int j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            (*tmp)[i][j] = powf(-1, i + j) * cofactor(m, i, j);
    }
}

void    transpose(mat44 *m)
{
    int     i;
    int     j;
    mat44   cp;

    mat_copy(*m, &cp);
    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            (*m)[i][j] = cp[j][i];
    }
}

bool    mat_inverse(mat44 m, mat44 *inv)
{
    float   det;
    mat44   tmp;
    int     i;
    int     j;

    det = determinant(m);
    if (det == 0)
        return (false);
    adjugate(m, &tmp);
    transpose(&tmp);

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
        {
            (*inv)[i][j] = (float)1 / det * tmp[i][j];
        }
    }
    return (true);
}