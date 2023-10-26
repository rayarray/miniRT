/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:36:12 by rleskine          #+#    #+#             */
/*   Updated: 2023/10/26 19:01:50 by rleskine         ###   ########.fr       */
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

int	main(void)
{
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
