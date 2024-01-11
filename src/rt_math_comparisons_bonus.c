/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_comparisons_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:51:17 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math_bonus.h"

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
