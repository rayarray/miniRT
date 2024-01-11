/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:39 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 15:50:00 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt_math.h"
#include "tracer.h"
#include "color.h"

// Tests if a given ray intersects with any shape along the ray within length.
int	collision_test(struct s_scene *scene, t_ray ray, double length)
{
	struct s_shape	*shape;
	double			distance;

	shape = scene->shapes;
	while (shape != NULL)
	{
		distance = intersect_distance(shape, ray);
		if (flessthan(distance, length))
			return (1);
		shape = shape->next;
	}
	return (0);
}

t_color	cast_ray(struct s_scene *scene, t_ray ray, int bounces)
{
	struct s_shape	*shape;
	struct s_shape	*closest_shape;
	double			distance_to_nearest;
	t_color			col;
	double			dist;

	closest_shape = NULL;
	col = (t_color){.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};
	if (bounces <= 0)
		return (col);
	distance_to_nearest = INFINITY;
	shape = scene->shapes;
	while (shape != NULL)
	{
		dist = intersect_distance(shape, ray);
		if (flessthan(dist, distance_to_nearest))
		{
			distance_to_nearest = dist;
			closest_shape = shape;
		}
		shape = shape->next;
	}
	if (closest_shape)
		col = intersect_color(closest_shape, scene, ray, bounces);
	return (col);
}
