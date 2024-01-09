/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:55:46 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/09 11:23:57 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "render.h"

static uint32_t	coltouint32_t(t_color col)
{
	uint32_t	ret;

	ret = 0;
	ret += col.r << 24;
	ret += col.g << 16;
	ret += col.b << 8;
	ret += col.a;
	return (ret);
}

void	render(struct s_scene *scene, mlx_image_t *image)
{
	t_camera2	camera;
	t_ray		camray;
	uint32_t	x;
	uint32_t	y;
	t_color		col;

	camray.loc = scene->camera->loc;
	camera = initCamera((t_ray){scene->camera->loc, scene->camera->dir},
			image->width, image->height, (M_PI * scene->camera->fov) / 180);
	//vecPrint("camray.loc", camray.loc, 1);
	shape_list_cam_check(scene->shapes, camray.loc);
	y = 0 - 1;
	while (++y < image->height)
	{
		x = 0 - 1;
		while (++x < image->width)
		{
			//camray.loc = scene->camera->loc;
			camray.dir = getRay(camera, x, y);
			camray.dir = unitVector(vecAdd(camray.dir, scene->camera->dir));
			col = cast_ray(scene, camray, camera.max_depth);
			mlx_put_pixel(image, x, y, coltouint32_t(col));
		}
	}
}

void	debug_ray(struct s_scene *scene, mlx_image_t *image, uint32_t x, uint32_t y)
{
	t_camera2	cam;
	t_ray		camray;
	t_color		col;

	cam = initCamera((t_ray){scene->camera->loc, scene->camera->dir}, image->width,
		image->height, (M_PI * scene->camera->fov) / 180);
	camray.loc = scene->camera->loc;
	camray.dir = unitVector(vecAdd(getRay(cam, x, y), scene->camera->dir));
	col = cast_ray(scene, camray, 7357);
	mlx_put_pixel(image, x, y, coltouint32_t(col));
}
