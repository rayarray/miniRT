/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:42:12 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/17 18:17:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_typedef.h"
#include "rt_math.h"

t_point	rayPoint(t_ray r, double distance)
{
	return (vecAdd(r.origin,
			vecMul(r.destination, vecInit(distance, distance, distance))));
}
