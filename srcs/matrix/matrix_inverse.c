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

void	mat_adjugate(t_mat44 m, t_mat44 *tmp)
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

void	mat_transpose(t_mat44 *m)
{
	int		i;
	int		j;
	t_mat44	cp;

	cp = mat_copy(*m);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			(*m)[i][j] = cp[j][i];
	}
}

t_mat44	mat_inverse(t_mat44 m)
{
	float	det;
	t_mat44	tmp;
	t_mat44	res;

	tmp = mat();
	res = mat();
	det = mat4_determinant(m);
	if (det == 0)
		return (res);
	mat_adjugate(m, &tmp);
	mat_transpose(&tmp);
	res = 1.0 / det * tmp;
	return (res);
}
