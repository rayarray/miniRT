/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:32:32 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/16 17:07:20 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>
# include "rt_typedef.h"

t_vec	vecInit(double x, double y, double z);
t_vec	vecScalar(double i);
t_vec	vecAdd(t_vec v1, t_vec v2);
t_vec	vecSub(t_vec v1, t_vec v2);
t_vec	vecMul(t_vec v1, double t);
t_vec	vecDiv(t_vec v1, double t);
double	vecDot(t_vec v1, t_vec v2);
t_vec	vecCross(t_vec v1, t_vec v2);
double	vecLengthSquared(t_vec v1);
double	vecLength(t_vec v1);
t_vec	unitVector(t_vec v1);

#endif	/* VECTOR_H */
