/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:42:31 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 11:42:32 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_mat44	mat(void)
{
	t_mat44	m;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			m[i][j] = 0;
			if (i == j)
				m[i][j] = 1;
		}
	}
	return (m);
}

void	mat_print(t_mat44 m)
{
	int		i;
	int		j;

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

t_mat44	mat_copy(t_mat44 m)
{
	t_mat44	res;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res[i][j] = m[i][j];
	}
	return (res);
}

t_vec4	mat_vec_product(t_mat44 m, t_vec4 v)
{
	t_vec4	res;

	res.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	res.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
	res.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
	res.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
	return (res);
}

t_mat44	mat_product(t_mat44 m, t_mat44 n)
{
	t_mat44	res;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			res[i][j] = 0;
			while (++k < 4)
				res[i][j] += m[i][k] * n[k][j];
		}
	}
	return (res);
}
