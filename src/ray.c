/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:06:29 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/14 14:20:22 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "rt_typedef.h"
#include "ray.h"

t_point3	getContactPoint(t_ray ray, t_ray plane)
{
	(void)ray;
	(void)plane;
	return (vecInit(0, 0, 0));
}