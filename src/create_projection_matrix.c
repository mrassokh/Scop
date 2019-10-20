/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_projection_matrix.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:12:46 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/11 15:12:48 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

float		*create_projection_matrix(float fop, float asp, float near,
																	float far)
{
	float	*projection_matrix;
	float	angle;

	angle = ANGLE * fop;
	if (!fop && !asp && !near && !far)
		return (NULL);
	projection_matrix = (float*)malloc(sizeof(float) * 16);
	ft_memset(projection_matrix, 0, sizeof(float) * 16);
	projection_matrix[0] = asp / tan(angle / 2);
	projection_matrix[5] = 1 / tan(angle / 2);
	projection_matrix[10] = (far + near) / (far - near);
	projection_matrix[11] = 1;
	projection_matrix[14] = -2 * far * near / (far - near);
	projection_matrix[15] = 1;
	return (projection_matrix);
}
