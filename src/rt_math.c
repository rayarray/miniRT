/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:53:18 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/15 17:13:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

double	vec_distance(t_vector a, t_vector b)
{
	double	distance;

	distance = sqrt(pow(a.x - b.x, 2)
			+ pow(a.y - b.y, 2)
			+ pow(a.z - b.z, 2));
	return (distance);
}

double	vec_length(t_vector a)
{
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

t_vector	vec_normalize(t_vector a)
{
	double		norm;
	t_vector	unit_vector;

	norm = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	unit_vector.x = a.x / norm;
	unit_vector.y = a.y / norm;
	unit_vector.z = a.z / norm;
	return (unit_vector);
}

double	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector	normal;

	normal.x = a.y * b.z - a.z * b.y;
	normal.y = a.z * b.x - a.x * b.z;
	normal.z = a.x * b.y - a.y * b.x;
	return (normal);
}

t_vector	vec_add(t_vector a, t_vector b)
{
	return (t_vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vector	vec_sub(t_vector a, t_vector b)
{
	return (t_vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vector	vec_neg(t_vector a)
{
	return (t_vector){-a.x, -a.y, -a.z};
}
