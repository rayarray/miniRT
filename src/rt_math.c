/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:53:18 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/03 21:02:58 by tsankola         ###   ########.fr       */
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

#include <stdio.h>
/* 
int	quadra(double a, double b, double c, double solutions[2])
{	// For testing, can be deleted
	double tmp;
	double discriminant = pow(b, 2) - 4 * a * c;

	if (flessthan(discriminant, 0) || feq(a, 0))
		return 0;
	if (feq(discriminant, 0)) {
		solutions[0] = -b / (2 * a);
		return 1;
	}
	solutions[0] = (-b - sqrt(discriminant)) / 2 * a;
	solutions[1] = (-b + sqrt(discriminant)) / 2 * a;
	if (fgreaterthan(solutions[0], solutions[1]))
	{
		tmp = solutions[0];
		solutions[0] = solutions[1];
		solutions[1] = tmp;
	}
	return 2;
} */

// Calculates solutions of a quadratic equation, stores the possible solutions
// in results in ascending order and returns the number of solutions.
int	quadratic_solver(double a, double b, double c, double solutions[2])
{
	double	discriminant;
	double	q;
	double	tmp;
	int		solution_count;
	
	solution_count = 0;
//	if (feq(a, 0))
//		return (0);
	discriminant = pow(b, 2) - 4 * a * c;
	if (feq(discriminant, 0))	// one solution
		solutions[solution_count++] = -b / (2 * a);
	else if (fgreaterthan(discriminant, 0)) // two solutions
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
		if (isnan(solutions[0]) || isnan(solutions[1]))
		{
			printf("Fucking nan\n");
			printf("%f %f %f\n", a, b, c);
			printf("%f\n", solutions[1]);
			printf("disc %f\n", discriminant);
			getchar();
		}
	}

/* 	double sols[2];
	int p;
	p = quadra(a, b, c, sols);

	if (p != solution_count)
		printf("solutions: %d p %d\n", solution_count, p);
	else if (p != 0)
	{
		if (p == 2 && sols[1] != solutions[1])
			printf("diff: %f %f\n", sols[1], solutions[1]);
		if (sols[0] != solutions[0])
			printf("diff: %f %f\n", sols[0], solutions[0]);
	}
	solutions[0] = sols[0];
	solutions[1] = sols[1];
 */
	return (solution_count);
}
