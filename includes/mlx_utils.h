/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:24 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:56:26 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

typedef struct s_image
{
	void	*image;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

#endif
