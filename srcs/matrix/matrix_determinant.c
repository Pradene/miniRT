/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:25:32 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 15:25:35 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

float	mat3_determinant(t_mat33 m)
{
	return (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) \
	- m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) \
	+ m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]));
}

float	cofactor(t_mat44 m, int r, int c)
{
	t_mat33	tmp;
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

float	mat4_determinant(t_mat44 m)
{
	int		i;
	float	res;

	res = 0;
	i = -1;
	while (++i < 4)
		res += m[0][i] * powf(-1, i) * cofactor(m, 0, i);
	return (res);
}
