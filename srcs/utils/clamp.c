/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:46:36 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:46:37 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

// This fucntion clamp the number between 2 values
float	clamp(float value, float min, float max)
{
	return (fmaxf(min, fminf(value, max)));
}
