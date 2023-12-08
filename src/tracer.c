/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:39 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/08 15:52:55 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "rt_math.h"
#include "tracer.h"
#include "color.h"

// Done using 
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
// as a guide
static t_vec	pixel_to_camera_ray(int fov, uint32_t width, uint32_t height,
	t_pixel	pixel_point)
{
	t_point2	ndc_point;
	t_point2	screen_point;
	t_vec		camera_point;
	double		half_fov_r;
	double		aspect_ratio;

	ndc_point = (t_point2){((double)pixel_point.x + 0.5) / width,
		 ((double)pixel_point.y + 0.5) / height};
	screen_point = (t_point2){2 * ndc_point.x - 1, 1 - 2 * ndc_point.y};	// y is flipped here
	aspect_ratio = (double)width / height;
	camera_point = (t_vec){(screen_point.x) * aspect_ratio, (screen_point.y), 1};
	half_fov_r = (double)fov / 2.0 * M_PI / 180.0;
	camera_point.x = camera_point.x * tan(half_fov_r);
	camera_point.y = camera_point.y * tan(half_fov_r);
	return (vec_normalize(camera_point));
}

// Tests if a given ray intersects with any shape along the ray within length.
int	collision_test(struct s_scene *scene, t_ray ray, double length)
{
	struct	s_shape *shape;

	shape = scene->shapes;
	while (shape != NULL)
	{
		if (flessthan(intersect_distance(shape, ray), length))
			return (1);
		shape = shape->next;
	}
	return (0);
}

static t_color	cast_ray(struct s_scene *scene, t_ray ray)
{
	struct s_shape	*shape;
	struct s_shape	*closest_shape;
	double			distance_to_nearest;
	t_color			col;
	double			dist;

	closest_shape = NULL;
	col = (t_color){.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};
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
		col = intersect_color(closest_shape, scene, ray);
	return (col);
}

t_color	trace_ray(struct s_scene *scene, uint32_t width, uint32_t height,
	t_pixel	pixel_point)
{
	t_vec	camera_point;		// point in camera space
	t_ray	ray;
	t_color	col;

	camera_point = pixel_to_camera_ray(scene->camera->fov, width, height, pixel_point);
	// TODO rotate camera point to camera direction using rotation matrix
	ray.origin = scene->camera->loc;
	ray.destination = camera_point;
	col = cast_ray(scene, ray);
	return (col);
}
