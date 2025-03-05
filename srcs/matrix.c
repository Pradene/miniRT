#include "minirt.h"

Matrix4	mat(void) {
	Matrix4	m;
	int		i;
	int		j;

	i = -1;
	while (++i < 4) {
		j = -1;
		while (++j < 4) {
			m[i][j] = 0;
			if (i == j) {
				m[i][j] = 1;
			}
		}
	}

	return (m);
}

void	mat_print(Matrix4 m) {
	int		i;
	int		j;

	i = -1;
	while (++i < 4) {
		j = -1;
		while (++j < 4) {
			printf("%lf ", m[i][j]);
		}
	
		printf("\n");
	}

	printf("\n");
}

Matrix4	mat_copy(Matrix4 m) {
	Matrix4	res;
	int		i;
	int		j;

	i = -1;
	while (++i < 4) {
		j = -1;
		while (++j < 4) {
			res[i][j] = m[i][j];
		}
	}

	return (res);
}

Vector	mat_vec_product(Matrix4 m, Vector v) {
	Vector	res;

	res.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	res.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
	res.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
	res.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
	return (res);
}

Matrix4	mat_product(Matrix4 m, Matrix4 n) {
	Matrix4	res;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 4) {
		j = -1;
		while (++j < 4) {
			k = -1;
			res[i][j] = 0;
			while (++k < 4) {
				res[i][j] += m[i][k] * n[k][j];
            }
		}
	}

	return (res);
}


void	mat_adjugate(Matrix4 m, Matrix4 *tmp) {
	int	i;
	int	j;

	i = -1;
	while (++i < 4) {
		j = -1;
		while (++j < 4) {
			(*tmp)[i][j] = powf(-1, i + j) * cofactor(m, i, j);
		}
	}
}

void	mat_transpose(Matrix4 *m) {
	int		i;
	int		j;
	Matrix4	cp;

	cp = mat_copy(*m);
	i = -1;
	while (++i < 4) {
		j = -1;
		while (++j < 4) {
			(*m)[i][j] = cp[j][i];
		}
	}
}

Matrix4	mat_inverse(Matrix4 m) {
	float	det;
	Matrix4	tmp;
	Matrix4	res;

	tmp = mat();
	res = mat();
	det = mat_determinant(m);
	if (det == 0)
		return (res);
	mat_adjugate(m, &tmp);
	mat_transpose(&tmp);
	res = 1.0 / det * tmp;
	return (res);
}

float	mat3_determinant(Matrix3 m) {
	return (
		m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - 
		m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) +
		m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1])
	);
}

float	cofactor(Matrix4 m, int r, int c) {
	Matrix3	tmp;
	int		i;
	int		j;
	int		row;
	int		col;

	row = -1;
	i = 0;
	j = 0;
	while (++row < 4) {
		col = -1;
		while (++col < 4) {
			if (row == r || col == c) {
				continue ;
			}

			tmp[i][j++] = m[row][col];
			j = j % 3;
			if (j == 0) {
				i++;
			}
		}
	}

	return (mat3_determinant(tmp));
}

float	mat_determinant(Matrix4 m) {
	int		i;
	float	res;

	res = 0;
	i = -1;
	while (++i < 4) {
		res += m[0][i] * powf(-1, i) * cofactor(m, 0, i);
	}

	return (res);
}
