/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:15:02 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/15 17:13:21 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H
# include <math.h>
# include "rt_typedef.h"

static const t_vector	g_zero_vector = {0,0,0};

double	vec_distance(t_vector a, t_vector b);

double	vec_length(t_vector a);

// Causes divide by zero if a is zero vector.
t_vector	vec_normalize(t_vector a);

double	dot_product(t_vector a, t_vector b);

t_vector	cross_product(t_vector a, t_vector b);

t_vector	vec_add(t_vector a, t_vector b);

t_vector	vec_sub(t_vector a, t_vector b);

t_vector	vec_neg(t_vector a);

#endif