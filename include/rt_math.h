/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:15:02 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 16:00:06 by tsankola         ###   ########.fr       */
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

// Floating point comparisons
int		feq(double a, double b);
int		flessthan(double a, double b);
int		fgreaterthan(double a, double b);
int		fleq(double a, double b);
int		fgeq(double a, double b);

double	vec_distance(t_vec a, t_vec b);

double	vec_length(t_vec a);

// Causes divide by zero if a is zero vector.
t_vec	vec_normalize(t_vec a);

double	dot_product(t_vec a, t_vec b);

t_vec	cross_product(t_vec a, t_vec b);

t_vec	vec_add(t_vec a, t_vec b);

t_vec	vec_sub(t_vec a, t_vec b);

t_vec	vec_neg(t_vec a);

t_vec	vec_scal_mul(t_vec a, double s);

#endif