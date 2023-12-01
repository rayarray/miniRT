/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:39 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/01 05:01:26 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "rt_math.h"
#include "tracer.h"
#include "color.h"
#include <stdio.h>
#include <math.h>
/* // DEPRECATED
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
 */

// Done using 
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
// as a guide
static t_vec	pixel_to_camera_ray(int fov, mlx_image_t *image,
	uint32_t x, uint32_t y)
{
	t_point2	ndc_point;		// 
	t_point2	screen_point;
	t_vec		camera_point;
	double		half_fov_r;
	double		aspect_ratio;

	ndc_point = (t_point2){((double)x + 0.5) / image->width,
		 ((double)y + 0.5) / image->height};
	screen_point = (t_point2){2 * ndc_point.x - 1, 1 - 2 * ndc_point.y};	// y is flipped here
	aspect_ratio = (double)image->width / image->height;
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

//	printf("light ray length %f\n", length);
//	getchar();
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

	closest_shape = NULL;
	col = COL_BACKGROUND;
	distance_to_nearest = INFINITY;
	shape = scene->shapes;
	while (shape != NULL)
	{
		if (flessthan(intersect_distance(shape, ray), distance_to_nearest))
			closest_shape = shape;
		shape = shape->next;
	}
	if (closest_shape)
		col = intersect_color(closest_shape, scene, ray);
	return (col);
}

t_color	trace_ray(struct s_scene *scene, mlx_image_t *image,
	uint32_t x, uint32_t y)
{
	t_vec	camera_point;		// point in camera space
	t_ray		ray;
	t_color		col;

	camera_point = pixel_to_camera_ray(scene->camera->fov, image, x, y);
	// TODO rotate camera point to camera direction using rotation matrix
	ray.origin = scene->camera->loc;
	ray.destination = camera_point;
	col = cast_ray(scene, ray);
	return (col);
}
