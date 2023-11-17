/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:39 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/17 19:37:38 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "tracer.h"
#include "scene.h"
#include <stdio.h>

uint32_t	rayColor(t_camera c, t_ray ray)
{
	t_vec		unit_direction;
	double		a;
	t_color 	color;

	(void)c;
	if (hitSphere(vecInit(0, 0, -3), 1, ray) > 0)
	{
		//printf("origin x%f y%f z%f\n", ray.origin.x, ray.origin.y, ray.origin.z);
		return (0xFF << 24 | 0x00 << 16 | 0x00 << 8 | 0xFF);
	}
	unit_direction = vecDiv(ray.destination, vecLength(ray.destination));
	a = 0.5 * (unit_direction.y + 1.0);
	//return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
	//gradient_color = (1.0 - a) * 0xFFFFFFFF + a * 
	//return (x % 0xFF << 24 | x % 0xFF << 16 | y % 0xFF << 8 | y % 0xFF);
	color.r = ((1.0 - a) + a * 0.5) * 255;
	color.g = ((1.0 - a) + a * 0.7) * 255;
	color.b = ((1.0 - a) + a * 1.0) * 255;
	color.a = 0xFF;
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}
