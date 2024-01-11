/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:32:10 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"
#include "rt_math_bonus.h"

t_vec	vec_normalize(t_vec a)
{
	double	norm;
	t_vec	unit_vector;

	norm = sqrt(fma(a.x, a.x, fma(a.y, a.y, fma(a.z, a.z, 0))));
	if (feq(norm, 0))
		return (a);
	unit_vector.x = a.x / norm;
	unit_vector.y = a.y / norm;
	unit_vector.z = a.z / norm;
	return (unit_vector);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec	vec_neg(t_vec a)
{
	return ((t_vec){-a.x, -a.y, -a.z});
}

t_vec	vec_scal_mul(t_vec a, double s)
{
	a.x *= s;
	a.y *= s;
	a.z *= s;
	return (a);
}
