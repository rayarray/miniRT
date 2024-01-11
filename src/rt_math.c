/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:53:18 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 13:40:33 by rleskine         ###   ########.fr       */
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

t_plane_eq	plane_eq(t_point3 loc, t_vec normal)
{
	t_plane_eq	plane;

	plane.a = normal.x;
	plane.b = normal.y;
	plane.c = normal.z;
	plane.d = -(normal.x * loc.x + normal.y * loc.y + normal.z * loc.z);
	return (plane);
}
