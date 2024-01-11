/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:32:32 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>
# include "rt_typedef_bonus.h"

// Vector functions
t_vec	vec_normalize(t_vec a);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_neg(t_vec a);
t_vec	vec_scal_mul(t_vec a, double s);
t_vec	vec_scal_div(t_vec a, double div);
// int		vec_eq(t_vec a, t_vec b);
double	vec_distance(t_vec a, t_vec b);
double	vec_length(t_vec a);
double	dot_product(t_vec a, t_vec b);
t_vec	cross_product(t_vec a, t_vec b);

#endif	/* VECTOR_H */
