/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:15:02 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 13:42:40 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H
# define RT_EPSILON 0.0000001
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# include <math.h>
# include "rt_typedef.h"

// Integer functions
int		imax(int a, int b);
int		imin(int a, int b);

// Floating point comparisons
int		feq(double a, double b);
int		flessthan(double a, double b);
int		fgreaterthan(double a, double b);
int		fleq(double a, double b);
int		fgeq(double a, double b);

// Calculates solutions of a quadratic equation, stores the possible solutions
// in solutions in ascending order and returns the number of solutions.
// Should a equal 0, a divide by zero error will follow. In that case the
// equation is not quadratic, so perhaps this function should not be utilised.
int		quadratic_solver(double a, double b, double c, double solutions[2]);

t_plane_eq	plane_eq(t_point3 loc, t_vec normal);

#endif