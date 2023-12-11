/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:55:46 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/12 00:54:33 by rleskine         ###   ########.fr       */
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

// void	render(struct s_scene *scene, mlx_image_t *image)
// {
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_color		col;

// 	y = 0 - 1;
// 	while (++y < image->height)
// 	{
// 		x = 0 - 1;
// 		while (++x < image->width)
// 		{
// 			col = trace_ray(scene, image->width, image->height, (t_pixel){x, y});
// //			printf(" ");
// 			mlx_put_pixel(image, x, y, coltouint32_t(col));
// 		}
// //		printf("\n");
// 	}
// //	printf("image drawn");
// //	getchar();
// }

void    render(struct s_scene *scene, mlx_image_t *image)
{
    t_camera2   camera;
    t_ray       camray;
    uint32_t    x;
    uint32_t    y;
    t_color     col;

    camray.dir = scene->camera->dir;
    camray.dir.x = 0.4;
    camray.point = scene->camera->loc;
    camera = initCamera(camray, image->width, image->height, (M_PI * scene->camera->fov) / 180);
    // t_ray r;
    // r = getRay(camera, 1, 1);
    // printf("ray at 0, 0: (x%f, y%f, z%f)\n", r.dir.x, r.dir.y, r.dir.z);
	// r = getRay(camera, 400, 262);
    // r.dir = vecAdd(r.dir, scene->camera->dir);
    // printf("ray.loc at 400, 262: (x%f, y%f, z%f)\n", r.point.x, r.point.y, r.point.z);
	// printf("ray.dir at 400, 262: (x%f, y%f, z%f)\n", r.dir.x, r.dir.y, r.dir.z);
	// r = getRay(camera, 600, 600);
	// printf("ray at 600, 600: (x%f, y%f, z%f)\n", r.dir.x, r.dir.y, r.dir.z);
    y = 0 - 1;
    while (++y < image->height)
    {
        x = 0 - 1;
        while (++x < image->width)
        {
            camray = getRay(camera, x, y);
            camray.dir = vecAdd(camray.dir, scene->camera->dir);
            col = cast_ray(scene, camray);
            mlx_put_pixel(image, x, y, coltouint32_t(col));
        }
    }
}
