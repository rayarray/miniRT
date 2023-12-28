/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:53:18 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/28 23:30:07 by tsankola         ###   ########.fr       */
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

#include <stdio.h>
int	feq(double a, double b)
{
//	return (fabs(a - b) <= RT_EPSILON);
	double	eps;
	if (isnan(a) || isnan(b))
	{
		printf("nan a %f b %f \n",a, b);
		getchar();
	}
	eps = fmax(fabs(a), fabs(b)) * 0.001;
//	printf("eps %f for %f and %f\n", eps, a, b);
	return (fabs(a - b) <= eps);
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

// Returns INFINITY if no solutions are found or if all solutions are negative
double	min_pos_discriminant(double a, double b, double c)
{	// Source material says this method might produce errors ("catastrophic cancellation")
	// TODO replace with a better method
	double discriminant;
	double results[3];
	
	results[0] = INFINITY;
	if (feq(a, 0))
		return (INFINITY);
	discriminant = pow(b, 2) - 4 * a * c;
	if (isnan(discriminant))
	{
		printf("discriminant nan\n");
		getchar();
	}
	if (flessthan(discriminant, 0))
		return (INFINITY);
	if (feq(discriminant, 0) /* && fgeq(-b / (2 * a), 0) */)	// one solution
		results[0] = -b / (2 * a);
	else //if (fgreaterthan(discriminant, 0))	// two solutions
	{
		// results[1] = (-b + sqrt(discriminant)) / (2 * a);
		// results[2] = (-b - sqrt(discriminant)) / (2 * a);
		double q;
		if (fgreaterthan(b, 0))
			q = (-b + sqrt(discriminant)) / 2;
		else
			q = (-b - sqrt(discriminant)) / 2;
		results[1] = q / a;
		results[2] = c / q;
		if (isnan(results[1]) || isnan(results[2])) {printf("isnan result\n"); getchar();}
		results[0] = fmin(results[1], results[2]);
//		if (fgeq(results[1], 0) && fgeq(results[2], 0))
//			results[0] = fmin(results[1], results[2]);
//		else if (fgeq(results[1], 0) || fgeq(results[2], 0))
//		else if (!(flessthan(results[1], 0) && flessthan(results[2], 0)))
//		{
//			results[0] = fmax(results[1], results[2]);
//			printf("%f %f %f\n", results[0], results[1], results[2]);
//			getchar();
//		}
//		else
//			; // No positive results
// 		if (!(flessthan(results[1], 0) && flessthan(results[2], 0)) != 
// 				(fgeq(results[1], 0) || fgeq(results[2], 0)))
// 		{
// //			printf("flessthan %d %d\n", flessthan(results[1], 0), flessthan(results[2], 0));
// //			printf("fgeq %d %d\n", fgeq(results[1], 0), fgeq(results[2], 0));
// //			printf("%f %f %f\n", results[0], results[1], results[2]);
// //			getchar();
// 		}	
	}
//	else
//		;	// No solutions
	return (results[0]);
}
