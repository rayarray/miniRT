/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:36:12 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/18 01:18:44 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42.h"
#include "libft.h"
#include "minirt.h"
#include "vector.h"
#include "camera.h"
#include "parser.h"
#include "scene.h"

#define WIDTH	512
#define HEIGHT	512

static mlx_image_t	*image;

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_randomize(void *param)
{
	(void)param;
	for (int32_t i = 0; i < (int)image->width; ++i)
	{
		for (int32_t y = 0; y < (int)image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
	for (int32_t i = 0; i < (int)image->width; i++)
		mlx_put_pixel(image, 256, i, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF));
}

void	ft_hook(void *param)
{
	mlx_t* mlx = param;

	(void)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ENTER))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

/*
 * Program flow (My current idea as of 16.11. -Tommi):
 * 		1.	parse, create scene
 * 		2.	render scene line by line, calling tracing function on each pixel
 * 		2.1.	tracing function will iterate through shapes in scene to see if
 * 				it hits anything and returns the color using lights etc. 
 * 		3.	draw rendered scene
 * 
 * 		(With threads, forbidden in subject but could be interesting:)
 * 		2. Use threads to render scene line by line
 * 		2.1. Put lines in an array with an index protected by mutex
 * 		2.2. Threads will take a line to process and increment index
 * 		2.2.1.	When processing the line, thread will call raytrace function on
 * 				each pixel on the line using the scene as data (which should be
 * 				immutable).
 * 		2.3. When thread is done with a line, get next line
 * 		2.4. When no more lines available, kill thread
 * 		3. When all threads are done, send rendered scene to be drawn
 */

#include "rt_validations.h"
int	main(int argc, char **argv)
{
	struct s_scene	*scene;

/*	char *s = "255,255,255	";
	printf("%s %d", s, is_double_triplet_strict(s));
	return 1;
 */
	if (argc != 2){
		printf("Usage: 'miniRT <filename>'\n");
		return 1;
	}
	scene = get_scene(argv[1]);
	printf("got scene! %p\n", scene);
	printf("ambient %f\n", scene->ambient->light_ratio);
	printf("camera %d\n", scene->camera->fov);
	for (struct s_light *l = scene->lights; l != NULL; l = l->next)
		printf("lights %f\n", l->brightness);
	for (struct s_shape *s = scene->shapes; s != NULL; s = s->next)
		printf("shapes %d\n", s->type);
	scene_dtor(&scene);
	return (0);

	mlx_t		*mlx;
	t_vec		v1;
	t_vec		v2;
	t_vec		v3;
	t_ray		center;
	t_camera	camera;

	v1 = vecInit(10, 10, 10);
	v2 = vecInit(-5, -5, -5);
	v3 = vecAdd(v1, v2);
	//printf("x%f y%f z%f\n", v3.x, v3.y, v3.z);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 512, 512)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	center = (t_ray){(t_point){0, 0, 0}, (t_vec){0, 0, 0}};
	camera = initCamera(image, 90, NULL, center);
	//printf("camera asp ratio %f\n", camera.aspect_ratio);
	printf("camera pixel00_loc x%f y%f z%f\n", camera.pixel00_loc.x, camera.pixel00_loc.y, camera.pixel00_loc.z);
	renderCamera(image, camera);
	//mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
