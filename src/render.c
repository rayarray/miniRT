/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:55:46 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/21 12:46:40 by rleskine         ###   ########.fr       */
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

	camray.destination = scene->camera->dir;
	camray.origin = scene->camera->loc;
	camera = initCamera(camray, image->width, image->height,
			(M_PI * scene->camera->fov) / 180);
	y = 0 - 1;
	while (++y < image->height)
	{
		x = 0 - 1;
		while (++x < image->width)
		{
			camray = getRay(camera, x, y);
			camray.destination = vecAdd(camray.destination, scene->camera->dir);
			if ((	x == image->width / 2 && y == 0)
				|| (x == image->width / 2 && y == image->height / 2)
				|| (x == image->width / 2 && y == image->height - 1)) {
				printf("debug activated at x:%d y:%d\n", x, y);
				col = cast_ray(scene, camray, -1);
			}
			else
				col = cast_ray(scene, camray, camera.max_depth);
			mlx_put_pixel(image, x, y, coltouint32_t(col));
		}
	}
}
