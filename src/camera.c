/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:17:25 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/12 18:25:20 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "vector.h"
#include "camera.h"
#include "tracer.h"
#include "rt_validations.h"

int camera_ctor(struct s_camera *c, t_point3 loc, t_vec dir, int fov)
{
	c->loc = loc;
	if (!is_direction_vector(dir))
		return (1);
	c->dir = vec_normalize(dir);
	if (!is_fov(fov))
		return (1);
	c->fov = fov;
	return (0);
}

// center: ray containing camera origin and direction, x: pixel width, y: pixel height, fov in degrees []
t_camera2	initCamera(t_ray center, int width, int height, double fov)
{
	t_camera2	c;

	c.focus_dist = 1;
	c.max_depth = BOUNCE_LIMIT;
	c.h_fov = fov;
	c.center = center;
	c.img_width = width;
	c.img_height = height;
	c.aspect_ratio = (double)width / (double)height;
	c.up = vecInit(0, 1, 0);
	c.h = tan(c.h_fov / 2);
	c.viewport_height = 2 * c.h * c.focus_dist;
	c.viewport_width = c.viewport_height * (double)width / (double)height;
	c.w = unitVector(c.center.destination);
	c.u = unitVector(vecCross(c.up, c.w));
	c.v = vecCross(c.w, c.u);
	c.viewport_u = vecMul(c.u, c.viewport_width);
	c.viewport_v = vecMul(vecSub(vecInit(0, 0, 0), c.v), c.viewport_height);
	c.px_delta_u = vecDiv(c.viewport_u, c.img_width);
	c.px_delta_v = vecDiv(c.viewport_v, c.img_height);
	c.viewport_upleft = vecSub(c.center.destination, vecMul(c.w, c.focus_dist));
	c.viewport_upleft = vecSub(c.viewport_upleft, vecDiv(c.viewport_u, 2.0));
	c.viewport_upleft = vecSub(c.viewport_upleft, vecDiv(c.viewport_v, 2.0));
	c.pixel00_loc = vecAdd(c.viewport_upleft,
			vecMul(vecAdd(c.px_delta_u, c.px_delta_v), 0.5));
	return (c);
}

//returns camera ray for pixel(i, j)
t_ray	getRay(t_camera2 c, int i, int j)
{
	t_ray	ray;

	ray.destination = vecAdd(c.pixel00_loc,
			vecAdd(vecMul(c.px_delta_u, i), vecMul(c.px_delta_v, j)));
	ray.origin = c.center.origin;
	return (ray);
}
