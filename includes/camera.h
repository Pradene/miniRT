/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:53 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:00:03 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "matrix.h"

# define WIDTH 1080
# define HEIGHT 720
# define ASPECT_RATIO (1080 / 720)

typedef struct s_camera
{
	int		created;
	vec3	origin;
	vec3	direction;
	int		fov;
	mat44	m_projection;
	mat44	m_inverse_projection;
	mat44	m_view;
	mat44	m_inverse_view;
	vec3	ray_direction[HEIGHT * WIDTH];
}	t_camera;

int		camera(char **args);

void	rotate_camera(t_camera *cam, float angle_x, float angle_y);

void	view_matrix(t_camera *cam, vec3 forward);
void	calculate_m_view(t_camera *cam);
void	calculate_rays(t_camera *cam);

quat	multiply_quat(quat q1, quat q2);
quat	angle_axis(float angle, vec3 axis);
vec3	rotate(vec3 v, quat rotationQuat);
quat	normalize_quat(quat q);
void	quaternionToMatrix(quat q, mat44 *m);
mat44	translate(t_camera *cam);

#endif
