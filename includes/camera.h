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

typedef struct s_camera
{
	int		created;
	t_vec3	origin;
	t_vec3	direction;
	int		fov;
	t_mat44	m_projection;
	t_mat44	m_inverse_projection;
	t_mat44	m_view;
	t_mat44	m_inverse_view;
	t_vec3	ray_direction[HEIGHT * WIDTH];
}	t_camera;

void	rotate_camera(t_camera *cam, float angle_x, float angle_y);

void	view_matrix(t_camera *cam, t_vec3 forward);
void	calculate_m_view(t_camera *cam);
void	calculate_rays(t_camera *cam);

t_quat	normalize_quat(t_quat q);
t_quat	multiply_quat(t_quat q1, t_quat q2);
t_quat	angle_axis(float angle, t_vec3 axis);
t_vec3	rotate(t_vec3 v, t_quat rotationt_Quat);

#endif
