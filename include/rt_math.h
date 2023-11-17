/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:15:02 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 18:03:26 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H
# include <math.h>
# include "rt_typedef.h"

static const t_vec	g_zero_vector = {0,0,0};

double	vec_distance(t_vec a, t_vec b);

double	vec_length(t_vec a);

// Causes divide by zero if a is zero vector.
t_vec	vec_normalize(t_vec a);

double	dot_product(t_vec a, t_vec b);

t_vec	cross_product(t_vec a, t_vec b);

t_vec	vec_add(t_vec a, t_vec b);

t_vec	vec_sub(t_vec a, t_vec b);

t_vec	vec_neg(t_vec a);

#endif