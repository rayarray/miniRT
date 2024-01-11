/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:41:27 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 13:57:03 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec_distance(t_vec a, t_vec b)
{
	double	distance;

	distance = sqrt(pow(a.x - b.x, 2)
			+ pow(a.y - b.y, 2)
			+ pow(a.z - b.z, 2));
	return (distance);
}

double	vec_length(t_vec a)
{
	return (sqrt(fma(a.x, a.x, fma(a.y, a.y, fma(a.z, a.z, 0)))));
}

t_vec	vec_scal_div(t_vec a, double div)
{
	return ((t_vec){a.x / div, a.y / div, a.z / div});
}

// unused
// int	vec_eq(t_vec a, t_vec b)
// {
// 	return (feq(a.x, b.x) && feq(a.y, b.y) && feq(a.z, b.z));
// }

double	dot_product(t_vec a, t_vec b)
{
	return (fma(a.x, b.x, fma(a.y, b.y, fma(a.z, b.z, 0))));
}

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	normal;

	normal.x = a.y * b.z - a.z * b.y;
	normal.y = a.z * b.x - a.x * b.z;
	normal.z = a.x * b.y - a.y * b.x;
	return (normal);
}
