/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:53:18 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/06 16:44:33 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "float.h"

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	imin(int a, int b)
{
	if (b < a)
		return (b);
	return (a);
}

// https://floating-point-gui.de/errors/comparison/
int	feq(double a, double b)
{
	double	abs_a;
	double	abs_b;
	double	diff;

	abs_a = fabs(a);
	abs_b = fabs(b);
	diff = fabs(a - b);
	if (a == b)
		return (1);
	if (a == 0 || b == 0 || (abs_a + abs_b < DBL_MIN))
		return (diff < RT_EPSILON * DBL_MIN);
	return (diff / fmin(abs_a + abs_b, DBL_MIN) < RT_EPSILON);
}

int	flessthan(double a, double b)
{
	if (feq(a, b))
		return (0);
	return (a < b);
}

int	fgreaterthan(double a, double b)
{
	if (feq(a, b))
		return (0);
	return (a > b);
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
	return (sqrt(fma(a.x, a.x, fma(a.y, a.y, fma(a.z, a.z, 0)))));
}

int	vec_eq(t_vec a, t_vec b)
{
	return (feq(a.x, b.x) && feq(a.y, b.y) && feq(a.z, b.z));
}

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

int	quadratic_solver(double a, double b, double c, double solutions[2])
{
	double	discriminant;
	double	q;
	double	tmp;
	int		solution_count;

	solution_count = 0;
	discriminant = b * b - 4 * a * c;
	if (feq(b * b, 4 * a * c))
		solutions[solution_count++] = -b / (2 * a);
	if (fgreaterthan(discriminant, 0))
	{
		if (fgreaterthan(b, 0))
			q = (-b - sqrt(discriminant)) / 2;
		else
			q = (-b + sqrt(discriminant)) / 2;
		solutions[solution_count++] = q / a;
		solutions[solution_count++] = c / q;
		if (fgreaterthan(solutions[0], solutions[1]))
		{
			tmp = solutions[0];
			solutions[0] = solutions[1];
			solutions[1] = tmp;
		}
	}
	return (solution_count);
}
