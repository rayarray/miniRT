/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:17:25 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 15:11:24 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "vector.h"
#include "camera.h"
#include "tracer.h"
#include "rt_validations.h"

int	camera_ctor(struct s_camera *c, t_point3 loc, t_vec dir, int fov)
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

static inline t_vec	v_div(t_vec a, double div)
{
	return ((t_vec){a.x / div, a.y / div, a.z / div});
}

static inline t_vec	camera_up(t_vec center)
{
	if (feq(center.x, 0.0) && feq(center.z, 0.0))
	{
		if (center.y < 0.0)
			return ((t_vec){0, 0, 1});
		else
			return ((t_vec){0, 0, -1});
	}
	return ((t_vec){0, 1, 0});
}

// center: ray containing t_camera2 with camera center set, x: pixel width, 
// y: pixel height, fov in degrees []
t_camera2	init_camera(t_camera2 c, int width, int height, double fov)
{
	c.focus_dist = 1;
	c.max_depth = BOUNCE_LIMIT;
	c.h_fov = fov;
	c.img_width = width;
	c.img_height = height;
	c.aspect_ratio = (double)width / (double)height;
	c.up = camera_up(c.center.dir);
	c.h = tan(c.h_fov / 2);
	c.viewport_height = 2 * c.h * c.focus_dist;
	c.viewport_width = c.viewport_height * (double)width / (double)height;
	c.w = vec_normalize(c.center.dir);
	c.u = vec_normalize(cross_product(c.up, c.w));
	c.v = cross_product(c.w, c.u);
	c.viewport_u = vec_scal_mul(c.u, c.viewport_width);
	c.viewport_v = vec_scal_mul(vec_sub((t_vec){0, 0, 0}, c.v),
			c.viewport_height);
	c.px_delta_u = vec_scal_div(c.viewport_u, c.img_width);
	c.px_delta_v = vec_scal_div(c.viewport_v, c.img_height);
	c.viewport_upleft = vec_sub(vec_sub(c.center.dir,
				vec_scal_mul(c.w, c.max_depth)), v_div(c.viewport_u, 2.0));
	c.viewport_upleft = vec_sub(c.viewport_upleft, v_div(c.viewport_v, 2.0));
	c.pixel00_loc = vec_add(c.viewport_upleft,
			vec_scal_mul(vec_add(c.px_delta_u, c.px_delta_v), 0.5));
	return (c);
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
