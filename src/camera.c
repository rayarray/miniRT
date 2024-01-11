/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:17:25 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 13:57:26 by rleskine         ###   ########.fr       */
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

t_vec	camera_up(t_vec center)
{
	(void)center;
	return ((t_vec){0, 1, 0});
}

// center: ray containing camera origin and direction, x: pixel width, y: pixel height, fov in degrees []
t_camera2	init_camera(t_camera2 cam, int width, int height, double fov)
{
	cam.focus_dist = 1;
	cam.max_depth = BOUNCE_LIMIT;
	cam.h_fov = fov;
	//cam.center = center;
	cam.img_width = width;
	cam.img_height = height;
	cam.aspect_ratio = (double)width / (double)height;
	cam.up = camera_up(cam.center.dir);
	// if (fabs(center.dir.y) == 1)		// Quick fix to handle situation when looking down or up along y-axis
	// 	cam.up = vecInit(0, 0, 1);
	// else
	// 	cam.up = vecInit(0, 1, 0);
	cam.h = tan(cam.h_fov / 2);
	cam.viewport_height = 2 * cam.h * cam.focus_dist;
	cam.viewport_width = cam.viewport_height * (double)width / (double)height;
	cam.w = vec_normalize(cam.center.dir);
	cam.u = vec_normalize(cross_product(cam.up, cam.w));
	cam.v = cross_product(cam.w, cam.u);
	cam.viewport_u = vec_scal_mul(cam.u, cam.viewport_width);
	cam.viewport_v = vec_scal_mul(vec_sub((t_vec){0, 0, 0}, cam.v), cam.viewport_height);
	cam.px_delta_u = vec_scal_div(cam.viewport_u, cam.img_width);
	cam.px_delta_v = vecDiv(cam.viewport_v, cam.img_height);
	cam.viewport_upleft = vecSub(cam.center.dir, vecMul(cam.w, cam.focus_dist));
	cam.viewport_upleft = vecSub(cam.viewport_upleft, vecDiv(cam.viewport_u, 2.0));
	cam.viewport_upleft = vecSub(cam.viewport_upleft, vecDiv(cam.viewport_v, 2.0));
	cam.pixel00_loc = vecAdd(cam.viewport_upleft,
			vecMul(vecAdd(cam.px_delta_u, cam.px_delta_v), 0.5));
	return (cam);
}

//returns camera ray for pixel(i, j)
t_ray	get_ray(t_camera2 c, int i, int j)
{
	t_ray	ray;

	ray.dir = vec_add(c.pixel00_loc,
			vec_add(vec_scal_mul(c.px_delta_u, i), 
				vec_scal_mul(c.px_delta_v, j)));
	ray.loc = c.center.loc;
	return (ray);
}
