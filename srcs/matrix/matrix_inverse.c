/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:43:02 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 11:44:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

float	mat3_determinant(mat33 m)
{
	return (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) \
	- m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) \
	+ m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]));
}

float	cofactor(mat44 m, int r, int c)
{
	mat33	tmp;
	int		i;
	int		j;
	int		row;
	int		col;

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
	return (mat3_determinant(tmp));
}

float	mat4_determinant(mat44 m)
{
	int		i;
	float	res;

	res = 0;
	i = -1;
	while (++i < 4)
		res += m[0][i] * powf(-1, i) * cofactor(m, 0, i);
	return (res);
}

void	mat_adjugate(mat44 m, mat44 *tmp)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			(*tmp)[i][j] = powf(-1, i + j) * cofactor(m, i, j);
	}
}

void	mat_transpose(mat44 *m)
{
	int		i;
	int		j;
	mat44	cp;

	cp = mat_copy(*m);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			(*m)[i][j] = cp[j][i];
	}
}

mat44	mat_inverse(mat44 m)
{
	float	det;
	mat44	tmp;
	mat44	res;
	int		i;
	int		j;

	tmp = mat();
	res = mat();
	det = mat4_determinant(m);
	if (det == 0)
		return (res);
	mat_adjugate(m, &tmp);
	mat_transpose(&tmp);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res[i][j] = (float)1 / det * tmp[i][j];
	}
	return (res);
}
