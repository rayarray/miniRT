/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:42:12 by rleskine          #+#    #+#             */
/*   Updated: 2023/10/25 16:55:17 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_point	rayPoint(t_ray r, double distance)
{
	return (vecAdd(r.origin,
			vecMul(r.destination, vecInit(distance, distance, distance))));
}
