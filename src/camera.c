/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:17:25 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/12 10:23:40 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "vector.h"
#include "camera.h"
#include "tracer.h"
#include "rt_validations.h"

// t_camera	initCamera(mlx_image_t *image, int fov, void *scene, t_ray center)
// {
// 	t_camera	c;

// 	c.fov = fov;
// 	c.image_width = image->width;
// 	c.aspect_ratio = image->height / image->width;
// 	ft_printf("aspectratio %f\n", c.aspect_ratio);
// 	c.focal_length = 1;
// 	c.scene = scene;
// 	c.center = center;
// 	c.viewport_height = 2.0;
// 	c.viewport_width = c.viewport_height
// 		* ((double)(image->width) / image->height);
// 	//c.viewport_u = vecAdd(c.center.destination,
// 	//		vecInit(c.viewport_width, 0, 0));
// 	c.viewport_u = vecInit(c.viewport_width, 0, 0);
// 	//c.viewport_v = vecAdd(c.center.destination,
// 	//		vecInit(0, -c.viewport_height, 0));
// 	c.viewport_v = vecInit(0, -c.viewport_height, 0);
// 	c.pixel_delta_u = vecDiv(c.viewport_u, image->width);
// 	c.pixel_delta_v = vecDiv(c.viewport_v, image->height);
// 	c.viewport_uv_half = vecDiv(vecAdd(c.viewport_u, c.viewport_v), 2);
// 	c.viewport_upper_left = vecSub(c.center.destination, c.viewport_uv_half);
// 	//c.viewport_upper_left = vecSub(c.center.destination, vecSub(
// 	//			vecInit(c.focal_length, 0, 0), c.viewport_uv_half));
// 	c.pixel00_loc = vecAdd(c.viewport_upper_left, vecMul(
// 				vecAdd(c.pixel_delta_u, c.pixel_delta_v), 0.5));
// 	return (c);
// }

// Takes camera direction vector and calculates what is vector for 
// camera up direction
t_vec camera_up(t_vec camera_dir)
{
	t_vec	world_up;

	world_up = vecInit(0, 1, 0);
	if (camera_dir.x == 0 && camera_dir.z == 0)
		world_up = vecInit(0, 0, 1);
	return (vecCross(camera_dir, world_up));
}

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

/*
// DEPRECATED TODO Needs rework to work with already constructed (uninitialized) camera
t_camera	initCamera(mlx_image_t *image, int fov, void *scene, t_ray center)
{	// DEPRECATED
	t_camera	c;

	(void)scene;
	c.fov = fov;
	c.image_width = image->width;
	c.aspect_ratio = (double)image->width / image->height;
	c.focal_length = 1;
	c.viewport_height = 2.0;
	c.viewport_width = c.viewport_height
		* ((double)(image->width) / image->height);
	c.viewport_u = vecInit(c.viewport_width, 0, 0);
	c.viewport_v = vecInit(0, -c.viewport_height, 0);
	c.pixel_delta_u = vecDiv(c.viewport_u, image->width);
	c.pixel_delta_v = vecDiv(c.viewport_v, image->height);
	//c.viewport_uv_half = vecDiv(vecAdd(c.viewport_u, c.viewport_v), 2);
	c.viewport_upper_left = vecSub(center.origin, vecInit(0, 0, c.focal_length));
	c.viewport_upper_left = vecSub(c.viewport_upper_left, vecDiv(c.viewport_u, 2));
	c.viewport_upper_left = vecSub(c.viewport_upper_left, vecDiv(c.viewport_v, 2));
	c.pixel00_loc = vecAdd(c.viewport_upper_left,
			vecMul(vecAdd(c.pixel_delta_u, c.pixel_delta_v), 0.5));
	return (c);
} */
/*
void	renderCamera(mlx_image_t *image, t_camera c)
{	// DEPRECATED
	//t_vec		pixel_center;
	//t_vec		ray_direction;
	t_ray		pixel_ray;
	uint32_t	pixel_color;
	int			x;
	int			y;

	//auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
	//auto ray_direction = pixel_center - camera_center;
	y = -1;
	while (++y < (int)image->height)
	{
		x = -1;
		while (++x < (int)image->width)
		{
			pixel_ray.origin = vecAdd(c.pixel00_loc,
					vecAdd(vecMul(c.pixel_delta_u, x),
						vecMul(c.pixel_delta_v, y)));
			pixel_ray.destination = vecSub(pixel_ray.origin, c.center.origin);
			pixel_color = rayColor(c, pixel_ray);
			mlx_put_pixel(image, x, y, pixel_color);
		}
	}
} */
