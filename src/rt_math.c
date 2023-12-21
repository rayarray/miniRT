/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:53:18 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/21 13:38:57 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int imin(int a, int b)
{
	if (b < a)
		return (b);
	return (a);
}

int	feq(double a, double b)
{
	return (fabs(a - b) <= RT_EPSILON);
}

int	flessthan(double a, double b)
{
	return (a < b + RT_EPSILON);
}

int	fgreaterthan(double a, double b)
{
	return (a > b - RT_EPSILON);
}

int	fleq(double a, double b)
{
	return (feq(a, b) || flessthan(a, b));
}

int	fgeq(double a, double b)
{
	return (feq(a, b) || fgreaterthan(a, b));
}

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
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

t_vec	vec_normalize(t_vec a)
{
	double	norm;
	t_vec	unit_vector;

	norm = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	unit_vector.x = a.x / norm;
	unit_vector.y = a.y / norm;
	unit_vector.z = a.z / norm;
	return (unit_vector);
}

double	dot_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	normal;

	normal.x = a.y * b.z - a.z * b.y;
	normal.y = a.z * b.x - a.x * b.z;
	normal.z = a.x * b.y - a.y * b.x;
	return (normal);
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

t_plane_eq	plane_eq(t_point3 loc, t_vec normal)
{
	t_plane_eq	plane;

	plane.a = normal.x;
	plane.b = normal.y;
	plane.c = normal.z;
	plane.d = -(loc.x + loc.y + loc.z);
	//plane.d = (normal.x * loc.x + normal.y * loc.y + normal.z * loc.z);
	return (plane);
}
