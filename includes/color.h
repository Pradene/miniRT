/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:02 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 13:03:05 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef float	t_rgba __attribute__((ext_vector_type(4)));

t_rgba	color(float r, float g, float b, float a);

t_rgba	atocolor(char *s);

int		colortoi(t_rgba c);
t_rgba	itocolor(int c);

#endif
